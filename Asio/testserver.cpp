#include "server.h"


using asio::ip::tcp;

int main() {
    Server myServer(12345);
    std::cout << "Server started on port 12345" << std::endl;
    myServer.Start();

    while(1)
    {
        if(!(myServer.inputMessages.empty()))
        {
            Message myMessage;
            std::vector<char> myVect = {'h', 'e', 'l', 'l', 'o'};
            myMessage.setMessage(myVect);
            myMessage.setSize(5);
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
        
            myServer.sendMessage(myServer.Connections[0], myMessage);

            for(int i = 0; i < myServer.inputMessages.front().size; i++)
            {
                std::cout << myServer.inputMessages.front().message[i];
            }
            std::cout << "Type: ";
            std::cout << myServer.inputMessages.front().type;
            myServer.inputMessages.pop_front();
            std::cout << std::endl;
        }
    }
    return 0;
}