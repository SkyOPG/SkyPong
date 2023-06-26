#include <a.h>
#include <discord_rpc.h>
#include <iostream>
#include <cstring>

DiscordEventHandlers handlers;
DiscordRichPresence presence;

void handleDiscordReady(const DiscordUser* request) {
    std::cout << "Discord Ready" << std::endl;
}
void handleDiscordJoinGame(const char* joinSecret) {
    std::cout << "Join game event received. Join secret: " << joinSecret << std::endl;

    bool acceptJoinRequest = true;
}
void handleDiscordJoinRequest(const DiscordUser* request) {
    std::cout << "a join request yay" << request;
}

int solve(long var2) {
   return var2;
}

void init() {
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = handleDiscordReady;
    handlers.joinGame = handleDiscordJoinGame;

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
void update_match(const char* matchsecret, const char* key, const char* state) {
    presence.state = state;
    presence.details = key;
    presence.largeImageKey = "pong";
    presence.partyId = "SkyPong";
    presence.matchSecret = "sfdghjthju-ug4uifs4";
    presence.joinSecret = "sfdghjhkju-ug4dffs4";
    presence.startTimestamp = time(0);
    Discord_UpdatePresence(&presence);
}

void end() {
    Discord_Shutdown();
}