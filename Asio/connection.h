#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>
#include <vector>
#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include "message.h"
#include "tsqueue.h" // Include the header, not the .cpp file

class Connection : public std::enable_shared_from_this<Connection> {
public:
    asio::io_context& io_context;
    asio::ip::tcp::socket socket;

    // Parent object's queue
    tsqueue& inputQueue;
    
    // Queue for outputs
    tsqueue outputQueue;
    
    // Temporary message
    Message temp;

    // Constructor
    Connection(asio::io_context& inputContext, asio::ip::tcp::socket inputSocket, tsqueue& queue);

    // Used to connect to servers
    void connect(const asio::ip::tcp::resolver::results_type& endpoints);

    // Disconnect the connection
    void disconnect();

    // Check if connected
    bool isConnected() const;

    // Send message to the output queue
    void send(const Message& message);

    // Write data to the socket
    void write();

    // Read data from the socket
    void read();
};

#endif // CONNECTION_H
