#include <common.h>

void SetTheme(Theme &gameTheme, char* &Themetext){
	switch(gameTheme){
        case NORMAL: {
            Themetext = "DEFAULT";
        } break;
        case RETRO: {
            Themetext = "RETRO";
        } break;
        case PARTY: {
            Themetext = "PARTY";
        }
    }
}