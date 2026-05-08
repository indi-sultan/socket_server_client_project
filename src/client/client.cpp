// src/client/client.cpp

#include "client/client.hpp"
#include <iostream>

using boost::asio::ip::tcp;

Client::Client(boost::asio::io_context& io_context,
               const std::string& host,
               int port)
    : socket_(io_context) 
{

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));

    boost::asio::connect(socket_, endpoints);
}

// void Client::start() 
// {
//     std::cout << "[Client] Connected to server\n";

//     while (true) 
//     {
//         std::string message;
//         std::getline(std::cin, message);

//         if (message == "exit") break;

//         boost::asio::write(socket_, boost::asio::buffer(message));

//         char reply[1024];
//         size_t reply_length =
//             socket_.read_some(boost::asio::buffer(reply));

//         std::cout << "[Server Reply]: "
//                   << std::string(reply, reply_length) << "\n";
//     }
// }


void Client::start() 
{
    std::cout << "[Client] Connected to server\n";

    // Thread for receiving messages
    std::thread receiver([this]() 
    {
        while (true) 
        {
            try 
            {
                char data[1024];

                boost::system::error_code ec;
                size_t length =
                    socket_.read_some(boost::asio::buffer(data), ec);

                if (ec) 
                {
                    std::cout << "[Client] Disconnected from server\n";
                    break;
                }

                std::cout << "\n[Message] "
                          << std::string(data, length)
                          << "\n> ";
                std::cout.flush();

            } 
            catch (std::exception& e) 
            {
                std::cerr << "[Client] Receive error: "
                          << e.what() << "\n";
                break;
            }
        }
    });

    // Main thread handles sending
    while (true) 
    {
        std::cout << "> ";

        std::string message;
        std::getline(std::cin, message);

        if (message == "exit") 
        {
            break;
        }

        boost::asio::write(
            socket_,
            boost::asio::buffer(message)
        );
    }

    socket_.close();
    receiver.join();
}