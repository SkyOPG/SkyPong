#include <aa.h>
#include <aaa.h>

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
bool playButtonPressed = false;
bool settingsButtonPressed = false;
bool editorButtonPressed = false;
Color sb = Color{ 135, 206, 235, 255 };
Color BC = Fade(sb, 0.5f);
Color G = Color{38, 185, 154, 255};
Color DG = Color{20, 160, 133, 255};
Color LG = Color{129, 204, 184, 255};
Color Y = Color{243, 213, 91, 255};
Color B = Color{30, 139, 159, 255};

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
