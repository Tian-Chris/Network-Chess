#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include "message.h"
#include "connection.cpp"
#include "tsqueue.cpp"

using asio::ip::tcp;

class client {
protected:
    asio::io_context io_context;
    std::thread myThread;
    std::unique_ptr<Connection> connection;
    
private:
    //messages from the server
    tsqueue inputMessage;

public:
    client() {};
    ~client() {
        disconnect();
    }

    bool connect(const std::string& host, const short port)
    {
        try
        {
            asio::ip::tcp::resolver resolver(io_context);
            asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

            connection = std::make_unique<Connection>(io_context, asio::ip::tcp::socket(io_context), inputMessage);
            
            connection->connect(endpoints);

            myThread = std::thread([this]() { io_context.run(); });
        }
        catch (std::exception& e)
        {
            std::cerr << "Client Exception: " << e.what() << "\n";
            return false;
        }
        return true;
    }

    void disconnect()
    {
        if(isConnected())
        {
            connection->disconnect();
        }

        io_context.stop();
        // ...and its thread
        if (myThread.joinable())
            myThread.join();

        // Destroy the connection object
        connection.release();
    }
    bool isConnected()
    {
        if (connection)
            return connection->isConnected();
        else
            return false;
    }

    void Send(const Message& message)
    {
        if (isConnected())
        {
            connection->send(message);
        }
    }

    tsqueue& incoming()
    { 
        return inputMessage;
    }
};

int main() {
    client myClient;
    myClient.connect("127.0.0.1", 12345);
    if (!myClient.isConnected()) {
        std::cerr << "Connection failed!" << std::endl;
        return -1;  
    }
    std::cout << "Connected!" << std::endl;

    Message myMessage;
    std::vector<char> myVect = {'h', 'e', 'l', 'l', 'o'};
    myMessage.setMessage(myVect);
    myMessage.setSize(5);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    myClient.Send(myMessage);
    std::cout << "message sent" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    myClient.disconnect();
    std::cout << "Disconnected!" << std::endl;

    return 0;
}