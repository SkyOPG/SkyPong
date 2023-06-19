#include <aa.h>
#include <a.h>
#include <aaa.h>

using namespace std;


int main(void) {
    init();

    cout << "Starting the game" << endl;
    Image logo = LoadImage("./resources/icon.png");
    InitWindow(screen_width, screen_height, "SkyPong");
    InitAudioDevice();
    SetExitKey(KEY_NULL);
    SetWindowIcon(logo);
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
        title();

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
