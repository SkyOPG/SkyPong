#include <pong.h>

#define GLSL_VERSION            330

/*
Namespaces are the way of making your code shorter for example: "std::cout" becomes "cout"
*/
using namespace std;

// setup variables
const float screen_width = 1280;
const float screen_height = 800;

/*
these Enumerators are a type definition for game screens (called scenes in game engines), Discord RPC text and the type of match respectively
they are used to define the location of the user
*/
typedef enum GameScreen { TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET, TIMED, NAN } GameScreen;
typedef enum RPCAt { HOME, PAUSED, INGAME, EDITORS, SETTING, TIME, NO } RPCAt;
typedef enum matchMode { VSCPU, VSPLAYER, VSPLAYERONLINE, NONE } matchMode;
typedef enum Theme { NORMAL, RETRO, PARTY } Theme;
// stuff
const float buttonSize = 200, buttonSpacing = 40, titleFontSize = 60, rotationSpeed = 2.0f;
float toggleSize = 57;
Theme gameTheme = NORMAL;
Theme song = NORMAL;
char* Themetext;
Color btclr1, btclr2;
Color purple = Color{90, 34, 139, 1};
Color lpurple = Color{102, 51, 153, 255};
Color wite = Color{255,255,255,255};
Color blak = Color{0,0,0,0};
Color G = Color{38, 185, 154, 255};
Color DG = Color{20, 160, 133, 255};
Color LG = Color{129, 204, 184, 255};
Color Y = Color{243, 213, 91, 255};
Color buttonColor = Color{30, 139, 159, 255};
Color otherBlue = Color{30, 139, 159, 0};
Color pc = wite;
/*
Definitions for enums
*/
GameScreen pausedFrom = NAN; // pause menu stuff
GameScreen windowState = TITLE; // scene stuff
RPCAt RPC = NO; // RPC location
matchMode match = NONE; // type of match
/*
Vector math
*/
Vector2 mousePosition = GetMousePosition();
/*
Rectangles types are predefined objects for easy use in scenes
*/
float addwidth = 0;
Rectangle settingsButton = { screen_width / 2 - buttonSize / 2, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle playButton = { screen_width / 2 - buttonSize - buttonSpacing / 2 - 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle editorButton = { screen_width / 2 + buttonSpacing / 2 + 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle rectoggle1 = { 17, 72, toggleSize, toggleSize };
Rectangle rectoggle2 = { 140, 72, toggleSize, toggleSize };
Rectangle rectoggle3 = { 19, 246, toggleSize + 129 , toggleSize };
Rectangle rec1 = { 340, 300, 250, 350 };
Rectangle rec2 = { 740, 300, 250, 350 };
/*
this thing
*/
bool playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool toggle1Pressed = CheckCollisionPointRec(mousePosition, rectoggle1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool toggle2Pressed = CheckCollisionPointRec(mousePosition, rectoggle2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool toggle3Pressed = CheckCollisionPointRec(mousePosition, rectoggle3) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool rec1Pressed = CheckCollisionPointRec(mousePosition, rec1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool rec2Pressed = CheckCollisionPointRec(mousePosition, rec2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
/*
Vanilla Variables can be constant or non constant (with or without const) with the obligation of a type (float, int, enum, auto, string...)
*/
float textx = 200, texty = 200, textsize = 40; // debugging
bool toggle1 = false; // toggles for settings
bool toggle2 = false; // another one
bool toggle3 = false; // last one
char textInput[256] = ""; // text 
// basic collision
/*
Custom Classes By me
*/ 
Ball ball; // the ball
PowerBall timeBall; // timed ball
MenuBall mball; // menu ball
Paddle player; // main player
Player2Paddle p2; // second player
CpuPaddle player2; // bot1
CpuPaddle player3; // bot2
CpuPaddle cpu; // bot3

void DrawTable(Theme theme) {
    switch(theme){
        case NORMAL: {
             ClearBackground(DG);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, G);
             DrawCircle(screen_width / 2, screen_height / 2, 150, LG);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = wite;
             btclr1 = buttonColor;
             btclr2 = otherBlue;
        } break;
        case RETRO: {
             ClearBackground(BLACK);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, BLACK);
             DrawCircle(screen_width / 2, screen_height / 2, 150, WHITE);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = wite;
             btclr1 = Fade(LIGHTGRAY, 0.5f);
             btclr2 = Fade(GRAY, 0.5f);
        } break;
        case PARTY: {
             ClearBackground(purple);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, lpurple);
             DrawCircle(screen_width / 2, screen_height / 2, 150, WHITE);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = blak;
             btclr1 = Fade(lpurple, 0.5f);
             btclr2 = Fade(purple, 0.5f);
        } break;
    }
}

void timedvscpu() {
    timeBall.Update();
        player.Update();
        cpu.Update(timeBall.y);

        if (CheckCollisionCircleRec(Vector2{timeBall.x, timeBall.y}, timeBall.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            timeBall.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{timeBall.x, timeBall.y}, timeBall.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            timeBall.speed_x *= -1;
        }

        DrawTable(gameTheme);
        timeBall.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}
void vscpu() {
    ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

        DrawTable(gameTheme);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}
void vsplayer() {
    ball.Update();
        player.Update();
        p2.Update();

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p2.x, p2.y, p2.width, p2.height}))
        {
            ball.speed_x *= -1;
        }

        DrawTable(gameTheme);
        ball.Draw();
        p2.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}
void gamescreen() {
        DrawTable(gameTheme);
        DrawRectangleRec(rec1, rec1Pressed ? btclr2 : btclr1);
        DrawRectangleRec(rec2, rec2Pressed ? btclr2 : btclr1);
        DrawText("VS PC", 797, 454, 40, RAYWHITE);
        DrawText("VS Friend", 358, 453, 40, RAYWHITE);
}

int main(void) {
    Image logo = LoadImage("./resources/icon.png");
    init();
    InitWindow(screen_width, screen_height, "SkyPong");
    SetTargetFPS(60);
    InitAudioDevice();
    Sound sretro = LoadSound("./resources/retro.mp3");
    SetExitKey(KEY_NULL);
    SetWindowIcon(logo);

ball.radius = 20;
ball.x = screen_width / 2;
ball.y = screen_height / 2;
ball.speed_x = 7;
ball.speed_y = 7;

timeBall.radius = 20;
timeBall.x = screen_width / 2;
timeBall.y = screen_height / 2;
timeBall.speed_x = 7;
timeBall.speed_y = 7;

mball.radius = 20;
mball.x = screen_width / 2;
mball.y = screen_height / 2;
mball.speed_x = 7;
mball.speed_y = 7;

player.width = 25;
player.height = 120;
player.x = screen_width - player.width - 10;
player.y = screen_height / 2 - player.height / 2;
player.speed = 6;

p2.width = 25;
p2.height = 120;
p2.x = 10;
p2.y = screen_height / 2 - p2.height / 2;
p2.speed = 6;

player2.width = 25;
player2.height = 120;
player2.x = screen_width - player2.width - 10;
player2.y = screen_height / 2 - player2.height / 2;
player2.speed = 6;player3.height = 120;

player3.width = 25;player3.x = 10;
player3.y = screen_height / 2 - player3.height / 2;
player3.speed = 6;cpu.height = 120;

cpu.width = 25;cpu.x = 10;
cpu.y = screen_height / 2 - cpu.height / 2;
cpu.speed = 6;

float rotationAngle = 0.0f;
float voice = 0.5;
Vector2 titlePosition = { screen_width / 2 - MeasureText("SkyPong", titleFontSize) / 2, screen_height / 4 };

bool initted = true;
while (!WindowShouldClose() && initted){
    string Themetext;
     mousePosition = GetMousePosition();
     playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     toggle1Pressed = CheckCollisionPointRec(mousePosition, rectoggle1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     toggle2Pressed = CheckCollisionPointRec(mousePosition, rectoggle2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     toggle3Pressed = CheckCollisionPointRec(mousePosition, rectoggle3) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     rec1Pressed = CheckCollisionPointRec(mousePosition, rec1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     rec2Pressed = CheckCollisionPointRec(mousePosition, rec2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

     switch(gameTheme){
        case NORMAL: {
            Themetext = "DEF";
        } break;
        case RETRO: {
            Themetext = "RETRO";
        } break;
        case PARTY: {
            Themetext = "PARTY";
        }
     }
     
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

            case TITLE: {
                if(RPC != HOME){
                    RPC = HOME;
                   update("Ponging", "In Main Menu");
                   // update_match("SkyOPG.ms/SkyPong/match/211", "Online", "Waiting...");
                }
                if (playButtonPressed)
                    windowState = GAME;
                else if (settingsButtonPressed)
                    windowState = SETTINGS;
                else if (editorButtonPressed){
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
                if (playButtonPressed)
                    windowState = pausedFrom;
                else if (settingsButtonPressed)
                    windowState = SETTINGS;
                else if (editorButtonPressed)
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
                if (toggle1Pressed){
                    voice = voice - 0.1;
                    if(voice <= 0.0){
                        
                    } else {
                        SetSoundVolume(sretro, voice);
                    }
                }
                else if (toggle2Pressed){
                    voice = voice + 0.1;
                    if(voice <= 0.0){
                        
                    } else {
                        SetSoundVolume(sretro, voice);
                    }
                }
                else if (toggle3Pressed) {
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

        BeginDrawing();
        switch(windowState){
            case TITLE: {
        mball.Update();
        player2.Update(mball.y);
        player3.Update(mball.y);

        if (CheckCollisionCircleRec(Vector2{mball.x, mball.y}, mball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height}))
        {
            mball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{mball.x, mball.y}, mball.radius, Rectangle{player3.x, player3.y, player3.width, player3.height}))
        {
            mball.speed_x *= -1;
        }

        DrawTable(gameTheme);
        
        DrawRectangleRec(settingsButton, settingsButtonPressed ? btclr2 : btclr1);
        DrawRectangleRec(playButton, playButtonPressed ? btclr2 : btclr1);
        DrawRectangleRec(editorButton, editorButtonPressed ? btclr2 : btclr1);
        mball.Draw();
        player2.Draw();
        player3.Draw();
        // Draw button text
        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Play", playButton.x + buttonSize / 2 - MeasureText("Play", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Quit", editorButton.x + buttonSize / 2 - MeasureText("Quit", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);   
            } break;
            case GAME: {
        gamescreen();
            } break;
            case GAMEVSCPU: {
        vscpu();
            } break;
            case PAUSE: {
        DrawTable(gameTheme);
        switch(pausedFrom){
            case GAMEVSCPU: {
                cpu.Draw();
            } break;
            case GAMEVSPLAYER: {
                p2.Draw();
            }
        }
        ball.Draw();
        player.Draw();
        DrawText("Paused", screen_width / 2 - MeasureText("Paused", 50) / 2, 20, 50, BLACK);
         DrawRectangleRec(settingsButton, settingsButtonPressed ? btclr2 : btclr1);
         DrawRectangleRec(playButton, playButtonPressed ? btclr2 : btclr1);
         DrawRectangleRec(editorButton, editorButtonPressed ? btclr2 : btclr1);

        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Resume", playButton.x + buttonSize / 2 - MeasureText("Resume", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Menu", editorButton.x + buttonSize / 2 - MeasureText("Menu", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);
            } break;
            case GAMEVSPLAYER: {
        vsplayer();
            } break;
            case TIMED: {
                timedvscpu();
            } break;
            case SETTINGS:{
                toggleSize = 57;
                int safe = voice * 100;
            DrawTable(gameTheme);
            DrawText("Settings", screen_width / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
            DrawRectangleRec(rectoggle1, toggle1 ? btclr2 : btclr1);
            DrawRectangleRec(rectoggle2, toggle2 ? btclr2 : btclr1);
            DrawRectangleRec(rectoggle3, toggle3 ? btclr2 : btclr1);
            DrawText(TextFormat("%i", safe), 84, 77, 51, WHITE);
            DrawText("Volume", 53, 18, 32, WHITE);
            DrawText("Theme", 52, 189, 37, WHITE);
            DrawText(">", 160, 65, 77, WHITE);
            DrawText("<", 27, 65, 77, WHITE);
            DrawText(TextFormat("%s", Themetext), 41, 257, 41, WHITE);

            } break;
            default: break;
        }
        
        EndDrawing();
}
    end();
    CloseWindow();

        return 0;
}