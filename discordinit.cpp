#include <a.h>
#include <discord_rpc.h>
#include <iostream>
#include <cstring>

void handleDiscordReady(const DiscordUser* request) {
    std::cout << "Discord Ready" << std::endl;
}

DiscordEventHandlers handlers;
DiscordRichPresence presence;

int solve(long var2) {
   return var2;
}

void init() {
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;

    Discord_Initialize("1119974286392840313", &handlers, 1, NULL);
}

void update(const char* state, const char* key) {
    
    memset(&presence, 0, sizeof(presence));
    presence.state = state;
    presence.details = key;
    presence.largeImageKey = "pong";
    presence.startTimestamp = time(0);
    Discord_UpdatePresence(&presence);
}

void end() {
    Discord_Shutdown();
}