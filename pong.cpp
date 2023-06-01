// including the libraries
#include <iostream>
#include <raylib.h>
#include <ball.h>

// namespace std for less code
using namespace std;

// screening system
typedef enum GameScreen { TITLE, GAMEVSCPU, GAME, GAMEVSPLAYER, PAUSE, SETTINGS, SECRET } GameScreen;

// executable icon
Image logo = LoadImage("./resources/icon.png");

// keybinds
KeyboardKey Up, Down, P2Up, P2Down, Quit;
int textx = 200, texty = 200, textsize = 40;

Ball ball;
MenuBall mball;
Text text;
Paddle player;
Player2Paddle p2;
CpuPaddle cpu;
MenuPaddle player2;
MenuPaddle player3;

int main(void)
{
    cout << "Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong: Sky Edition");
    InitAudioDevice();
    SetExitKey(KEY_HOME);
    SetWindowIcon(logo);
    SetTargetFPS(60);

ball.radius = 20;
ball.x = screen_width/2;
ball.y = screen_height/2;
ball.speed_x = 7;
ball.speed_y = 7;
mball.radius = 20;
mball.x = screen_width/2;
mball.y = screen_height/2;
mball.speed_x = 7;
mball.speed_y = 7;
text.size = 60;
text.size2 = 40;
text.speed_x = 7;
text.speed_y = 7;

player.width = 25;
player.height = 120;
player.x = screen_width-player.width-10;
player.y = screen_height/2-player.height/2;
player.speed = 6;
p2.height = 120;
p2.width = 25;
p2.x = 10;
p2.y = screen_height/2-cpu.height/2;
p2.speed = 6;

player2.width = 25;
player2.height = 120;
player2.x = screen_width-player.width-10;
player2.y = screen_height/2-player.height/2;
player2.speed = 6;

player3.height = 120;
player3.width = 25;
player3.x = 10;
player3.y = screen_height/2-cpu.height/2;
player3.speed = 6;

cpu.height = 120;
cpu.width = 25;
cpu.x = 10;
cpu.y = screen_height/2-cpu.height/2;
cpu.speed = 6;

GameScreen windowState = TITLE;

Sound sound = LoadSound("song.mp3");

PlaySound(sound);

while (!WindowShouldClose()){
        if(!IsSoundPlaying(sound)){
            PlaySound(sound);
        }

        switch(windowState){
            case TITLE: {
                if (IsKeyPressed(KEY_SPACE))
                {
                    windowState = GAME;
                }
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    TakeScreenshot(TextFormat("screenshot.png"));
                }
                if(IsKeyPressed(KEY_Q)) {
                    return 0;
                }
            } break;
            case GAME: {
                if(IsKeyDown(KEY_UP)) {
                    texty += 1;
                }
                if(IsKeyDown(KEY_DOWN)) {
                    texty -= 1;
                }
                if(IsKeyDown(KEY_LEFT)) {
                    textx -= 1;
                }
                if(IsKeyDown(KEY_RIGHT)) {
                    textx += 1;
                }
                if(IsMouseButtonPressed(1)) {
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
            } break;
            case GAMEVSCPU: {
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    int time = GetTime();
                    TakeScreenshot("screenshot.png" );
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    windowState = PAUSE;
                }
            } break;
            case PAUSE: {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    windowState = GAME;
                }
                if(IsKeyPressed(KEY_Q)) {
                    windowState = TITLE;
                }
            } break;
            case GAMEVSPLAYER: {
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    int time = GetTime();
                    TakeScreenshot("screenshot.png" );
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    windowState = PAUSE;
                }
            } break;
            default: break;
        }
        }

        BeginDrawing();
        switch(windowState){
            case TITLE: {

        // Updating
        text.Update();
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
        text.Draw();
        mball.Draw();
        player2.Draw();
        player3.Draw();

            } break;
            case GAME: {
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        DrawRectangle(340, 300, 250, 350, BLACK);
        DrawRectangle(740, 300, 250, 350, BLACK);
        DrawText("VS PC", 797, 454, 40, RAYWHITE);
        DrawText("VS Friend", 358, 453, 40, RAYWHITE);
            } break;
            case GAMEVSCPU: {

        // Updating
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
            } break;
            case PAUSE: {
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        cpu.Draw();
        player.Draw();
            } break;
            case GAMEVSPLAYER: {
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
            } break;
            default: break;
        }

        EndDrawing();

        
        }

    CloseWindow();
    return 0;
}
