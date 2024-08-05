#include <common.h>
#include <a.h>
Color DAG = Color{20, 160, 133, 255};

void KeyEvents(
	GameScreen &windowState, 
	RPCAt& RPC, 
	ButtonPressed isPressed, 
	bool& initted, 
	matchMode& match, 
	GameScreen& pausedFrom, 
	float& voice,
	Sound sretro,
	Theme& gameTheme,
	int& frames,
    Color& color,
    Vector2D& position,
    bool& build,
    int& numbah
	){
	if(!IsSoundPlaying(sretro)){
            PlaySound(sretro);
    }
	if(IsKeyPressed(KEY_I)){
        switch(gameTheme){
            case RETRO: {
                gameTheme = NORMAL;
            } break;
            case NORMAL: {
                gameTheme = PARTY;
            } break;
            case PARTY: {
                gameTheme = RETRO;
            } break;
        }
    }
	switch(windowState){
			case LOADING:{
                frames++;
           /* bool done = (color.b == DAG.b) && (color.r == DAG.r) && (color.g == DAG.g);
                if(!done){   
                    if(color.r != DAG.r){
                        bool idk = color.r < DAG.r;
                        bool idk2 = color.r > DAG.r;
                        if(idk){
                            color.r = color.r + 1;
                        } else if(idk2){
                            color.r = color.r - 1;
                        }
                    }
                    if(color.g != DAG.g){
                        bool idk = color.g < DAG.g;
                        bool idk2 = color.g > DAG.g;
                        if(idk){
                            color.g = color.g + 1;
                        } else if(idk2){
                            color.g = color.g - 1;
                        }
                    }
                    if(color.b != DAG.b){
                        bool idk = color.b < DAG.b;
                        bool idk2 = color.b > DAG.b;
                        if(idk){
                            color.b = color.b + 1;
                        } else if(idk2){
                            color.b = color.b - 1;
                        }
                    }
                } else {
                    if((position.y != (GetRenderHeight() + 240))){
                        position.x -= 4;
                        position.y += 4;
                    } else if((position.x != -680)){
                        position.x -= 4;
                    } else {
                        build = true;
                    }
                }
                if(build){
                    numbah++;
                    int multiplier = 4;
                    multiplier *= numbah;
                    DrawCircle(screen_width / 2, screen_height / 2, numbah > 150 ? 150 : numbah, {129, 204, 184, 255});
                    DrawLine(screen_width / 2, 0, screen_width / 2, multiplier > screen_height ? screen_height : multiplier, WHITE);
                }*/
			} break;
            case TITLE: {
                if(RPC != HOME){
                    RPC = HOME;
                   update("Ponging", "In Main Menu");
                    update_match("skypong.skyopg.pro/match/211", "Online", "Waiting...");
                }
                if (isPressed.play)
                    windowState = GAME;
                else if (isPressed.settings)
                    windowState = SETTINGS;
                else if (isPressed.editor){
                    initted = false;
                    }
                if(IsKeyPressed(KEY_F11)) 
                    ToggleFullscreen();
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
                }
                if(IsKeyPressed(KEY_T)) 
                    windowState = TIMED;
            } break;
            case GAME: {
                if(IsMouseButtonPressed(0)) {
            if(341 <= GetMouseX()){
                if(GetMouseX() <= 585){
                    if(273 <= GetMouseY()){
                        if(GetMouseY() <= 618) {
                windowState = GAMEVSPLAYER;
            }
                }
            } else if(740 <= GetMouseX()){
                 if(GetMouseX() <= 985){
                     if(273 <= GetMouseY()){
                         if(GetMouseY() <= 618){
                            windowState = GAMEVSCPU;
                            } 
                        } 
                    }  
                }
        }
            }
            if(IsKeyPressed(KEY_ESCAPE))
            windowState = TITLE;
                } break;
            case GAMEVSCPU: {
                if(RPC != INGAME){
                    RPC = INGAME;
                    match = VSCPU;
                    update("Ponging", "VS Computer");
                }
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    pausedFrom = GAMEVSCPU;
                    windowState = PAUSE;
                }
            } break;
            case PAUSE: {
                if(RPC != PAUSED){
                    RPC = PAUSED;
                    update("Ponging", "Paused");
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    windowState = pausedFrom;
                }
                if (isPressed.play)
                    windowState = pausedFrom;
                else if (isPressed.settings)
                    windowState = SETTINGS;
                else if (isPressed.editor)
                    windowState = GAME;
            } break;
            case GAMEVSPLAYER: {
                if(RPC != INGAME){
                    RPC = INGAME;
                    match = VSPLAYER;
                    update("Ponging", "VS Friend");
                }
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    pausedFrom = GAMEVSPLAYER;
                    windowState = PAUSE;
                }
            } break;
            case SETTINGS: {
                if(IsKeyPressed(KEY_ESCAPE))
                windowState = TITLE;
                if (isPressed.toggle1){
                    voice = voice - 0.1;
                    if(voice <= 0.0){
                        
                    } else {
                        SetSoundVolume(sretro, voice);
                    }
                }
                else if (isPressed.toggle2){
                    voice = voice + 0.1;
                    if(voice >= 0.0)
                        SetSoundVolume(sretro, voice);
                }
                else if (isPressed.toggle3) {
                    switch(gameTheme){
                case RETRO: {
                    gameTheme = NORMAL;
                } break;
                case NORMAL: {
                    gameTheme = PARTY;
                } break;
                case PARTY: {
                    gameTheme = RETRO;
                } break;
            }
                }
            } break;
            case TIMED: {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    pausedFrom = TIMED;
                    windowState = PAUSE;
                }
            }
            default: break;
        }
}