#define ENET_IMPLEMENTATION
#include <enet.h>
#include <iostream>

ENetAddress address;
ENetHost* server;
ENetEvent event;
void ParseData(ENetHost* server, int id, char* data){
    std::cout << "parsing data from user" << id << std::endl;

    int dataType;

    sscanf(data, "%d|", &dataType); 

    switch(dataType){
        case 1:
        break;
        case 2:
            char username[80];
            sscanf(data, "2|%[^\n]", &username);
            char send_data[1024] = {'\0'};
            sprintf(send_data, "2|%d|%s", id, username);
            std::cout << data << std::endl;
        break;
    }
}

int main(int argc, char** argv) {
    int init = enet_initialize();
    if(init != 0) {
        fprintf(stderr, "YOUR MOM DIED\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    address.host = ENET_HOST_ANY;
    address.port = 6969;

    server = enet_host_create(&address, 2, 1, 0, 0);
    if(server == NULL) {
        fprintf(stderr, "YOUR MOM DIED\n");
        return EXIT_FAILURE;
    }

    while(true) {
        while(enet_host_service(server, &event, 1000) > 0){
            switch(event.type) {
                case ENET_EVENT_TYPE_CONNECT: {
                    printf("SOME RANDOM BITCH ENTERED YOUR HOUSE FROM %s:%u GG", event.peer -> address.host, event.peer -> address.port);
                } break;
                case ENET_EVENT_TYPE_RECEIVE: {
                printf ("A packet of length %u containing %s was received from %s:%u on channel %u.\n",
                event.packet -> dataLength,
                event.packet -> data,
                event.peer -> address.host,
                event.peer -> address.port,
                event.channelID);
                ParseData(server, -1, event.packet->data);
                } break;
                case ENET_EVENT_TYPE_DISCONNECT: {
                    printf("THE BITCH FROM %s:%u LEFT YOUR HOUSE IMAGINE", event.peer -> address.host, event.peer -> address.port);
                } break;
   }
  } 
 }
 enet_host_destroy(server);
 return EXIT_SUCCESS;
}