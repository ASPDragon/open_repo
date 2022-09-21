#include "TcpConnection.hpp"
#include <ctime>

std::string make_daytime_string() {
    using namespace std; // time_t, time и ctime;
    time_t now = time(0);
    return ctime(&now);
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_context& io_context){
    return pointer(new TcpConnection(io_context));
}

void TcpConnection::start()
{
    message_ = "Processing of client's requests\r\nBoost Asio Server example\r\n\r\n" + make_daytime_string();
    auto s = shared_from_this();

    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                             [s](const boost::system::error_code& error, size_t bytes_transferred) {
        s->handle_write(error, bytes_transferred);
    });
}

TcpConnection::TcpConnection(boost::asio::io_context& io_context)
    : socket_(io_context) {}
