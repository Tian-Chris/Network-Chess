#include "server.h" // Include the header file for the Server class
#include <iostream>
#include <thread>
#include <asio.hpp>

using asio::ip::tcp;

Server::Server(unsigned short port) : acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
}

Server::~Server() {
    Stop();
}

bool Server::Start() {
    try {
        do_accept();
        myThread = std::thread([this]() { io_context.run(); });
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void Server::Stop() {
    io_context.stop();
    if (myThread.joinable()) {
        myThread.join();
    }
}

void Server::do_accept() {
    acceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::cout << "Client connected!" << std::endl;
                std::shared_ptr<Connection> connection = std::make_shared<Connection>(io_context, std::move(socket), inputMessages);
                Connections.push_back(std::move(connection));
                Connections.back()->read();
            } else {
                std::cout << "SERVER: Connection Error: " << ec.message() << "\n";
            }
            do_accept();
        });
}

void Server::sendMessage(std::shared_ptr<Connection> client, const Message& myMessage) {
    if (client && client->isConnected()) {
        client->send(myMessage);
    } else {
        std::cout << "tried to send to disconnected client" << std::endl;
    }
}