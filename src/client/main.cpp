#include "client/client.hpp"
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;

    Client client(io_context, "127.0.0.1", 8080);
    client.start();

    return 0;
}