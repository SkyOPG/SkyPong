#include <pong.h>

Rectangle rec1 = { 340, 300, 250, 350 };
Rectangle rec2 = { 740, 300, 250, 350 };

void GameModeChooser(Theme gameTheme) {
        DrawTable(gameTheme);
        DrawRectangleRec(rec1, Fade(LIGHTGRAY, 0.5f));
        DrawRectangleRec(rec2, Fade(LIGHTGRAY, 0.5f));
        DrawText("VS PC", 797, 454, 40, RAYWHITE);
        DrawText("VS Friend", 358, 453, 40, RAYWHITE);
}