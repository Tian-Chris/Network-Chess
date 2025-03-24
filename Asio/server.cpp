#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include "message.h"
#include "connection.cpp"
#include "tsqueue.cpp"

using asio::ip::tcp;

class Server {
public:

    Server(unsigned short port) : acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) 
    {
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
                    std::shared_ptr<Connection> connection = std::make_shared<Connection>(io_context, std::move(socket), inputMessages);
                    Connections.push_back(std::move(connection));
                    Connections.back() -> read();
                }
                else
                {
                    std::cout << "SERVER: Connection Error: " << ec.message() << "\n";
                }
                do_accept();
            });
    }

    void sendMessage(std::shared_ptr<Connection> client, const Message& myMessage) 
    {
        if (client && client->isConnected())
        {
            client->send(myMessage);
        }
        else
        {
            std::cout << "tried to send to disconnected client" << std::endl;
        }
    }

//protected:
public:
    asio::io_context io_context;
    tcp::acceptor acceptor;
    std::thread myThread; //needed to launch io_context in its own thread since io_context is blocking

    //build my own thread safe queue that takes message
    //Message will be an int for size and char for info
    tsqueue inputMessages;

    //a deque of pointers toward connections need to build connection.
    std::deque<std::shared_ptr<Connection>> Connections;

};

using asio::ip::tcp;

int main() {
    Server myServer(12345);
    std::cout << "Server started on port 12345" << std::endl;
    myServer.Start();

    while(1)
    {
        //not working it seems
        if(!(myServer.inputMessages.empty()))
        {
            std::cout << "hello" << std::endl;
            std::cout << myServer.inputMessages.front().message[0] << std::endl;
            std::cout << myServer.inputMessages.front().message[1] << std::endl;
        }
    }
    return 0;
}