#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include "server/server.hpp"

using namespace std::chrono_literals;
using boost::asio::ip::tcp;

TEST(EchoTest, BasicSendReceive) 
{
    boost::asio::io_context io_context;

    // Start server in background thread
    Server server(io_context, 9090);

    std::thread server_thread([&]() {
        server.start();
    });

    // Give server time to start
    std::this_thread::sleep_for(100ms);

    // Create client manually (no Client class needed for test)
    tcp::socket socket(io_context);
    tcp::resolver resolver(io_context);

    auto endpoints = resolver.resolve("127.0.0.1", "9090");
    boost::asio::connect(socket, endpoints);

    std::string message = "hello";

    boost::asio::write(socket, boost::asio::buffer(message));

    char reply[1024];
    size_t reply_length = socket.read_some(boost::asio::buffer(reply));

    std::string response(reply, reply_length);

    EXPECT_EQ(response, message);

    // Cleanup
    socket.close();
    server.stop();
    server_thread.join();
}