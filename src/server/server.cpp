// src/server/server.cpp

#include "server/server.hpp"
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, int port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    std::cout << "[Server] Listening...\n";

    while (running_) 
    {
        boost::asio::ip::tcp::socket socket(acceptor_.get_executor());

        acceptor_.accept(socket);
        std::cout << "[Server] Client connected\n";

        // Handle each client in separate thread (temporary for Stage 1)
        std::thread(&Server::handleClient, this, std::move(socket)).detach();
    }
}

void Server::stop()
{
    running_ = false;
    acceptor_.close();
}

void Server::handleClient(tcp::socket socket) {
    try {
        char data[1024];

        while (true) {
            boost::system::error_code ec;
            size_t length = socket.read_some(boost::asio::buffer(data), ec);

            if (ec == boost::asio::error::eof) {
                std::cout << "[Server] Client disconnected\n";
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            }

            std::cout << "[Server] Received: "
                      << std::string(data, length) << "\n";

            // Echo back
            boost::asio::write(socket, boost::asio::buffer(data, length));
        }
    } catch (std::exception& e) {
        std::cerr << "[Server] Error: " << e.what() << "\n";
    }
}