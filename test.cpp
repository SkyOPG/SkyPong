#include "raylib.h"

enum View { TITLE, SETTINGS, INGAME, EDITOR, PAUSE };

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int buttonSize = 100;
    const int buttonSpacing = 40;
    const int titleFontSize = 60;
    const float rotationSpeed = 2.0f;
    const int toggleSize = 20;

    InitWindow(screenWidth, screenHeight, "Main Menu");

    Rectangle settingsButton = { screenWidth / 2 - buttonSize / 2, screenHeight / 2 + buttonSpacing, buttonSize, buttonSize };
    Rectangle playButton = { screenWidth / 2 - buttonSize - buttonSpacing / 2 - 100, screenHeight / 2 + buttonSpacing, buttonSize, buttonSize };
    Rectangle editorButton = { screenWidth / 2 + buttonSpacing / 2 + 100, screenHeight / 2 + buttonSpacing, buttonSize, buttonSize };

    bool playButtonPressed = false;
    bool settingsButtonPressed = false;
    bool editorButtonPressed = false;

    float rotationAngle = 0.0f;

    View currentView = TITLE;

    Vector2 titlePosition = { screenWidth / 2 - MeasureText("SkyPong", titleFontSize) / 2, screenHeight / 4 };

    SetTargetFPS(60);

    Color buttonColor = Fade(SKYBLUE, 0.5f); // 50% opacity

    bool toggle1 = false;
    bool toggle2 = false;
    bool toggle3 = false;
    char textInput[256] = "";

    while (!WindowShouldClose())
    {
        // Update
        Vector2 mousePosition = GetMousePosition();

        playButtonPressed = CheckCollisionPointRec(mousePosition, playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
        settingsButtonPressed = CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
        editorButtonPressed = CheckCollisionPointRec(mousePosition, editorButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

        switch (currentView)
        {
            case TITLE:
                if (playButtonPressed)
                    currentView = INGAME;
                else if (settingsButtonPressed)
                    currentView = SETTINGS;
                else if (editorButtonPressed)
                    currentView = EDITOR;
                break;
            case INGAME:
                // Handle in-game logic and input
                if (IsKeyPressed(KEY_P))
                    currentView = PAUSE;
                break;
            case SETTINGS:
                // Handle settings logic and input
                if (IsKeyPressed(KEY_ESCAPE))
                    currentView = TITLE;
                break;
            case EDITOR:
                // Handle editor logic and input
                if (IsKeyPressed(KEY_ESCAPE))
                    currentView = TITLE;
                break;
            case PAUSE:
                // Handle pause menu logic and input
                if (IsKeyPressed(KEY_P))
                    currentView = INGAME;
                else if (IsKeyPressed(KEY_ESCAPE))
                    currentView = TITLE;
                break;
        }

        // Update rotation angle
        rotationAngle += rotationSpeed;

        if (rotationAngle > 360.0f)
            rotationAngle -= 360.0f;

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentView)
        {
            case TITLE:
                // Draw title with rotation
                DrawTextEx(GetFontDefault(), "SkyPong", titlePosition, titleFontSize, 0.0f, Fade(BLACK, 1.0f));

                // Draw buttons
                DrawRectangleRec(settingsButton, settingsButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
                DrawRectangleRec(playButton, playButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);
                DrawRectangleRec(editorButton, editorButtonPressed ? Fade(DARKBLUE, 0.8f) : buttonColor);

                // Draw button text
                DrawText("Settings", settingsButton.x + buttonSize / 2 - MeasureText("Settings", 20) / 2, settingsButton.y + buttonSize / 2 - 10, 20, WHITE);
                DrawText("Play", playButton.x + buttonSize / 2 - MeasureText("Play", 20) / 2, playButton.y + buttonSize / 2 - 10, 20, WHITE);
                DrawText("Editor", editorButton.x + buttonSize / 2 - MeasureText("Editor", 20) / 2, editorButton.y + buttonSize / 2 - 10, 20, WHITE);

                break;
            case INGAME:
                // Draw in-game elements
                DrawText("In-Game", screenWidth / 2 - MeasureText("In-Game", 30) / 2, screenHeight / 2, 30, BLACK);
                break;
            case SETTINGS:
                // Draw settings elements
                ClearBackground(BLUE);
                DrawText("Settings", screenWidth / 2 - MeasureText("Settings", 30) / 2, 20, 30, BLACK);
                DrawRectangle(screenWidth / 2 + 20, screenHeight / 2 - 90, toggleSize, toggleSize, toggle1 ? BLACK : GRAY);
                DrawRectangle(screenWidth / 2 + 20, screenHeight / 2 - 50, toggleSize, toggleSize, toggle2 ? BLACK : GRAY);
                DrawText(textInput, screenWidth / 2 + 25, screenHeight / 2 + 7, 20, BLACK);
                DrawRectangle(screenWidth / 2 + 20, screenHeight / 2 + 50, toggleSize, toggleSize, toggle3 ? BLACK : GRAY);
                break;
            case EDITOR:
                // Draw editor elements
                DrawText("Editor", screenWidth / 2 - MeasureText("Editor", 30) / 2, screenHeight / 2, 30, BLACK);
                break;
            case PAUSE:
                // Draw pause menu elements
                DrawText("Pause", screenWidth / 2 - MeasureText("Pause", 30) / 2, screenHeight / 2, 30, BLACK);
                break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
