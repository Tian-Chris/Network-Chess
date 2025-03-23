#include <asio.hpp>
#include <iostream>

using asio::ip::tcp;

void client() {
    try {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::query query("127.0.0.1", "12345");  // Server IP and port
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_context);
        asio::connect(socket, endpoint_iterator);

        asio::streambuf response;
        asio::read_until(socket, response, "\0");  // Read until the null terminator

        std::istream response_stream(&response);
        std::string response_message((std::istreambuf_iterator<char>(response_stream)),
                                     std::istreambuf_iterator<char>());

        std::cout << "Response from server: " << response_message << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    client();
    return 0;
}