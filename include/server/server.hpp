// include/server/server.hpp
#pragma once

#include <boost/asio.hpp>
#include <vector>
#include <memory>
#include <mutex>

class Session;

class Server 
{
public:
    Server(boost::asio::io_context& io_context, int port);
    void start();
    void stop();

    void broadcast(const std::string& message);
    void addSession(std::shared_ptr<Session> session);
    void removeSession(std::shared_ptr<Session> session);

private:
    // void handleClient(boost::asio::ip::tcp::socket socket);
    std::vector<std::shared_ptr<Session>> sessions_;
    std::mutex sessions_mutex_;

private:
    bool running_ = true;
    boost::asio::ip::tcp::acceptor acceptor_;
};