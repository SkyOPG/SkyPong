#include <raylib.h>

// custom type definitions by raylib
Color sb = Color{ 135, 206, 235, 255 }; // sky blue
Color BC = Fade(sb, 0.5f); // sky blue but 50% opacity
Color G = Color{38, 185, 154, 255}; // green
Color DG = Color{20, 160, 133, 255}; // dark green
Color LG = Color{129, 204, 184, 255}; // light green
Color Y = Color{243, 213, 91, 255}; // yellow
Color B = Color{30, 139, 159, 255}; // blue
Color skyblue = Color{ 135, 206, 235, 255 }; // sky blue (again)
Color buttonColor = Fade(skyblue, 0.5f); // sky blue but 50% opacity (again)
Color Green = Color{38, 185, 154, 255}; // green (again)
Color Dark_Green = Color{20, 160, 133, 255}; // dark green (again)
Color Light_Green = Color{129, 204, 184, 255}; // light green (again)
Color Yellow = Color{243, 213, 91, 255}; // yellow (again)
Color Blue = Color{30, 139, 159, 255}; // blue (again)
Color otherBlue = Color{30, 139, 159, 1};
KeyboardKey Up, Down, P2Up, P2Down, Quit; // keybinds
extern int cpu_score;
extern int player_score;
