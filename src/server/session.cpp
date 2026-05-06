#include "server/session.hpp"
#include "server/server.hpp"
#include <iostream>

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket, Server& server)
    : socket_(std::move(socket)), server_(server)
    {}

void Session::start()
{
    std::thread(&Session::readLoop, shared_from_this()).detach();
}

void Session::readLoop()
{
    try
    {
        char data[1024];

        while (true)
        {
            boost::system::error_code ec;
            size_t length = socket_.read_some(boost::asio::buffer(data), ec);

            if (ec == boost::asio::error::eof)
            {
                std::cout << "[Session] Client disconnected\n";
                break;
            }
            else if (ec) 
            {
                throw boost::system::system_error(ec);
            }

            std::string message(data, length);
            std::cout << "[Session] Received: " << message << "\n";

            server_.broadcast(message);
        }
    }
    catch (std::exception& e) 
    {
        std::cerr << "[Session] Error: " << e.what() << "\n";
    }

    server_.removeSession(shared_from_this());
}

void Session::send(const std::string& message) 
{
    boost::asio::write(socket_, boost::asio::buffer(message));
}