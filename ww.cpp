#include "raylib.h"
#include "webwise.h"
#include <cstddef>

// Shader source code
const char *motionBlurShaderCode = R"(
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 resolution;
uniform float alphaDecay;

out vec4 finalColor;

void main()
{
    vec4 color = vec4(0.0);
    vec2 texelSize = vec2(1.0 / resolution.x, 1.0 / resolution.y);
    
    // Sample the texture multiple times with offsets to create blur
    for (int i = 0; i < 10; i++)
    {
        float offset = float(i) * alphaDecay;
        vec2 sampleCoord = fragTexCoord + vec2(offset * texelSize.x, offset * texelSize.y);
        color += texture(texture0, sampleCoord) * (1.0 - offset);
    }

    finalColor = color / 10.0;
}
)";

int main(void)
{
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
	
    InitWindow(screenWidth, screenHeight, "i hate my life");

	Image image = {
        .data = WEBWISE_DATA,  // This is the name of the image data array in the header file
        .width = WEBWISE_WIDTH,
        .height = WEBWISE_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    // Load the logo
    Texture2D logo = LoadTextureFromImage(image);

    // Load shader
    Shader motionBlurShader = LoadShaderFromMemory(NULL, motionBlurShaderCode);
    Vector2 resolution = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(motionBlurShader, GetShaderLocation(motionBlurShader, "resolution"), &resolution, SHADER_UNIFORM_VEC2);
    float alphaDecay = 0.05f;  // Alpha decay for motion blur
    SetShaderValue(motionBlurShader, GetShaderLocation(motionBlurShader, "alphaDecay"), &alphaDecay, SHADER_UNIFORM_FLOAT);

    // Define animation parameters
	bool fadeout = false;
    float logoScale = 0.0f;  // Start with a small scale
    Vector2 logoPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    float alpha = 0.0f;  // Start with fully transparent
    float scaleSpeed = 0.005f;  // Scale speed
    float alphaSpeed = 0.01f;   // Alpha speed

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        if (alpha < 1.0f && !fadeout) alpha += alphaSpeed;
		else alpha -= alphaSpeed;

        if (logoScale < 0.6f) logoScale += scaleSpeed;
		else {
			fadeout = true;
			logoScale += scaleSpeed * 4;
		}

        logoPosition.x = screenWidth / 2.0f - (logo.width * logoScale) / 2;
        logoPosition.y = screenHeight / 2.0f - (logo.height * logoScale) / 2;

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);  // Black background

        // Draw the logo with the shader
        BeginShaderMode(motionBlurShader);
        DrawTextureEx(logo, logoPosition, 0.0f, logoScale, Fade(WHITE, alpha));
        EndShaderMode();
        
        EndDrawing();
    }

    // De-Initialization
    UnloadTexture(logo);  // Unload logo texture
    UnloadShader(motionBlurShader);  // Unload shader
    CloseWindow();  // Close window and OpenGL context

    return 0;
}
