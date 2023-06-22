#define ENET_IMPLEMENTATION
#include <enet.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

void SendPacket(ENetPeer* peer, const char* data) {
    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
}

int main(){
    int init = enet_initialize();
    if(init != 0) {
        fprintf(stderr, "YOUR MOM DIED\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    ENetHost* client;
    client = enet_host_create(NULL, 1, 1, 0, 0);
    if(client == NULL) {
        fprintf(stderr, "YOUR MOM DIED\n");
        return EXIT_FAILURE;
    }
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 6969;

    peer = enet_host_connect(client, &address, 1, 0);
    if(peer == NULL) {
        fprintf(stderr, "YOUR MOM DIED\n");
        return EXIT_FAILURE;
    }

    if(enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
    puts("Connection to 127.0.0.1:6969 Successful");
    } else {
        enet_peer_reset(peer);
        puts("Connection to 127.0.0.1:6969 not fucking Successful");
        return EXIT_SUCCESS;
    }
    char* name = "johnny sins";
    char code[80] = "8|";
    strcat(code, name);
    SendPacket(peer, code);

    while(enet_host_service(client, &event, 1000) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_RECEIVE: {
                printf ("A packet of length %u containing %s was received from %s:%u on channel %u.\n",
                event.packet -> dataLength,
                event.packet -> data,
                event.peer -> address.host,
                event.peer -> address.port,
                event.channelID);
            } break;
        }
    }
    enet_peer_disconnect(peer, 0);

    while(enet_host_service(client, &event, 3000) > 0) {
        switch(event.type) {
            case ENET_EVENT_TYPE_RECEIVE: {
                enet_packet_destroy(event.packet);
            } break;
            case ENET_EVENT_TYPE_DISCONNECT: {
                puts("oh ye your mom died in a cool way");
            } break;
        }
    }

    return EXIT_SUCCESS;
}