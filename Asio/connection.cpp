#include "connection.h"
#include <asio.hpp>
#include <iostream>

Connection::Connection(asio::io_context& inputContext, asio::ip::tcp::socket inputSocket, tsqueue& queue)
    : io_context(inputContext), socket(std::move(inputSocket)), inputQueue(queue)
{
}

void Connection::connect(const asio::ip::tcp::resolver::results_type& endpoints) {
    asio::async_connect(socket, endpoints,
        [this](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
            if (!ec) {
                std::cout << "read:" << std::endl;
                read();
            }
        });
}

void Connection::disconnect() {
    if (isConnected()) {
        asio::post(io_context, [this]() { socket.close(); });
    }
}

bool Connection::isConnected() const {
    return socket.is_open();
}

void Connection::send(const Message& message) {
    asio::post(io_context,
        [this, message]() {
            if (outputQueue.empty()) {
                outputQueue.push_back(message);
                write();
            } else {
                outputQueue.push_back(message);
            }
        });
}

void Connection::write() {
    // Write size
    asio::async_write(socket, asio::buffer(&outputQueue.front().size, sizeof(outputQueue.front().size)),
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                // Write message data
                asio::async_write(socket, asio::buffer(&outputQueue.front().type, sizeof(outputQueue.front().type)),
                [this](std::error_code ec, std::size_t length) {
                    if (!ec) {
                    asio::async_write(socket, asio::buffer(outputQueue.front().message.data(), outputQueue.front().message.size()),
                        [this](std::error_code ec, std::size_t length) {
                            if (!ec) {
                                outputQueue.pop_front();
                                if (!outputQueue.empty()) {
                                    write();
                                }
                            } else {
                                    std::cout << "Connection: write message failed" << std::endl;
                                }
                        });
                    } else {
                        std::cout << "Connection: write type failed" << std::endl;
                        }
                });
            } else {
                std::cout << "Connection: write size failed" << std::endl;
            }
        });
}

void Connection::read() {
    asio::async_read(socket, asio::buffer(&temp.size, sizeof(temp.size)),
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                asio::async_read(socket, asio::buffer(&temp.type, sizeof(temp.type)),
                    [this](std::error_code ec, std::size_t length) {
                        if (!ec) {
                            temp.message.resize(temp.size);
                            asio::async_read(socket, asio::buffer(temp.message.data(), temp.size),
                                [this](std::error_code ec, std::size_t length) {
                                    if (!ec) {
                                        inputQueue.push_back(temp);
                                        read();
                                    } else {
                                        std::cout << "Connection: read message failed" << std::endl;
                                    }
                                });
                        } else {
                            std::cout << "Connection: read type failed" << std::endl;
                            std::cout << ec.message() << std::endl;
                        }
                        });
            } else {
                std::cout << "Connection: read size failed" << std::endl;
                std::cout << ec.message() << std::endl;
            }
        });
}
