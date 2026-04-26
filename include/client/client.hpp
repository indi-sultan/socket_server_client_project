// include/client/client.hpp
#pragma once

#include <boost/asio.hpp>
#include <string>

class Client {
public:
    Client(boost::asio::io_context& io_context,
           const std::string& host,
           int port);

    void start();

private:
    boost::asio::ip::tcp::socket socket_;
};