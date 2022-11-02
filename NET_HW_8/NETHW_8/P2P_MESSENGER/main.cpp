//
// Created by ionian_caster on 02/11/22.
//

#include "Peer.hpp"

int main(int argc, char* argv[])
{
    boost::asio::thread_pool thread_pool(2);

    if(argc != 3){
        std::cerr << "Usage: ./P2P_MESSENGER <your_nickname> <multicast_address>" << std::endl;
        std::exit(1);
    }

    boost::asio::io_context io_context;
    boost::asio::ip::address chat_room(boost::asio::ip::make_address(argv[2]));
    Peer peer(io_context, chat_room, argv[1]);

    boost::asio::post(thread_pool, [&]{
        peer.do_receive();
        io_context.run();
    });
    boost::asio::post(thread_pool, [&]{
        peer.do_send();
        io_context.run();
    });
    thread_pool.join();

    return 0;
}