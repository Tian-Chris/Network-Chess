#ifndef CONNECTION_H
#define CONNECTION_H
#include <memory>
#include <vector>
#include <asio.hpp>
#include <iostream>
#include <thread>
#include <deque>
#include "message.h"
#include "tsqueue.cpp"


class Connection : public std::enable_shared_from_this<Connection>{
public: 
    asio::io_context& io_context;
    asio::ip::tcp::socket socket;

    //parent object's queue
    tsqueue& inputQueue;
    //queue for outputs
    tsqueue outputQueue;
    //temp message
    Message temp;

    //constructor
    Connection(asio::io_context& inputContext, asio::ip::tcp::socket inputSocket, tsqueue& queue)
    : io_context(inputContext), socket(std::move(inputSocket)), inputQueue(queue)
    {
    }

    //used to connect to servers
    void connect(const asio::ip::tcp::resolver::results_type& endpoints)
    {
        asio::async_connect(socket, endpoints,
            [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
            {
                if (!ec)
                {
                    std::cout << "read:" << std::endl;
                    read();
                }
            });
    }

    void disconnect()
    {
        if(isConnected())
        {
            asio::post(io_context, [this]() { socket.close(); });
        }
    }

    bool isConnected() const
    {
        return socket.is_open();
    }

    //only writes if its empty else just adds to the queue since if the queue is full that must mean writing is occuring asynchronously
    void send(const Message& message)
        {
            asio::post(io_context,
                [this, message]()
                {
                    if (outputQueue.empty())
                    {
                        outputQueue.push_back(message);
                        write();
                    }
                    else
                    {
                        outputQueue.push_back(message);
                    }
                });
        }

    void write()
    {
        //finish this when fix tsqueue
        asio::async_write(socket, asio::buffer((&outputQueue.front().size), sizeof(outputQueue.front().size)),
            [this](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    //finish this when fix tsqueue
                    asio::async_write(socket, asio::buffer(outputQueue.front().message.data(), outputQueue.front().message.size()),
                    [this](std::error_code ec, std::size_t length)
                        {  
                            if(!ec)
                            {
                                outputQueue.pop_front();
                                if(!outputQueue.empty())
                                {
                                    write();
                                }
                            }
                            else
                            {
                                std::cout << "Connection: write message failed" << std::endl;
                            }
                        });
                }
                
                else
                {
                    std::cout << "Connection: write size failed" << std::endl;
                    socket.close();
                }
            });
    }

    void read() {
        asio::async_read(socket, asio::buffer(&temp.size, sizeof(temp.size)),
        [this](std::error_code ec, std::size_t length)
        {	
            if(!ec)
            {
                temp.message.resize(temp.size);
                std::cout << temp.size << std::endl;
                asio::async_read(socket, asio::buffer(temp.message.data(), temp.size),
                [this](std::error_code ec, std::size_t length)
                {	
                    if(!ec)
                    {
                        inputQueue.push_back(temp);
                        read();
                    }
                    else
                    {
                        std::cout << "Connection: read message failed" << std::endl;
                    }
                });

            }
            else
            {
                std::cout << "Connection: read size failed" << std::endl;
                std::cout << ec.message() << std::endl;
            }
        });
    }


};
#endif
