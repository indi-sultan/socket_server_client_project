// include/server/server.hpp
#pragma once

#include <boost/asio.hpp>

class Server {
public:
    Server(boost::asio::io_context& io_context, int port);
    void start();
    void stop();

private:
    void handleClient(boost::asio::ip::tcp::socket socket);

private:
    bool running_ = true;
    boost::asio::ip::tcp::acceptor acceptor_;
};