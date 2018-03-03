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

#include "trihlavHttpClient.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>

#include "trihlavLib/trihlavConstants.hpp"

using boost::asio::ip::tcp;

using std::string;
using std::ostream;
using boost::lexical_cast;
using std::string;
using boost::asio::ssl::context;
using boost::asio::io_service;

namespace trihlav {

    static const string K_HTTP("http");
    static const string K_HTTPS("https");
    static const string K_DIV("://");

    HttpClient::~HttpClient() {
        // TODO Auto-generated destructor stub
    }

    void HttpClient::parseModeHostAndPort(const string &pServer) {
        size_t myIt = pServer.find(K_HTTP + K_DIV);
        if (myIt == -1) {
            myIt = pServer.find(K_HTTPS + K_DIV);
            if (myIt == -1) {
                throw std::invalid_argument(
                        "\"" + pServer + "\" does not contain a "
                                "valid protocoll (" + K_HTTP + K_DIV + " or "
                        + K_HTTPS + K_DIV + ".");
            } else {
                m_Mode = HTTPS;
                BOOST_LOG_TRIVIAL(debug) << "mode \"" << K_HTTPS << "\"";
            }
        } else {
            m_Mode = HTTP;
            BOOST_LOG_TRIVIAL(debug) << "mode \"" << K_HTTP << "\"";
        }
        myIt = pServer.find("://");
        const size_t myIt3 = myIt + 3;
        if (myIt3 >= pServer.size()) {
            throw std::invalid_argument(
                    "\"" + pServer + "\" is too short it does not contain a valid "
                            "server definition.");
        }
        const string myServer{pServer.substr(myIt3, pServer.size())};
        BOOST_LOG_TRIVIAL(debug) << "server and port " << myServer;
        myIt = myServer.find_first_of(':');
        if (myIt == -1) {
            m_Server = myServer;
            m_Port = "";
        } else {
            m_Server = myServer.substr(0, myIt);
            if (++myIt < myServer.size()) {
                m_Port = myServer.substr(myIt, myServer.size());
            } else {
                m_Port = "";
            }
        }
        BOOST_LOG_TRIVIAL(debug) << "server \"" << m_Server << "\" port \""
                                 << m_Port << "\"";
    }

/**
 *  TODO: URL encoding
 */
    HttpClient::HttpClient(io_service &io_service, context &context,
                           const string &pServer, const string &pUsername,
                           const Passwords &pPasswords) :
            m_Resolver(io_service), m_SslSocket(io_service, context), m_HttpSocket(
            io_service) {
        parseModeHostAndPort(pServer);
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        std::ostream request_stream(&m_Request);
        string myUrl{K_AUTH_URL + "?" + K_USER_NM + "=" + pUsername};
        const string K_SP("&" + K_PSWD + "=");
        for (auto myPswdPtr = pPasswords.begin(); //
             myPswdPtr != pPasswords.end(); ++myPswdPtr) {
            myUrl += (K_SP + *myPswdPtr);
        }
        BOOST_LOG_TRIVIAL(debug) << myUrl;
        request_stream << "GET " << myUrl << " HTTP/1.0\r\n";
        request_stream << "Host: " << m_Server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Start an asynchronous resolve to translate the server and service names
        // into a list of endpoints.
        BOOST_LOG_TRIVIAL(debug) << "Resolving " << m_Server;
        tcp::resolver::query query(m_Server,
                                   m_Port.empty() ? getProtocol() : m_Port);    ///"http" "https"
        m_Resolver.async_resolve(query,
                                 boost::bind(&HttpClient::handleResolve, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::iterator));
    }

    void HttpClient::handleResolve(const boost::system::error_code &err,
                                   tcp::resolver::iterator endpoint_iterator) {
        if (!err) {
            BOOST_LOG_TRIVIAL(info) << "Resolve OK";
            m_ResponseStr = "";
            m_SslSocket.set_verify_mode(boost::asio::ssl::verify_peer);
            m_SslSocket.set_verify_callback(
                    boost::bind(&HttpClient::verifyCertificate, this, _1, _2));

            if (getMode() == HTTPS) {
                boost::asio::async_connect(m_SslSocket.lowest_layer(), endpoint_iterator,
                                           boost::bind(&HttpClient::handleConnect, this,
                                                       boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_connect(m_HttpSocket, endpoint_iterator,
                                           boost::bind(&HttpClient::handleConnect, this,
                                                       boost::asio::placeholders::error));
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error resolve: " << err.message();
        }
    }

    bool HttpClient::verifyCertificate(bool preverified,
                                       boost::asio::ssl::verify_context &ctx) {
        // The verify callback can be used to check whether the certificate that is
        // being presented is valid for the peer. For example, RFC 2818 describes
        // the steps involved in doing this for HTTPS. Consult the OpenSSL
        // documentation for more details. Note that the callback is called once
        // for each certificate in the certificate chain, starting from the root
        // certificate authority.

        // In this example we will simply print the certificate's subject name.
        char subject_name[256];
        X509 *cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
        BOOST_LOG_TRIVIAL(info) << "Verifying " << subject_name;

        return preverified;
    }

    void HttpClient::handleConnect(const boost::system::error_code &err) {
        if (!err) {
            BOOST_LOG_TRIVIAL(info) << "Connect OK ";
            if (getMode() == HTTPS) {
                m_SslSocket.async_handshake(boost::asio::ssl::stream_base::client,
                                            boost::bind(&HttpClient::handleHandshake, this,
                                                        boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_write(m_HttpSocket, m_Request,
                                         boost::bind(&HttpClient::handleWriteRequest, this,
                                                     boost::asio::placeholders::error));
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Connect failed: " << err.message();
        }
    }

    void HttpClient::handleHandshake(const boost::system::error_code &error) {
        if (!error) {
            BOOST_LOG_TRIVIAL(info) << "Handshake OK ";
            BOOST_LOG_TRIVIAL(debug) << "Request: ";
            const char *header = boost::asio::buffer_cast<const char *>(
                    m_Request.data());
            BOOST_LOG_TRIVIAL(debug) << header;

            // The handshake was successful. Send the request.
            boost::asio::async_write(m_SslSocket, m_Request,
                                     boost::bind(&HttpClient::handleWriteRequest, this,
                                                 boost::asio::placeholders::error));
        } else {
            BOOST_LOG_TRIVIAL(error) << "Handshake failed: " << error.message();
        }
    }

    void HttpClient::handleWriteRequest(const boost::system::error_code &err) {
        if (!err) {
            // Read the response status line. The m_Response streambuf will
            // automatically grow to accommodate the entire line. The growth may be
            // limited by passing a maximum size to the streambuf constructor.
            if (getMode() == HTTPS) {
                boost::asio::async_read_until(m_SslSocket, m_Response, "\r\n",
                                              boost::bind(&HttpClient::handleReadStatusLine, this,
                                                          boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_read_until(m_HttpSocket, m_Response, "\r\n",
                                              boost::bind(&HttpClient::handleReadStatusLine, this,
                                                          boost::asio::placeholders::error));
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error write req: " << err.message();
        }
    }

    void HttpClient::handleReadStatusLine(const boost::system::error_code &err) {
        if (!err) {
            // Check that response is OK.
            std::istream response_stream(&m_Response);
            std::string http_version;
            response_stream >> http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
                std::cout << "Invalid response";
                return;
            }
            if (status_code != 200) {
                BOOST_LOG_TRIVIAL(error) << "Response returned with status code ";
                BOOST_LOG_TRIVIAL(error) << status_code;
                return;
            }
            BOOST_LOG_TRIVIAL(error) << status_code;

            // Read the response headers, which are terminated by a blank line.
            if (getMode() == HTTPS) {
                boost::asio::async_read_until(m_SslSocket, m_Response, "\r\n\r\n",
                                              boost::bind(&HttpClient::handleReadHeaders, this,
                                                          boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_read_until(m_HttpSocket, m_Response,
                                              "\r\n\r\n",
                                              boost::bind(&HttpClient::handleReadHeaders, this,
                                                          boost::asio::placeholders::error));
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error reading status line: " << err.message();
        }
    }

    void HttpClient::handleReadHeaders(const boost::system::error_code &err) {
        if (!err) {
            // Process the response headers.
            std::istream response_stream(&m_Response);
            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
                BOOST_LOG_TRIVIAL(debug) << header;

            // Write whatever content we already have to output.
            if (m_Response.size() > 0)
                if (foundResponseStr())
                    return;

            // Start reading remaining data until EOF.
            if (getMode() == HTTPS) {
                boost::asio::async_read(m_SslSocket, m_Response,
                                        boost::asio::transfer_at_least(1),
                                        boost::bind(&HttpClient::handleReadContent, this,
                                                    boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_read(m_HttpSocket, m_Response,
                                        boost::asio::transfer_at_least(1),
                                        boost::bind(&HttpClient::handleReadContent, this,
                                                    boost::asio::placeholders::error));
            }
        } else {
            BOOST_LOG_TRIVIAL(error) << "Error reading headers: " << err;
        }
    }

    bool HttpClient::foundResponseStr() {
        // Write all of the data that has been read so far.
        m_ResponseStr += string {buffers_begin(m_Response.data()), buffers_end(
                m_Response.data())};
        BOOST_LOG_TRIVIAL(debug) << m_ResponseStr;
        if (m_ResponseStr.find("Fail!") != -1) {
            m_AuthOk = false;
            return true;
        } else if (m_ResponseStr.find("ok!") != -1) {
            m_AuthOk = true;
            return true;
        }
        return false;
    }

    void HttpClient::handleReadContent(const boost::system::error_code &err) {
        if (!err) {
            // Write all of the data that has been read so far.
            if (foundResponseStr()) return;
            // Continue reading remaining data until EOF.
            if (getMode() == HTTPS) {
                boost::asio::async_read(m_SslSocket, m_Response,
                                        boost::asio::transfer_at_least(1),
                                        boost::bind(&HttpClient::handleReadContent, this,
                                                    boost::asio::placeholders::error));
            } else if (getMode() == HTTP) {
                boost::asio::async_read(m_HttpSocket, m_Response,
                                        boost::asio::transfer_at_least(1),
                                        boost::bind(&HttpClient::handleReadContent, this,
                                                    boost::asio::placeholders::error));
            }
        } else if (err != boost::asio::error::eof) {
            BOOST_LOG_TRIVIAL(error) << "Error reading content: " << err;
        }
    }

    const std::string &HttpClient::getProtocol() const {
        if (m_Mode == HTTP)
            return K_HTTP;
        if (m_Mode == HTTPS)
            return K_HTTPS;
        BOOST_LOG_TRIVIAL(error) << "Unknown protocol " << m_Mode
                                 << " returning " + K_HTTPS;
        return K_HTTPS;
    }

}
/* namespace trihlav */
