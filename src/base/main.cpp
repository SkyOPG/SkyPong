#include <pong.h>
#define midwidth screen_width / 2
#define midheight screen_height / 2
#define GLSL_VERSION            330

using namespace std;
float toggleSize = 57;
Rectangle settingsButton = { midwidth - buttonSize / 2, midheight + buttonSpacing, buttonSize, buttonSize };
Rectangle playButton = { midwidth - buttonSize - buttonSpacing / 2 - 100, midheight + buttonSpacing, buttonSize, buttonSize };
Rectangle editorButton = { midwidth + buttonSpacing / 2 + 100, midheight + buttonSpacing, buttonSize, buttonSize };

Theme gameTheme = NORMAL;
Theme song = NORMAL;
char* Themetext;
Color btclr1, btclr2;

GameScreen pausedFrom = NAN;
GameScreen windowState = LOADING;
RPCAt RPC = NO;
matchMode match = NONE;

float addwidth = 0;
int cpuScore = 0;
int playerScore = 0;
int a = 0;
int b = 0;

int main(void) {
    Image loogo = LoadImage("./resources/icons/webwise.png");
    Image smallWW = LoadImage("./resources/icons/webwise_small.png");
    Image icon = LoadImage("./resources/icons/icon.png");
    char* title = "SkyPong";
    StartWindow(icon, title);
    Sound sretro = LoadSound("./resources/music/retro.mp3");
    Shader glowShader = LoadShader("resources/shaders/glow.vs", "resources/shaders/glow.fs");

    float voice = 0.5;

    bool initted = true;
    Texture2D logo = LoadTextureFromImage(loogo);
    int frames = 0;
    Color black = BLACK;
    bool build = false;
    while (!WindowShouldClose() && initted){
        Vector2 mousePosition = GetMousePosition();
        ButtonPressed isPressed = checkCollisions(mousePosition);
        KeyEvents(windowState, RPC, isPressed, initted, match, pausedFrom, voice, sretro, gameTheme, frames, black, WebWiseLogoPos, build, a);
        BeginDrawing();
        switch(windowState){
            case LOADING: {
                if(frames == 30){
                    frames = 0;
                    a += 85;
                    b += 30;
                }
                Image idk = ImageCopy(smallWW.width + a >= 680 ? loogo : smallWW);
                ImageResize(&idk, smallWW.width +a, smallWW.height + b);
                Texture2D thgf = LoadTextureFromImage(idk);
                Vector2D WebWiseLogoPos = { (screen_width - thgf.width) / 2, (screen_height - thgf.height) / 2 };
                BeginShaderMode(glowShader);
                LoadingScreen(thgf, WebWiseLogoPos.x, WebWiseLogoPos.y, black);
                EndShaderMode();
            } break;
            default: break;
        }
        EndDrawing();
    }
    end();
    CloseWindow();

        return 0;
}

/*
    char* Themetext;
        

    BeginDrawing();
        switch(windowState){
            case LOADING: {
                ClearBackground(BLACK);
                DrawTexture(logo, 0, 0, BLACK);
            } break;
            case TITLE: {

        player.automatic = true;
        player2.automatic = true;
        int idk = 0;
        LoadGame(ball, gameTheme, player, player2, idk, idk);
        DrawRectangleRec(settingsButton, isPressed.settings ? btclr2 : btclr1);
        DrawRectangleRec(playButton, isPressed.play ? btclr2 : btclr1);
        DrawRectangleRec(editorButton, isPressed.editor ? btclr2 : btclr1);
        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Play", playButton.x + buttonSize / 2 - MeasureText("Play", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Quit", editorButton.x + buttonSize / 2 - MeasureText("Quit", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);   
            } break;
            case GAME: {
        GameModeChooser(gameTheme);
            } break;
            case GAMEVSCPU: {
            player2.automatic = true;
            Vector2 score = LoadGame(ball, gameTheme, player, player2, playerScore, cpuScore);
            playerScore = score.x;
            cpuScore = score.y;
            } break;
            case PAUSE: {
        DrawTable(gameTheme);
        switch(pausedFrom){
            case GAMEVSCPU: {
                player2.Draw();
            } break;
            case GAMEVSPLAYER: {
                player2.Draw();
            } break;
			default:
				break;
        }
        ball.Draw();
        player.Draw();
        DrawText("Paused", screen_width / 2 - MeasureText("Paused", 50) / 2, 20, 50, BLACK);
         DrawRectangleRec(settingsButton, isPressed.settings ? btclr2 : btclr1);
         DrawRectangleRec(playButton, isPressed.play ? btclr2 : btclr1);
         DrawRectangleRec(editorButton, isPressed.editor ? btclr2 : btclr1);

        DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Resume", playButton.x + buttonSize / 2 - MeasureText("Resume", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
        DrawText("Menu", editorButton.x + buttonSize / 2 - MeasureText("Menu", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);
            } break;
            case GAMEVSPLAYER: {
		        player2.automatic = false;
                LoadGame(ball, gameTheme, player, player2, playerScore, cpuScore);
            } break;
            case TIMED: {
                LoadTimedScreen(ball, player2, player, gameTheme, playerScore, cpuScore);
            } break;
            case SETTINGS:{
                toggleSize = 57;
                int safe = voice * 100;
            DrawTable(gameTheme);
            DrawText("Settings", screen_width / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
            DrawText(TextFormat("%i", safe), 84, 77, 51, WHITE);
            DrawText("Volume", 53, 18, 32, WHITE);
            DrawText("Theme", 52, 189, 37, WHITE);
            DrawText(">", 160, 65, 77, WHITE);
            DrawText("<", 27, 65, 77, WHITE);
            DrawText(Themetext, 41, 257, 41, WHITE);

            } break;
            default: break;
        }
        
        EndDrawing();
 */