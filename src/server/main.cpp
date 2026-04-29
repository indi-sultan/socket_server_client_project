#include "server/server.hpp"
#include <boost/asio.hpp>

int main() {
    boost::asio::io_context io_context;

    Server server(io_context, 8080);
    server.start();

    return 0;
}