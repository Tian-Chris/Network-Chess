#include "client.h"
#include <iostream>
#include <fstream>

Client::Client() {
}

Client::~Client() {
    disconnect();
}

bool Client::connect(const std::string& host, const short port) {
    try {
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

        connection = std::make_unique<Connection>(io_context, asio::ip::tcp::socket(io_context), inputMessages);
        connection->connect(endpoints);

        myThread = std::thread([this]() { io_context.run(); });
    }
    catch (std::exception& e) {
        std::cerr << "Client Exception: " << e.what() << "\n";
        return false;
    }
    return true;
}

void Client::disconnect() {
    if (isConnected()) {
        connection->disconnect();
    }

    io_context.stop();
    // Join the thread if it's running
    if (myThread.joinable()) {
        myThread.join();
    }

    // Destroy the connection object
    connection.release();
}

bool Client::isConnected() {
    if (connection)
        return connection->isConnected();
    else
        return false;
}

void Client::Send(const Message& message) {
    if (isConnected()) {
        connection->send(message);
    }
}

tsqueue& Client::incoming() {
    return inputMessages;
}
