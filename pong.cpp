#include <pong.h>

/*
Namespaces are the way of making your code shorter for example: "std::cout" becomes "cout"
*/
using namespace std;

/*
these Enumerators are a type definition for game screens (called scenes in game engines), Discord RPC text and the type of match respectively
they are used to define the location of the user
*/
typedef enum GameScreen { TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET, NAN } GameScreen;
typedef enum RPCAt { HOME, PAUSED, INGAME, EDITORS, SETTING, NO } RPCAt;
typedef enum matchMode { VSCPU, VSPLAYER, VSPLAYERONLINE, NONE } matchMode;

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
Vanilla Variables can be constant or non constant (with or without const) with the obligation of a type (float, int, enum, auto, string...)
*/
const float buttonSize = 200, buttonSpacing = 40, titleFontSize = 60, rotationSpeed = 2.0f, toggleSize = 20;// info
float textx = 200, texty = 200, textsize = 40; // debugging
const float screen_width = 1280; // width of the window
const float screen_height = 800; // height of the window
bool toggle1 = false; // toggles for settings
bool toggle2 = false; // another one
bool toggle3 = false; // last one
char textInput[256] = ""; // text 
// basic collision
bool playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
// custom type definitions by raylib
Color sb = Color{ 135, 206, 235, 255 }; // sky blue
Color BC = Fade(sb, 0.5f); // sky blue but 50% opacity
Color G = Color{38, 185, 154, 255}; // green
Color DG = Color{20, 160, 133, 255}; // dark green
Color LG = Color{129, 204, 184, 255}; // light green
Color Y = Color{243, 213, 91, 255}; // yellow
Color B = Color{30, 139, 159, 255}; // blue
Color skyblue = Color{ 135, 206, 235, 255 }; // sky blue (again)
Color buttonColor = Fade(skyblue, 0.5f); // sky blue but 50% opacity (again)
Color Green = Color{38, 185, 154, 255}; // green (again)
Color Dark_Green = Color{20, 160, 133, 255}; // dark green (again)
Color Light_Green = Color{129, 204, 184, 255}; // light green (again)
Color Yellow = Color{243, 213, 91, 255}; // yellow (again)
Color Blue = Color{30, 139, 159, 255}; // blue (again)
KeyboardKey Up, Down, P2Up, P2Down, Quit; // keybinds
/*
Custom Classes By me
*/
Ball ball;
MenuBall mball;
Player2Paddle p2;
CpuPaddle cpu;
CpuPaddle player2;
CpuPaddle player3;

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
    ClearBackground(BLUE);
                DrawText("Settings", screen_width / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
                DrawRectangle(screen_width / 2 + 20, screen_height / 2 - 90, toggleSize, toggleSize, toggle1 ? BLACK : GRAY);
                DrawRectangle(screen_width / 2 + 20, screen_height / 2 - 50, toggleSize, toggleSize, toggle2 ? BLACK : GRAY);
                DrawText(textInput, screen_width / 2 + 25, screen_height / 2 + 7, 20, BLACK);
                DrawRectangle(screen_width / 2 + 20, screen_height / 2 + 50, toggleSize, toggleSize, toggle3 ? BLACK : GRAY);
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
    DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText("Paused", screen_width / 2 - MeasureText("Paused", 50) / 2, 20, 50, BLACK);
        DrawRectangleRec(settingsButton, settingsButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(playButton, playButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(editorButton, editorButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);

        // Draw button text
        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Resume", playButton.x + buttonSize / 2 - MeasureText("Resume", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Menu", editorButton.x + buttonSize / 2 - MeasureText("Menu", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);
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
void title() {
        
}

void titlescreen_code() {
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
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
                }
}
void gamescreen_code(){
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
}

void vscpu_code(){
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
                    windowState = PAUSE;
                }
}
void pause_code() {
    if(RPC != PAUSED){
                    RPC = PAUSED;
                    update("Ponging", "Paused");
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    windowState = pausedFrom;
                }
}
void vsplayer_code(){
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
                    pausedFrom = GAMEVSCPU;
                    windowState = PAUSE;
                }
}

int mailn(void) {
    init();

    cout << "Starting the game" << endl;
    
    InitWindow(screen_width, screen_height, "SkyPong");
    
    SetTargetFPS(60);

float rotationAngle = 0.0f;

Vector2 titlePosition = { screen_width / 2 - MeasureText("SkyPong", titleFontSize) / 2, screen_height / 4 };

Sound sound = LoadSound("./resources/song.mp3");

PlaySound(sound);

while (!WindowShouldClose()){
        if(!IsSoundPlaying(sound)){
            PlaySound(sound);
        }
        switch(windowState){
            case TITLE: {
                titlescreen_code();
            } break;
            case GAME: {
                gamescreen_code();
                } break;
            case GAMEVSCPU: {
                vscpu_code();
            } break;
            case PAUSE: {
                pause_code();
            } break;
            case GAMEVSPLAYER: {
                vsplayer_code();
            } break;
            default: break;
        }
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

        // Draw button text
        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Play", playButton.x + buttonSize / 2 - MeasureText("Play", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Quit", editorButton.x + buttonSize / 2 - MeasureText("Quit", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);
            } break;
            case GAME: {
        gamescreen();
            } break;
            case GAMEVSCPU: {

        // Updating
        vscpu();
            } break;
            case PAUSE: {
        pause();
            } break;
            case GAMEVSPLAYER: {
        vsplayer();
            } break;
            case SETTINGS:{
                // Draw settings elements
                settings();
                } break;
            default: break;
        }

        EndDrawing();end();CloseWindow();return 0;
}
int main(){
    Image logo = LoadImage("./resources/icon.png");
    InitWindow(screen_width, screen_height, "SkyPong");
    SetTargetFPS(60);
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetWindowIcon(logo);
    while(!WindowShouldClose()){
        BeginDrawing();
        switch(windowState){
            case TITLE: {
                mball.Draw();
                player2.Draw();
                player3.Draw();
            } break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}