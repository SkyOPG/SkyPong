#include <raylib.h>
#include <iostream>
#include <vector>
bool HighDef = false;
int main(int argc, char* argv[]){
    InitWindow(960, 540, "idk");
    SetTargetFPS(60);
    std::vector<Texture2D> idk{};
    if(argv[1] == "-hd")
        SetWindowSize(1920, 1080);
    
    int num = 0;
    while (!WindowShouldClose()) {
            Image img = LoadImage(TextFormat("frames/frame_%i.png", num));
            if(argv[1] != "-hd")
                ImageResize(&img, 960, 540);
            Texture2D texture = LoadTextureFromImage(img);
            UnloadImage(img);
        
        BeginDrawing();
            ClearBackground(BLUE);
            DrawText("hi bro", 69, 69, 40, BLACK);
            DrawTexture(texture, 0, 0, WHITE);
            DrawFPS(20, 20);
        EndDrawing();
        UnloadTexture(texture);
        num++;
    }

    CloseWindow();
}
