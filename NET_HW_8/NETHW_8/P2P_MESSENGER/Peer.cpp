//
// Created by ionian_caster on 02/11/22.
//

#include "Peer.hpp"

Peer::Peer(boost::asio::io_context& io_context, const boost::asio::ip::address& room, const std::string& name)
        : socket_(io_context), multicast_endpoint_(room, multicast_port), name_(name)
{
    boost::asio::ip::udp::endpoint listen_endpoint(room, multicast_port);
    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);

    socket_.set_option(boost::asio::ip::multicast::join_group(room.to_v4()));

    auto welcome_message = std::string(name_ + " connected to the chat!");

    socket_.async_send_to(boost::asio::buffer(welcome_message, welcome_message.size()), multicast_endpoint_,
                          [](const boost::system::error_code& error, size_t bytes_transfered) {
        if (!error)
            std::cout << "Entered chat room successfully!" << std::endl;
        else
            std::cerr << error.what() << ", " << bytes_transfered << " transferred!" << std::endl;
    });
}

void Peer::do_receive(){
    socket_.async_receive_from(boost::asio::buffer(buffer_), remote_endpoint_,
                               [this](const boost::system::error_code& error_code, std::size_t bytes_received){
                                   if (!error_code.failed() && bytes_received > 0){
                                       auto received_message_string = std::string(buffer_.begin(),
                                                                                  buffer_.begin() + bytes_received);
                                       if (received_message_string.find(name_) != 0){
                                           std::cout.write(buffer_.data(), bytes_received);
                                           std::cout << std::flush;
                                       }
                                       do_receive();
                                   }
                               });
}

void Peer::do_send(){
    std::string name = name_;
    std::string message;
    std::getline(std::cin, message);
    std::string buffer = name.append(": " + message);
    socket_.async_send_to(boost::asio::buffer(buffer, maximum_size_), multicast_endpoint_,
                          [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
                              std::cout << "You: " << message << std::endl;
                              do_send();
                          });
}