#include "network.h"
#include "../game/game.h"

//SERVER
enum messageTypes {
    mapBackground,
    mapObstacles,
    entityList,
    entityUpdate,
    move
};
GameServer::GameServer(Game* game): Server(12345), game(game){};
GameServer::GameServer(unsigned short port, Game* game): Server(port), game(game) {};

void GameServer::do_accept() {
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

void GameServer::sendMap(std::shared_ptr<Connection> client) {
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

void GameServer::GameServerStart()
{
    std::cout << "server started on 12345" << std::endl;
    Start();
}

void GameServer::sendMove(const Move& move) {
    std::string serializedMove = move.serialize();
    if (serializedMove.empty()) {
        std::cerr << "Error: Serialized move is empty!" << std::endl;
        return;
    }

    std::vector<char> temp(serializedMove.begin(), serializedMove.end());
    Message sendMove(temp);
    sendMove.setType(messageTypes::move);
    sendMove.setSize(temp.size());

    if (Connections.empty()) {
        std::cerr << "Error: No clients connected to send the move!" << std::endl;
        return;
    }

    sendMessage(Connections.back(), sendMove); // Only sends to one client for now
}

void GameServer::processMove() {
    while (!inputMessages.empty()) {
        if(inputMessages.front().getType() == messageTypes::move)
        {
            Message msg = inputMessages.front();
            inputMessages.pop_front();

            std::string temp(msg.message.begin(), msg.message.end());
            Move move = Move::deserialize(temp);

            if (checkMove(game->entitiesList, move, true)) {
            } else {
                std::cerr << "Invalid move received from client!" << std::endl;
            }
        }
        else {
            std::cerr << "Invalid message type received from client!" << std::endl;
            std::cout << "Message type: " << inputMessages.front().getType() << std::endl;
            std::cout << "Message content: " << std::string(inputMessages.front().message.begin(), inputMessages.front().message.end()) << std::endl;
            std::cout << "Message size: " << inputMessages.front().message.size() << std::endl;
        }
    }
}

GameClient::GameClient(Game* game) : Client() {
    this->game = game;
}

void GameClient::GameClientConnect(std::string ip, int port)
{
    std::cout << "client connected on port" << port << std::endl;
    connect(ip, port); //connection
}

void GameClient::sendMove(const Move& move) {
    std::string serializedMove = move.serialize();
    if (serializedMove.empty()) {
        std::cerr << "Error: Serialized move is empty!" << std::endl;
        return;
    }

    std::vector<char> temp(serializedMove.begin(), serializedMove.end());
    Message sendMove(temp);
    sendMove.setType(messageTypes::move);
    sendMove.setSize(temp.size());
    Send(sendMove);
}

void GameClient::processMove() {
    while (!inputMessages.empty()) {
        Message msg = inputMessages.front();
        inputMessages.pop_front();

        std::string temp(msg.message.begin(), msg.message.end());
        Move move = Move::deserialize(temp);

        if (checkMove(game->entitiesList, move, true)) {
        } else {
            std::cerr << "Invalid move received from server!" << std::endl;
        }
    }
}