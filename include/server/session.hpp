#pragma once

#include <boost/asio.hpp>
#include <memory>

class Server;

class Session : public std::enable_shared_from_this<Session> 
{
public:
    Session(boost::asio::ip::tcp::socket socket, Server& server);

    void start();
    void send(const std::string& message);

private:
    void readLoop();

private:
    boost::asio::ip::tcp::socket socket_;
    Server& server_;
};