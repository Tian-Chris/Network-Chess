#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include "message.h"
#include "connection.h"  // Include the header file for the Connection class
#include "tsqueue.h"     // Include the header file for the tsqueue class

using asio::ip::tcp;

class Server {
public:
    // Constructor that initializes the acceptor with the given port
    Server(unsigned short port);
    
    // Destructor
    ~Server();
    
    // Starts the server
    bool Start();
    
    // Stops the server
    void Stop();
    
    // Accepts incoming client connections
    void do_accept();

    // Sends a message to a specific client
    void sendMessage(std::shared_ptr<Connection> client, const Message& myMessage);
    
    // Input message queue
    tsqueue inputMessages;
    
    // List of active client connections
    std::deque<std::shared_ptr<Connection>> Connections;

private:
    asio::io_context io_context;  // IO context for async operations
    tcp::acceptor acceptor;       // Accepts incoming client connections
    std::thread myThread;         // IO context runs in a separate thread
};

#endif // SERVER_H
