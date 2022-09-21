#include <iostream>
#include "server.hpp"
#include <memory>

int main()
{
    try
    {
        // io_context предоставляет службы ввода-вывода, которые будет использовать сервер, такие как сокеты.
        boost::asio::io_context io_context;
        auto server = std::make_shared<TcpServer>(io_context, std::thread::hardware_concurrency());

        // Запуск асинхронных операций.
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
