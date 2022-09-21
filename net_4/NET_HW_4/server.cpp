#include "server.hpp"

#include <vector>
#include <functional>
#include <thread>


// В конструкторе инициализируется акцептор, начинается прослушивание TCP порта.
TcpServer::TcpServer(boost::asio::io_context& io_context, size_t thread_pool_size) :
    io_context_(io_context), thread_pool_size_(thread_pool_size),
    acceptor_(io_context, tcp::endpoint(tcp::v4(), echo_port)) {
    boost::asio::ip::tcp::resolver resolver(io_context);
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.listen();
    start_accept();
}

void TcpServer::run() {
    std::vector<boost::shared_ptr<std::thread>> threads;

    for(size_t i = 0; i < thread_pool_size_; ++i) {
        boost::shared_ptr<std::thread> thread(new std::thread(
                  boost::bind(&boost::asio::io_context::run, &io_context_)));
            threads.push_back(thread);
    }

    for (auto th : threads) {
        th->join();
    }
}

// Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`, при соединении.
void TcpServer::start_accept() {
    TcpConnection::pointer new_connection = TcpConnection::create(io_context_);

    acceptor_.async_accept(new_connection->socket(),
                           [this, new_connection] (const boost::system::error_code& error) {
        this->handle_accept(new_connection, error);
    }
    );
}

// Метод handle_accept() вызывается, когда асинхронный accept, инициированный в start_accept() завершается.
// Она выполняет обработку запроса клиента и запуск нового акцептора.
void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error) {
    if (!error) {
        new_connection->start();
    }

    start_accept();
}
