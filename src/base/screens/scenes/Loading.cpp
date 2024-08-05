#include <raylib.h>

void LoadingScreen(Texture2D logo, int x, int y, Color& color){
	ClearBackground(color);
    DrawTexture(logo, x, y, WHITE);
}