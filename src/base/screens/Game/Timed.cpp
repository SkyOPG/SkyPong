#include <pong.h>

void LoadTimedScreen(Ball timeBall, Paddle cpu, Paddle player, Theme gameTheme, int players, int cpus) {
        timeBall.Update(cpus, players);
        player.Update(timeBall.y);
        cpu.Update(timeBall.y);

        if (CheckCollisionCircleRec(Vector2{timeBall.x, timeBall.y}, timeBall.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            timeBall.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{timeBall.x, timeBall.y}, timeBall.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            timeBall.speed_x *= -1;
        }

        DrawTable(gameTheme);
        timeBall.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i", cpus), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", players), 3 * screen_width / 4 - 20, 20, 80, WHITE);
}