#pragma once

#include <ctime>
#include <iostream>
#include "TcpConnection.hpp"

class TcpServer : public boost::enable_shared_from_this<TcpServer> {
public:
    TcpServer(boost::asio::io_context& io_context, size_t thread_pool_size);
    void start_accept();

    void run();
private:
    void handle_accept(TcpConnection::pointer new_connection,
          const boost::system::error_code& error);

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;
    static constexpr int echo_port = 1300;
    size_t thread_pool_size_;
};

