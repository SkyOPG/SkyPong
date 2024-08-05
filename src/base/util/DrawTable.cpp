#include <pong.h>

Color purple = Color{90, 34, 139, 1};
Color lpurple = Color{102, 51, 153, 255};
Color wite = Color{255,255,255,255};
Color blak = Color{0,0,0,0};
Color G = Color{38, 185, 154, 255};
Color DG = Color{20, 160, 133, 255};
Color LG = Color{129, 204, 184, 255};
Color Y = Color{243, 213, 91, 255};
Color buttonColor = Color{30, 139, 159, 255};
Color otherBlue = Color{30, 139, 159, 0};
Color pc = wite;

void DrawTable(Theme theme) {
    switch(theme){
        case NORMAL: {
             ClearBackground(DG);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, G);
             DrawCircle(screen_width / 2, screen_height / 2, 150, LG);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = wite;
//             btclr1 = buttonColor;
//             btclr2 = otherBlue;
        } break;
        case RETRO: {
             ClearBackground(BLACK);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, BLACK);
             DrawCircle(screen_width / 2, screen_height / 2, 150, WHITE);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = wite;
//             btclr1 = Fade(LIGHTGRAY, 0.5f);
//             btclr2 = Fade(GRAY, 0.5f);
        } break;
        case PARTY: {
             ClearBackground(purple);
             DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, lpurple);
             DrawCircle(screen_width / 2, screen_height / 2, 150, WHITE);
             DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
             pc = blak;
//             btclr1 = Fade(lpurple, 0.5f);
//             btclr2 = Fade(purple, 0.5f);
        } break;
    }
}