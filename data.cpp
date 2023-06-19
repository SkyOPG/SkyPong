#include <pong.h>

const float buttonSize = 200;
const float buttonSpacing = 40;
const float titleFontSize = 60;
const float rotationSpeed = 2.0f;
const float toggleSize = 20;
float textx = 200;
float texty = 200;
float textsize = 40;
const float screen_width = 1280;
const float screen_height = 800;
Color sb = Color{ 135, 206, 235, 255 };
Color BC = Fade(sb, 0.5f);
Color G = Color{38, 185, 154, 255};
Color DG = Color{20, 160, 133, 255};
Color LG = Color{129, 204, 184, 255};
Color Y = Color{243, 213, 91, 255};
Color B = Color{30, 139, 159, 255};
bool toggle1 = false;
bool toggle2 = false;
bool toggle3 = false;
char textInput[256] = "";
Vector2 mousePosition = GetMousePosition();

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
Rectangle settingsButton = { screen_width / 2 - buttonSize / 2, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle playButton = { screen_width / 2 - buttonSize - buttonSpacing / 2 - 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle editorButton = { screen_width / 2 + buttonSpacing / 2 + 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
bool playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
bool editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
Color skyblue = Color{ 135, 206, 235, 255 };
Color buttonColor = Fade(skyblue, 0.5f);
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color Blue = Color{30, 139, 159, 255};
KeyboardKey Up, Down, P2Up, P2Down, Quit;
GameScreen pausedFrom = NAN;
GameScreen windowState = TITLE;

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
}