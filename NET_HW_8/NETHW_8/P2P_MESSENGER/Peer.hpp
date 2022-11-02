//
// Created by ionian_caster on 02/11/22.
//

#pragma once

#include <iostream>
#include <string>

#include <boost/asio.hpp>

constexpr uint16_t multicast_port = 30000;

class Peer {
public:
    Peer(boost::asio::io_context& io_context, const boost::asio::ip::address& room, const std::string& name);

    void do_receive();
    void do_send();

private:
    constexpr static size_t maximum_size_ = 1024;
    std::array<char, maximum_size_> buffer_;
    std::string name_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::asio::ip::udp::endpoint multicast_endpoint_;
};