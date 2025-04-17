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
    Server(unsigned short port);
    ~Server();
    bool Start();
    void Stop();
    virtual void do_accept();
    void sendMessage(std::shared_ptr<Connection> client, const Message& myMessage);
    
    // Input  queue
    tsqueue inputMessages;
    
    // List of active client connections
    std::deque<std::shared_ptr<Connection>> Connections;

// private:
    asio::io_context io_context;  // IO context for async operations
    tcp::acceptor acceptor;       // Accepts incoming client connections
    std::thread myThread;         // IO context runs in a separate thread
};

#endif // SERVER_H
