#ifndef NET_H
#define NET_H
#include <memory> 
#include "../Asio/server.h" 
#include "../Asio/client.h" 
#include "../Asio/connection.h" 
#include "move.h"
class Game;

class GameServer : public Server{
public:
    GameServer(unsigned short port, Game* game);
    GameServer(Game* game);

    void GameServerStart();
    void do_accept() override;
    void sendMove(const Move& move);
    void sendMap(std::shared_ptr<Connection> client);
    void processMove();
    void receiveMap(std::shared_ptr<Connection> client);
    void handleReceivedMap();
    void processMapData();
    void receiveMove(std::shared_ptr<Connection> client);

    Game* game;
};
    
class GameClient : public Client{
public:
    GameClient(Game* game);
    void GameClientConnect(std::string ip, int port);
    void sendMove(const Move& move);
    void processMove();
    void sendMap(std::shared_ptr<Connection> client);
    void receiveMap(std::shared_ptr<Connection> client);
    void handleReceivedMap();
    void processMapData();

    Game* game;
};

#endif