#ifndef CLIENT_H
#define CLIENT_H

#include <asio.hpp>
#include <thread>
#include <deque>
#include "message.h"
#include "connection.h"  // Assuming connection class is declared in connection.h
#include "tsqueue.h"     // Assuming tsqueue is declared in tsqueue.h

using asio::ip::tcp;

class client {
protected:
    asio::io_context io_context;
    std::thread myThread;
    std::unique_ptr<Connection> connection;

public:
    // Message queue from the server
    tsqueue inputMessages;

public:
    client();
    ~client();

    bool connect(const std::string& host, const short port);
    void disconnect();
    bool isConnected();
    void Send(const Message& message);
    tsqueue& incoming();
};

#endif // CLIENT_H