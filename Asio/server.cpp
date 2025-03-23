#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>

using asio::ip::tcp;

class Server {
public:

    Server(unsigned short port) : acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
        Start();
    }

    ~Server() {
        Stop();
    }

    bool Start() //starts 
    {
        try
        {
            do_accept();
            myThread = std::thread([this]() { io_context.run(); });
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }
        return true;
    }

    void Stop() //stops
    {
        io_context.stop();
        if(myThread.joinable())
        {
            myThread.join();
        }
    }

    void do_accept() // checks for socket when found makes a connection and passes socket to that connection so that it can be handled async adds connection to a deque of connections
    {
        acceptor.async_accept(
            [this](std::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::cout << "Client connected!" << std::endl;
                    std::shared_ptr<connection> connection = std::make_shared<connection>(connection::owner::server, io_context, std::move(socket), inputMessages);
                    connections.push_back(std::move(connection));
                }
                else
                {
                    std::cout << "SERVER: Connection Error: " << ec.message() << "\n";
                }
                do_accept();
            });
    }

    void sendMessage(std::shared_ptr<connection> client, const Message& myMessage) 
    {
        if (client && client->IsConnected())
        {
            client->Send(myMessage);
        }
        else
        {
            std::cout << "tried to send to disconnected client" << std::endl;
        }
    }

protected:
    asio::io_context io_context;
    tcp::acceptor acceptor;
    std::thread myThread; //needed to launch io_context in its own thread since io_context is blocking

    //build my own thread safe queue that takes message
    //Message will be an int for size and char for info
    tsqueue<owned_message<Message>> inputMessages;

    //a deque of pointers toward connections need to build connection.
    std::deque<std::shared_ptr<Connection>> Connections;

};

int main() {
    Server myServer(12345);
    return 0;
}