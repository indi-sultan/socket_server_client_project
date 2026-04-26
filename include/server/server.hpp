// include/server/server.hpp
#pragma once

#include <boost/asio.hpp>

class Server {
public:
    Server(boost::asio::io_context& io_context, int port);
    void start();

private:
    void handleClient(boost::asio::ip::tcp::socket socket);

private:
    boost::asio::ip::tcp::acceptor acceptor_;
};