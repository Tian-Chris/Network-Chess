#include "client.h"
#include <iostream>
#include <fstream>

client::client() {
    // Constructor (empty here but could initialize members if needed)
}

client::~client() {
    disconnect();
}

bool client::connect(const std::string& host, const short port) {
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

void client::disconnect() {
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

bool client::isConnected() {
    if (connection)
        return connection->isConnected();
    else
        return false;
}

void client::Send(const Message& message) {
    if (isConnected()) {
        connection->send(message);
    }
}

tsqueue& client::incoming() {
    return inputMessages;
}


// int main() {
//     client myClient;
//     myClient.connect("127.0.0.1", 12345);
//     if (!myClient.isConnected()) {
//         std::cerr << "Connection failed!" << std::endl;
//         return -1;  
//     }
//     std::cout << "Connected!" << std::endl;

//     Message myMessage;
//     std::vector<char> myVect = {'h', 'e', 'l', 'l', 'o'};
//     myMessage.setMessage(myVect);
//     myMessage.setSize(5);
    
//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     myClient.Send(myMessage);
//     std::cout << "message sent" << std::endl;

//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     std::vector<char> myString;
//     char myInput;
//     int size = 0;
//     while(std::cin >> myInput)
//     {
//         myString.push_back(myInput);
//         size++;
//     }

//     myMessage.setMessage(myString);
//     myMessage.setSize(size);
//     myClient.Send(myMessage);
//     std::cout << "sent custom" << std::endl;
//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     std::ifstream file("../text/background.txt");
//     if (!file) {
//         std::cerr << "Failed to open file.\n";
//         return 1;
//     }

//     std::vector<char> contents;
//     char c;
//     while (file.get(c)) {
//         contents.push_back(c);
//     }

//     myMessage.setSize(contents.size());
//     myMessage.setMessage(contents);
//     myClient.Send(myMessage);
//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     while(1)
//     {
//         if(!(myClient.inputMessages.empty()))
//         {
//             for(int i = 0; i < myClient.inputMessages.front().size; i++)
//             {
//                 std::cout << myClient.inputMessages.front().message[i];
//             }
//             myClient.inputMessages.pop_front();
//             std::cout << std::endl;
//         }
//     }

//     myClient.disconnect();
//     std::cout << "Disconnected!" << std::endl;

//     return 0;
// }