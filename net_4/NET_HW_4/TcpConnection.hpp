#pragma once

#include <string>

#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context);
    tcp::socket& socket() { return socket_; }
    void start();

private:
    TcpConnection(boost::asio::io_context& io_context);

    void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes transferred*/) {}
    tcp::socket socket_;
    std::string message_;
};

