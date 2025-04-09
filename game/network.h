#ifndef NET_H
#define NET_H
#include "game.h"
class CustomServer : public Server {
public:
    CustomServer(unsigned short port);
    void do_accept() override;
    void sendMap(std::shared_ptr<Connection> client);
};
    
class CustomClient : public Client {
public:
    CustomClient();
    void sendMap(std::shared_ptr<Connection> client);
    void receiveMap(std::shared_ptr<Connection> client);
    void handleReceivedMap();
    void processMapData();
    void send();
};
    
class GameServer : public Game {
public:
    GameServer();
    CustomServer myServer;
    void checkInput();
    void handleInput();
    void send();
    void receiveMap(std::shared_ptr<Connection> client);
    void handleReceivedMap();
    void processMapData();
};
    
class GameClient : public Game {
public:
    GameClient();
    CustomClient myClient;
};

#endif