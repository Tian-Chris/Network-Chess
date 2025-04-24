#include "network.h"
#include "../game/game.h"

//SERVER
enum messageTypes {
    mapBackground,
    mapObstacles,
    entityList,
    entityUpdate,
    move,
    turn,
    color
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
                startGame();
            } else {
                std::cout << "SERVER: Connection Error: " << ec.message() << "\n";
            }
            do_accept();
        });
}

void GameServer::startGame() {
    if(rand() % 2 == 0)
    {
        game->turn = false;
        game->color = false;
        Message color;
        color.setType(messageTypes::color);
        color.setMessage(std::vector<char>{'w', 'h', 'i', 't', 'e'});
        color.setSize(color.message.size());
        Message turn;
        turn.setType(messageTypes::turn);
        turn.setMessage(std::vector<char>{'t', 'r', 'u', 'e'});
        turn.setSize(turn.message.size()); 
        sendMessage(Connections.back(), turn);
        sendMessage(Connections.back(), color);
        std::cout << "clien turn!" << std::endl;
    }
    else
    {
        game->turn = true;
        game->color = true;
        Message color;
        color.setType(messageTypes::color);
        color.setMessage(std::vector<char>{'b', 'l', 'a', 'c', 'k'});
        color.setSize(color.message.size());
        Message turn;
        turn.setType(messageTypes::turn);
        turn.setMessage(std::vector<char>{'f', 'a', 'l', 's', 'e'});
        turn.setSize(turn.message.size());
        sendMessage(Connections.back(), turn);
        sendMessage(Connections.back(), color);
        std::cout << "server turn!" << std::endl;
    }
    std::cout << "Game started!" << std::endl;
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
    Message turn;
    turn.setType(messageTypes::turn);
    turn.setMessage(std::vector<char>{'t', 'r', 'u', 'e'});
    turn.setSize(turn.message.size());
    sendMessage(Connections.back(), turn); // Changed from Send(turn) to sendMessage
    cout << "server sent turn" << endl;
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
        else if(inputMessages.front().getType() == messageTypes::turn)
        {
            cout << "inside turn server" << endl;
            if(inputMessages.front().message == std::vector<char>{'t', 'r', 'u', 'e'})
            {
                cout << "server true" << endl;
                game->turn = true;
            }
            else
            {
                std::cout << "Message content: " << std::string(inputMessages.front().message.begin(), inputMessages.front().message.end()) << std::endl;
                game->turn = false;
            }
            inputMessages.pop_front();
        }
        else if(inputMessages.front().getType() == messageTypes::color)
        {
            if(inputMessages.front().message == std::vector<char>{'w', 'h', 'i', 't', 'e'})
            {
                game->color = true;
            }
            else
            {
                game->color = false;
            }
            inputMessages.pop_front();

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
    Message turn;
    turn.setType(messageTypes::turn);
    turn.setMessage(std::vector<char>{'t', 'r', 'u', 'e'});
    turn.setSize(turn.message.size());
    Send(turn);
    cout << "client sent turn" << endl;
}

void GameClient::processMove() {
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
        else if(inputMessages.front().getType() == messageTypes::turn)
        {
            cout << "inside turn client" << endl;

            if(inputMessages.front().message == std::vector<char>{'t', 'r', 'u', 'e'})
            {
                std::cout << "client true" << std::endl;
                game->turn = true;
            }
            else
            {
                std::cout << "Message content: " << std::string(inputMessages.front().message.begin(), inputMessages.front().message.end()) << std::endl;
                game->turn = false;
            }
            inputMessages.pop_front();
        }
        else if(inputMessages.front().getType() == messageTypes::color)
        {
            if(inputMessages.front().message == std::vector<char>{'w', 'h', 'i', 't', 'e'})
            {
                game->color = true;
            }
            else
            {
                game->color = false;
            }
            inputMessages.pop_front();
        }
        else {
            std::cerr << "Invalid message type received from sserver!" << std::endl;
            std::cout << "Message type: " << inputMessages.front().getType() << std::endl;
            std::cout << "Message content: " << std::string(inputMessages.front().message.begin(), inputMessages.front().message.end()) << std::endl;
            std::cout << "Message size: " << inputMessages.front().message.size() << std::endl;
            inputMessages.pop_front();
        }
    }
}