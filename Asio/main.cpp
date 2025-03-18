#define ASIO_STANDALONE
#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <string>
#include <array>

std::vector<char> vBuffer(20 * 1024);

void GradSomeData(asio::ip::tcp::socket& socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), 
    [&](std::error_code ec, std::size_t length)
    {
        if(!ec)
        {
            std::cout << "\n\nRead " << length << " bytes\n\n";
            for(int i = 0; i < length; i++)
            {
                std::cout << vBuffer[i];
            }
            GradSomeData(socket);
        }
    }
    );
}

int main() {
    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&]() { context.run(); });
    asio::ip::tcp::resolver resolver(context);
    auto endpoints = resolver.resolve("example.com", "80");

    asio::ip::tcp::socket socket(context);
    asio::connect(socket, endpoints);
    
    if(!ec)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to address: \n" << ec.message() << std::endl;
        return 1;
    }

    if(socket.is_open())
    {
        GradSomeData(socket);
        std::string sRequest = "GET / HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Connection: close\r\n"
        "\r\n";
        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20000ms);
    }

    return 0;

}
