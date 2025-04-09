#include "network.h"

//SERVER
enum messageTypes {
    mapBackground,
    mapObstacles,
    entityList,
    entityUpdate
};

CustomServer::CustomServer(unsigned short port): Server(port) {};

CustomClient::CustomClient() : Client() {};

void CustomServer::do_accept() {
    acceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::cout << "Client connected!" << std::endl;
                std::shared_ptr<Connection> connection = std::make_shared<Connection>(io_context, std::move(socket), inputMessages);
                Connections.push_back(std::move(connection));
                sendMap(Connections.back());
                Connections.back()->read();
            } else {
                std::cout << "SERVER: Connection Error: " << ec.message() << "\n";
            }
            do_accept();
        });
}

void CustomServer::sendMap(std::shared_ptr<Connection> client) {
    Message mapBackground;
    Message mapObstacles;
    mapBackground.readFile("background.txt");
    mapObstacles.readFile("obstacles.txt");
    mapBackground.setType(messageTypes::mapBackground);
    mapObstacles.setType(messageTypes::mapObstacles);
    sendMessage(client, mapBackground);
    sendMessage(client, mapObstacles);
    std::cout << "mapsent";
}


GameServer::GameServer() : myServer(12345) //port address
{   
    std::cout << "Server started on port 12345" << std::endl;
    myServer.Start();
}

GameClient::GameClient() : myClient()
{   
    std::cout << "client connected on port 12345" << std::endl;
    myClient.connect("127.0.0.1", 12345); //connection
}

