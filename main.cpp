#include "raylib.h"
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

struct Player {
    int x = 0, y = 0;
    int health = 100, maxHealth = 100;
    int exp = 0, level = 1;
};

// Game States
enum GameState { EXPLORING, BATTLE, WON, LOST };

int main() {
    srand(static_cast<unsigned int>(time(0)));
    InitWindow(600, 700, "C++ Dungeon Crawler - Boss Edition"); // Taller for UI
    SetTargetFPS(60);

    Player p;
    GameState currentState = EXPLORING;
    bool hasSword = false;
    int bossHP = 50;
    char battleMsg[50] = "A Boss appears! Press Space to Attack!";

    while (!WindowShouldClose()) {
        // --- 1. UPDATE LOGIC ---
        if (currentState == EXPLORING) {
            bool moved = false;
            if (IsKeyPressed(KEY_W) && p.y > 0) { p.y--; moved = true; }
            if (IsKeyPressed(KEY_S) && p.y < 2) { p.y++; moved = true; }
            if (IsKeyPressed(KEY_A) && p.x > 0) { p.x--; moved = true; }
            if (IsKeyPressed(KEY_D) && p.x < 2) { p.x++; moved = true; }

            if (moved) {
                p.exp += 10;
                // Random Trap (10% chance)
                if (GetRandomValue(0, 100) < 10) {
                    p.health -= 10;
                }
            }

            // Level Up Check
            if (p.exp >= 50) {
                p.level++; p.exp = 0; p.maxHealth += 20; p.health = p.maxHealth;
            }

            // Trigger Boss Battle at (2, 2)
            if (p.x == 2 && p.y == 2) currentState = BATTLE;
            if (p.x == 1 && p.y == 1) hasSword = true;
            if (p.health <= 0) currentState = LOST;

        } else if (currentState == BATTLE) {
            if (IsKeyPressed(KEY_SPACE)) {
                // Player Attacks
                int dmg = hasSword ? GetRandomValue(15, 25) : GetRandomValue(5, 15);
                bossHP -= dmg;
                
                // Boss Attacks Back
                if (bossHP > 0) p.health -= GetRandomValue(5, 12);
                
                if (bossHP <= 0) currentState = WON;
                if (p.health <= 0) currentState = LOST;
            }
        }

        // --- 2. DRAWING LOGIC ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == EXPLORING) {
            // Draw Grid
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) 
                    DrawRectangleLines(i * 200, j * 200, 200, 200, LIGHTGRAY);
            }
            if (!hasSword) DrawCircle(300, 300, 20, GOLD); // Sword at (1,1)
            DrawRectangle(410, 410, 180, 180, GREEN); // Exit
            DrawRectangle(p.x * 200 + 50, p.y * 200 + 50, 100, 100, BLUE); // Player
        } 
        else if (currentState == BATTLE) {
            DrawRectangle(0, 0, 600, 600, MAROON);
            DrawText("BOSS BATTLE", 180, 100, 40, WHITE);
            DrawText(TextFormat("Boss HP: %i", bossHP), 230, 200, 30, YELLOW);
            DrawText(battleMsg, 120, 400, 20, WHITE);
        }
        else if (currentState == WON) {
            DrawText("VICTORY! YOU ESCAPED!", 100, 300, 30, GREEN);
        }
        else if (currentState == LOST) {
            DrawText("GAME OVER - YOU DIED", 120, 300, 30, RED);
        }

        // Stats UI Area (Bottom)
        DrawRectangle(0, 600, 600, 100, BLACK);
        DrawText(TextFormat("HP: %i/%i", p.health, p.maxHealth), 20, 620, 20, RED);
        DrawText(TextFormat("LVL: %i", p.level), 200, 620, 20, SKYBLUE);
        DrawText(TextFormat("XP: %i/50", p.exp), 350, 620, 20, LIME);
        if (hasSword) DrawText("SWORD EQUIPPED", 20, 660, 20, ORANGE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}