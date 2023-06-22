#include <pong.h>
/*
these Enumerators are a type definition for game screens (called scenes in game engines), Discord RPC text and the type of match respectively
they are used to define the location of the user
*/
typedef enum GameScreen { TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET, NAN } GameScreen;
typedef enum RPCAt { HOME, PAUSED, INGAME, EDITORS, SETTING, NO } RPCAt;
typedef enum matchMode { VSCPU, VSPLAYER, VSPLAYERONLINE, NONE } matchMode;
int cpu_score = 0, player_score = 0;
/*
Namespaces are the way of making your code shorter for example: "std::cout" becomes "cout"
*/
using namespace std;

const float buttonSize = 200, buttonSpacing = 40, titleFontSize = 60, rotationSpeed = 2.0f;
float toggleSize = 20; // info
const float screen_width = 1280; // width of the window
const float screen_height = 800; // height of the window
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
Rectangle settingsButton = { screen_width / 2 - buttonSize / 2, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle playButton = { screen_width / 2 - buttonSize - buttonSpacing / 2 - 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle editorButton = { screen_width / 2 + buttonSpacing / 2 + 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
/*
this thing
*/
bool playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
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
MenuBall mball; // menu ball
Paddle player; // main player
Player2Paddle p2; // second player
CpuPaddle player2; // bot1
CpuPaddle player3; // bot2
CpuPaddle cpu; // bot3

void gamescreen() {
        ClearBackground(DG);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, G);
        DrawCircle(screen_width / 2, screen_height / 2, 150, LG);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        DrawRectangle(340, 300, 250, 350, BC);
        DrawRectangle(740, 300, 250, 350, BC);
        DrawText("VS PC", 797, 454, 40, RAYWHITE);
        DrawText("VS Friend", 358, 453, 40, RAYWHITE);
}
void settings() {
            
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

        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        p2.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}
void pause() {
    
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

        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}


int main(void) {
        Image logo = LoadImage("./resources/icon.png");
    init();
    InitWindow(screen_width, screen_height, "SkyPong");
    SetTargetFPS(60);
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetWindowIcon(logo);
ball.radius = 20;
ball.x = screen_width / 2;
ball.y = screen_height / 2;
ball.speed_x = 7;
ball.speed_y = 7;
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
player2.speed = 6;
player3.height = 120;
player3.width = 25;
player3.x = 10;
player3.y = screen_height / 2 - player3.height / 2;
player3.speed = 6;
cpu.height = 120;
cpu.width = 25;
cpu.x = 10;
cpu.y = screen_height / 2 - cpu.height / 2;
cpu.speed = 6;

float rotationAngle = 0.0f;

Vector2 titlePosition = { screen_width / 2 - MeasureText("SkyPong", titleFontSize) / 2, screen_height / 4 };
float voice = 0.5;
Sound sound = LoadSound("./resources/song.mp3");

PlaySound(sound);
int x1 = 200, y1 = 200, x2 = 200, y2 = 200, y3 = 200, x3 = 200;

while (!WindowShouldClose()){
     playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
     mousePosition = GetMousePosition();
        if(!IsSoundPlaying(sound)){
            PlaySound(sound);
        }
        switch(windowState){
            case TITLE: {
                
                if(RPC != HOME){
                    RPC = HOME;
                    update("Ponging", "In Main Menu");
                }
                if (playButtonPressed)
                    windowState = GAME;
                else if (settingsButtonPressed)
                    windowState = SETTINGS;
                else if (editorButtonPressed)
                    CloseWindow();
                if(IsKeyPressed(KEY_F11)) 
                    ToggleFullscreen();
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
                }
                if(IsKeyPressed(KEY_G)) {
                    voice = 0.1 + voice;
                    if(voice <= 1.0){
                        
                    } else {
                        SetSoundVolume(sound, voice);
                    } 
                }
                if(IsKeyPressed(KEY_B)) {
                    voice = 0.1 - voice;
                    if(voice <= 0.0){
                        
                    } else {
                        SetSoundVolume(sound, voice);
                    }
                    
                }
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
                if(IsKeyDown(KEY_W))
                y1++;
                if(IsKeyDown(KEY_A))
                x1++;
                if(IsKeyDown(KEY_S))
                y1--;
                if(IsKeyDown(KEY_D))
                x1--;
                if(IsKeyDown(KEY_T))
                y2++;
                if(IsKeyDown(KEY_F))
                x2++;
                if(IsKeyDown(KEY_G))
                y2--;
                if(IsKeyDown(KEY_H))
                x2--;
                if(IsKeyDown(KEY_I))
                y3++;
                if(IsKeyDown(KEY_J))
                x3++;
                if(IsKeyDown(KEY_K))
                y3--;
                if(IsKeyDown(KEY_L))
                x3--;
                if(IsKeyDown(KEY_DOWN))
                toggleSize--;
                if(IsKeyDown(KEY_UP))
                toggleSize++;
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

        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        
        DrawRectangleRec(settingsButton, settingsButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(playButton, playButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(editorButton, editorButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
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
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
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
         DrawRectangleRec(settingsButton, settingsButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
         DrawRectangleRec(playButton, playButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
         DrawRectangleRec(editorButton, editorButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);

        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Resume", playButton.x + buttonSize / 2 - MeasureText("Resume", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Menu", editorButton.x + buttonSize / 2 - MeasureText("Menu", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);
            } break;
            case GAMEVSPLAYER: {
        vsplayer();
            } break;
            case SETTINGS:{
            ClearBackground(BLACK);
            DrawText("Settings", screen_width / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
            DrawRectangle(x1, y1, toggleSize, toggleSize, toggle1 ? BLACK : GRAY);
            DrawRectangle(x2, y2, toggleSize, toggleSize, toggle2 ? BLACK : GRAY);
            DrawRectangle(x3, y3, toggleSize, toggleSize, toggle3 ? BLACK : GRAY);
            } break;
            default: break;
        }
        EndDrawing();
}
        end();
        CloseWindow();
        return 0;
}