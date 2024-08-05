#include <raylib.h>

const float screen_width = 1280;
const float screen_height = 800;
const float buttonSize = 200, buttonSpacing = 40, titleFontSize = 60, rotationSpeed = 2.0f;

Rectangle sbutton = { screen_width / 2 - buttonSize / 2, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle pButton = { screen_width / 2 - buttonSize - buttonSpacing / 2 - 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle eButton = { screen_width / 2 + buttonSpacing / 2 + 100, screen_height / 2 + buttonSpacing, buttonSize, buttonSize };
Rectangle rectoggle1 = { 17, 72, 57, 57 };
Rectangle rectoggle2 = { 140, 72, 57, 57 };
Rectangle rectoggle3 = { 19, 246, 57 + 129 , 57 };
Rectangle r1 = { 340, 300, 250, 350 };
Rectangle r2 = { 740, 300, 250, 350 };

struct ButtonPressed {
	bool play;
	bool settings;
	bool editor;
	bool toggle1;
	bool toggle2;
	bool toggle3;
	bool r1;
	bool r2;
};

ButtonPressed checkCollisions(Vector2 mousePosition){
	bool playButtonPressed = CheckCollisionPointRec(mousePosition, pButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool sbuttonPressed = CheckCollisionPointRec(mousePosition, sbutton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool editorButtonPressed = CheckCollisionPointRec(mousePosition, eButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool toggle1Pressed = CheckCollisionPointRec(mousePosition, rectoggle1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool toggle2Pressed = CheckCollisionPointRec(mousePosition, rectoggle2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool toggle3Pressed = CheckCollisionPointRec(mousePosition, rectoggle3) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool rec1Pressed = CheckCollisionPointRec(mousePosition, r1) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	bool rec2Pressed = CheckCollisionPointRec(mousePosition, r2) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);

	return {
		playButtonPressed,
		sbuttonPressed,
		editorButtonPressed,
		toggle1Pressed,
		toggle2Pressed,
		toggle3Pressed,
		rec1Pressed,
		rec2Pressed
	};
}