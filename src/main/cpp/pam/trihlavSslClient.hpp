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

#ifndef TRIHLAV_SSL_CLIENT_HPP_
#define TRIHLAV_SSL_CLIENT_HPP_

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

namespace trihlav {

class SslClient {
public:
	SslClient(boost::asio::io_service& io_service,
			boost::asio::ssl::context& context, const std::string& server,
			const std::string& path);
	virtual ~SslClient();

private:
	  void handle_resolve(const boost::system::error_code& err,
	                      boost::asio::ip::tcp::resolver::iterator endpoint_iterator);
	  bool verify_certificate(bool preverified,
	                          boost::asio::ssl::verify_context& ctx);
	  void handle_connect(const boost::system::error_code& err);
	  void handle_handshake(const boost::system::error_code& error);
	  void handle_write_request(const boost::system::error_code& err);
	  void handle_read_status_line(const boost::system::error_code& err);
	  void handle_read_headers(const boost::system::error_code& err);
	  void handle_read_content(const boost::system::error_code& err);

	  boost::asio::ip::tcp::resolver itsResolver;
	  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> itsSocket;
	  boost::asio::streambuf itsRequest;
	  boost::asio::streambuf itsResponse;

};

} /* namespace trihlav */

#endif /* TRIHLAV_SSL_CLIENT_HPP_ */
