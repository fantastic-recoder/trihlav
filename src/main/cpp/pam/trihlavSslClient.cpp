/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>

#include "trihlavSslClient.hpp"

#include "trihlavLib/trihlavConstants.hpp"

using boost::asio::ip::tcp;

using std::string;
using std::ostream;
using boost::lexical_cast;
using std::string;
using boost::asio::ssl::context;
using boost::asio::io_service;

namespace trihlav {

SslClient::~SslClient() {
	// TODO Auto-generated destructor stub
}

/**
 *  TODO: URL encoding
 */
SslClient::SslClient(io_service& io_service, context& context,
		const string& pServer, const string& pUsername,
		const Passwords& pPasswords) :
		itsResolver(io_service), itsSocket(io_service, context) {

	// Form the request. We specify the "Connection: close" header so that the
	// server will close the socket after transmitting the response. This will
	// allow us to treat all data up until the EOF as the content.
	std::ostream request_stream(&itsRequest);
	string myUrl{K_AUTH_URL+"?"+K_USER_NM+"="+pUsername};
	const string K_SP(" "+K_PSWD+"=");
	for (auto myPswdPtr = pPasswords.begin(); //
			myPswdPtr != pPasswords.end();
			++myPswdPtr) {
		myUrl += (K_SP + *myPswdPtr);
	}
	BOOST_LOG_TRIVIAL(debug)<<myUrl;
	request_stream << "GET " << myUrl << " HTTP/1.0\r\n";
	request_stream << "Host: " << pServer << "\r\n";
	request_stream << "Accept: */*\r\n";
	request_stream << "Connection: close\r\n\r\n";

	// Start an asynchronous resolve to translate the server and service names
	// into a list of endpoints.
	tcp::resolver::query query(pServer, "https");
	itsResolver.async_resolve(query,
			boost::bind(&SslClient::handle_resolve, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator));
}

void SslClient::handle_resolve(const boost::system::error_code& err,
		tcp::resolver::iterator endpoint_iterator) {
	if (!err) {
		std::cout << "Resolve OK" << "\n";
		itsSocket.set_verify_mode(boost::asio::ssl::verify_peer);
		itsSocket.set_verify_callback(
				boost::bind(&SslClient::verify_certificate, this, _1, _2));

		boost::asio::async_connect(itsSocket.lowest_layer(), endpoint_iterator,
				boost::bind(&SslClient::handle_connect, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error)<< "Error resolve: " << err.message() << "\n";
	}
}

bool SslClient::verify_certificate(bool preverified,
		boost::asio::ssl::verify_context& ctx) {
	// The verify callback can be used to check whether the certificate that is
	// being presented is valid for the peer. For example, RFC 2818 describes
	// the steps involved in doing this for HTTPS. Consult the OpenSSL
	// documentation for more details. Note that the callback is called once
	// for each certificate in the certificate chain, starting from the root
	// certificate authority.

	// In this example we will simply print the certificate's subject name.
	char subject_name[256];
	X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
	X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
	BOOST_LOG_TRIVIAL(info)<< "Verifying " << subject_name << "\n";

	return preverified;
}

void SslClient::handle_connect(const boost::system::error_code& err) {
	if (!err) {
		std::cout << "Connect OK " << "\n";
		itsSocket.async_handshake(boost::asio::ssl::stream_base::client,
				boost::bind(&SslClient::handle_handshake, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error)<< "Connect failed: " << err.message() << "\n";
	}
}

void SslClient::handle_handshake(const boost::system::error_code& error) {
	if (!error) {
		BOOST_LOG_TRIVIAL(info)<< "Handshake OK " << "\n";
		BOOST_LOG_TRIVIAL(debug) << "Request: " << "\n";
		const char* header = boost::asio::buffer_cast<const char*>(
				itsRequest.data());
		BOOST_LOG_TRIVIAL(debug) << header << "\n";

		// The handshake was successful. Send the request.
		boost::asio::async_write(itsSocket, itsRequest,
				boost::bind(&SslClient::handle_write_request, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error) << "Handshake failed: " << error.message() << "\n";
	}
}

void SslClient::handle_write_request(const boost::system::error_code& err) {
	if (!err) {
		// Read the response status line. The itsResponse streambuf will
		// automatically grow to accommodate the entire line. The growth may be
		// limited by passing a maximum size to the streambuf constructor.
		boost::asio::async_read_until(itsSocket, itsResponse, "\r\n",
				boost::bind(&SslClient::handle_read_status_line, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error)<< "Error write req: " << err.message() << "\n";
	}
}

void SslClient::handle_read_status_line(const boost::system::error_code& err) {
	if (!err) {
		// Check that response is OK.
		std::istream response_stream(&itsResponse);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
			std::cout << "Invalid response\n";
			return;
		}
		if (status_code != 200) {
			std::cout << "Response returned with status code ";
			std::cout << status_code << "\n";
			return;
		}
		std::cout << "Status code: " << status_code << "\n";

		// Read the response headers, which are terminated by a blank line.
		boost::asio::async_read_until(itsSocket, itsResponse, "\r\n\r\n",
				boost::bind(&SslClient::handle_read_headers, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error)<< "Error: " << err.message() << "\n";
	}
}

void SslClient::handle_read_headers(const boost::system::error_code& err) {
	if (!err) {
		// Process the response headers.
		std::istream response_stream(&itsResponse);
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
			std::cout << header << "\n";
		std::cout << "\n";

		// Write whatever content we already have to output.
		if (itsResponse.size() > 0)
			BOOST_LOG_TRIVIAL(debug)<< &itsResponse;

			// Start reading remaining data until EOF.
		boost::asio::async_read(itsSocket, itsResponse,
				boost::asio::transfer_at_least(1),
				boost::bind(&SslClient::handle_read_content, this,
						boost::asio::placeholders::error));
	} else {
		BOOST_LOG_TRIVIAL(error)<< "Error: " << err << "\n";
	}
}

void SslClient::handle_read_content(const boost::system::error_code& err) {
	if (!err) {
		// Write all of the data that has been read so far.
		std::cout << &itsResponse;

		// Continue reading remaining data until EOF.
		boost::asio::async_read(itsSocket, itsResponse,
				boost::asio::transfer_at_least(1),
				boost::bind(&SslClient::handle_read_content, this,
						boost::asio::placeholders::error));
	} else if (err != boost::asio::error::eof) {
		BOOST_LOG_TRIVIAL(error)<<"Error: " << err << "\n";
	}
}

}
/* namespace trihlav */
