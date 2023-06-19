#include <pong.h>

using namespace std;
GameScreen pausedFrom = NAN;
GameScreen windowState = TITLE;
RPCAt RPC = NO;
matchMode mode = NONE;

Ball ball;
MenuBall mball;
Text text;
APaddle player;
Player2Paddle p2;
CpuPaddle cpu;
CpuPaddle player2;
CpuPaddle player3;
matchMode match = NONE;
Image logo = LoadImage("./resources/icon.png");
Rectangle settingsButton = { screen_width / 2 - buttonSize / 2, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle playButton = { screen_width / 2 - buttonSize - buttonSpacing / 2 - 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle editorButton = { screen_width / 2 + buttonSpacing / 2 + 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Color skyblue = Color{ 135, 206, 235, 255 };
Color buttonColor = Fade(skyblue, 0.5f);
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color Blue = Color{30, 139, 159, 255};
KeyboardKey Up, Down, P2Up, P2Down, Quit;

int main(void) {
    init();

    cout << "Starting the game" << endl;
    
    InitWindow(screen_width, screen_height, "SkyPong");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetWindowIcon(logo);
    SetTargetFPS(60);



float rotationAngle = 0.0f;

Vector2 titlePosition = { screen_width / 2 - MeasureText("SkyPong", titleFontSize) / 2, screen_height / 4 };

Sound sound = LoadSound("/resources/song.mp3");

PlaySound(sound);



bool toggle1 = false;
bool toggle2 = false;
bool toggle3 = false;
char textInput[256] = "";

while (!WindowShouldClose()){
        if(!IsSoundPlaying(sound)){
            PlaySound(sound);
        }
        Vector2 mousePosition = GetMousePosition();

        playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
        settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
        editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

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
                if(IsKeyPressed(KEY_F11)) {
                    ToggleFullscreen();
                }
                if(IsKeyPressed(KEY_F2)) {
                    double time = GetTime();
                    TakeScreenshot(TextFormat("ss-%i.png",time));
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
                    pausedFrom = GAMEVSCPU;
                    windowState = PAUSE;
                }
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
        mball.Draw();
        player2.Draw();
        player3.Draw();
        DrawRectangleRec(settingsButton, settingsButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(playButton, playButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
        DrawRectangleRec(editorButton, editorButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);

        // Draw button text
        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Play", playButton.x + buttonSize / 2 - MeasureText("Play", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Quit", editorButton.x + buttonSize / 2 - MeasureText("Editor", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);

            } break;
            case GAME: {
        gamescreen();
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
            case SETTINGS:{
                // Draw settings elements
                ClearBackground(BLUE);
                DrawText("Settings", screen_width / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
                DrawRectangle(screen_width / 2 + 20, screen_height / 2 - 90, toggleSize, toggleSize, toggle1 ? BLACK : GRAY);
                DrawRectangle(screen_width / 2 + 20, screen_height / 2 - 50, toggleSize, toggleSize, toggle2 ? BLACK : GRAY);
                DrawText(textInput, screen_width / 2 + 25, s