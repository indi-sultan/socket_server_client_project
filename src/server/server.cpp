#include "server/server.hpp"
#include "server/session.hpp"
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, int port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() 
{
    std::cout << "[Server] Listening...\n";

    while (running_) 
    {
        tcp::socket socket(acceptor_.get_executor());
        
        boost::system::error_code ec;
        acceptor_.accept(socket, ec);

        if (ec)
        {
            if (running_)
            {
                std::cerr << "[Server] Accept error: " << ec.message() << "\n";
            }
            break;
        }
        std::cout << "[Server] Client connected\n";

        auto session = std::make_shared<Session>(std::move(socket), *this);
        addSession(session);
        session->start();
    }
}

void Server::stop()
{
    running_ = false;
    boost::system::error_code ec;
    acceptor_.close();
}

// void Server::handleClient(tcp::socket socket) {
//     try {
//         char data[1024];

//         while (true) {
//             boost::system::error_code ec;
//             size_t length = socket.read_some(boost::asio::buffer(data), ec);

//             if (ec == boost::asio::error::eof) {
//                 std::cout << "[Server] Client disconnected\n";
//                 break;
//             } else if (ec) {
//                 throw boost::system::system_error(ec);
//             }

//             std::cout << "[Server] Received: "
//                       << std::string(data, length) << "\n";

//             // Echo back
//             boost::asio::write(socket, boost::asio::buffer(data, length));
//         }
//     } catch (std::exception& e) {
//         std::cerr << "[Server] Error: " << e.what() << "\n";
//     }
// }

void Server::broadcast(const std::string& message) 
{
    std::lock_guard<std::mutex> lock(sessions_mutex_);

    for (auto& session : sessions_) 
    {
        session->send(message);
    }
}

void Server::addSession(std::shared_ptr<Session> session) 
{
    std::lock_guard<std::mutex> lock(sessions_mutex_);
    sessions_.push_back(session);
}

void Server::removeSession(std::shared_ptr<Session> session) 
{
    std::lock_guard<std::mutex> lock(sessions_mutex_);

    sessions_.erase(
        std::remove(sessions_.begin(), sessions_.end(), session),
        sessions_.end()
    );
}