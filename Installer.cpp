#include <raylib.h>
#include "webwise.h"
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 450;
typedef enum window { loading, title } window;

window Window = window::loading;

Color CalculateAlpha(float alpha) {
    Color color = WHITE;
    int transparency = static_cast<int>(alpha * 255);
    color.r = (color.r * transparency) / 255;
    color.g = (color.g * transparency) / 255;
    color.b = (color.b * transparency) / 255;
    color.a = transparency;
    return color;
}

void UpdateAnimationData(float& alpha, bool& fadeout, float& alphaSpeed, float& logoScale, float& scaleSpeed, Vector2& logoPosition, int logoWidth, int logoHeight) {
    if (alpha < 1.0f && !fadeout) alpha += alphaSpeed;
    else if(alpha < 0.1f && fadeout) Window = window::title;
	else alpha -= alphaSpeed;

    if (logoScale < 0.6f) logoScale += scaleSpeed;
    else {
        fadeout = true;
        logoScale += scaleSpeed * 4;
    }

    logoPosition.x = screenWidth / 2.0f - (logoWidth * logoScale) / 2;
    logoPosition.y = screenHeight / 2.0f - (logoHeight * logoScale) / 2;
}

void DrawAnimation(Texture2D logo, Vector2 logoPosition, float logoScale, float alpha) {
	ClearBackground(BLACK);
    DrawTextureEx(logo, logoPosition, 0.0f, logoScale, CalculateAlpha(alpha));
}

void TitleAnimation(bool& done, int frames, Font font){
	ClearBackground(BLACK);
	std::cout << frames << std::endl;
	Rectangle rec = { 0, 0, (frames * 4) > GetRenderWidth() ? GetRenderWidth() : frames * 4 ,(frames * 4) > 40 ? 40 : frames * 4 };
	DrawRectangleRounded(rec, 0.8, 0, WHITE);
	DrawTextPro(font, "Installer", (Vector2){20, 10}, (Vector2){0, 0}, 0, 24, 1.0f, BLACK);
}

int main() {
    InitWindow(screenWidth, screenHeight, "webwise game installer");
    SetTargetFPS(60);
	Font Inter = LoadFontEx("./inter.ttf", 24, 0, 250);
    Image image = {
        .data = WEBWISE_DATA,
        .width = WEBWISE_WIDTH,
        .height = WEBWISE_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    Texture2D logo = LoadTextureFromImage(image);

    bool fadeout = false;
    float logoScale = 0.0f;
    Vector2 logoPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    float alpha = 0.0f;
    float scaleSpeed = 0.005f;
	bool done = false;
	int frames = 0;
    float alphaSpeed = 0.01f;

    while (!WindowShouldClose()) {
		std::cout << alpha << std::endl;
		switch (Window){
		case window::loading:
			UpdateAnimationData(alpha, fadeout, alphaSpeed, logoScale, scaleSpeed, logoPosition, logo.width, logo.height);
		break;
		case window::title:
//			UpdateTitleAnimationData();
			break;
		default:
			break;
		}
        BeginDrawing();
        switch (Window){
		case window::loading:
			DrawAnimation(logo, logoPosition, logoScale, alpha);
		break;
		case window::title:
			TitleAnimation(done, frames, Inter);
		break;
		default:
			break;
		}
		DrawFPS((screenWidth / 2) - TextLength("10 fps"),10);
        EndDrawing();
		frames++;
    }

    UnloadTexture(logo);
    CloseWindow();

    return 0;
}
