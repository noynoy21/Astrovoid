#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "game.h"

#define WIDTH 20         // The horizontal boundary of the game area
#define HEIGHT 20        // The vertical boundary of the game area
#define MAX_ENEMIES 6    // Maximum number of enemies active on screen at once
#define MAX_BULLETS 5    // Maximum number of bullets that can be fired simultaneously

// ===================== GAMEPLAY FUNCTION =====================
void playGame() {
    system("cls");         // Clear screen before starting game
    drawBorder();          // Draws outer frame of the playfield

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 }; // Player starts near bottom center
    Entity enemies[MAX_ENEMIES];                  // Array of enemies
    Entity bullets[MAX_BULLETS];                  // Array of bullets
    int score = 0;            // Tracks player's score
    char key;                 // Stores input key
    srand(time(0));           // Seed random generator for varied enemy spawns

    // Initialize enemies with random positions
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = rand() % (WIDTH - 2) + 1; // Random X inside play area
        enemies[i].y = rand() % 5 + 1;           // Y starts near top
        enemies[i].active = 1;                   // Enemy is active
    }

    // Deactivate all bullets at game start
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    // ===================== MAIN GAME LOOP =====================
    while (1) {
        // -------- Erase old positions to prepare for new frame --------
        erasePlayer(player.x, player.y);
        for (int i = 0; i < MAX_ENEMIES; i++)
            eraseEnemy(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);

        // -------- Handle Player Input --------
        if (_kbhit()) {                    // If a key is pressed
            key = _getch();                // Read it without waiting for Enter
            if (key == 'a' || key == 'A') player.x--;   // Move left
            if (key == 'd' || key == 'D') player.x++;   // Move right
            if (key == 'w' || key == 'W') player.y--;   // Move up
            if (key == 's' || key == 'S') player.y++;   // Move down

            // SPACEBAR: Fire a bullet upward
            if (key == 32) {               // ASCII code 32 = Space
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bullets[i].active) {     // Find first inactive bullet slot
                        bullets[i].x = player.x;  // Spawn bullet at player's position
                        bullets[i].y = player.y;
                        bullets[i].active = 1;    // Activate bullet
                        break;                    // Only fire one bullet per press
                    }
                }
            }

            if (key == 27) break;          // ESC (ASCII 27) exits game
        }

        // -------- Prevent player from leaving play area --------
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;
        if (player.y < 1) player.y = 1;
        if (player.y > HEIGHT - 2) player.y = HEIGHT - 2;

        // -------- Move enemies downward each frame --------
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].y++;                        // Move enemy down one unit
            if (enemies[i].y > HEIGHT - 1) {       // If enemy passes bottom
                enemies[i].y = 1;                  // Respawn at top
                enemies[i].x = rand() % (WIDTH - 2) + 1; // Random X position
            }
        }

        // -------- Move bullets upward --------
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;                    // Move up
                if (bullets[i].y < 1)              // If bullet goes off-screen
                    bullets[i].active = 0;         // Deactivate it
            }
        }

        // -------- Draw updated positions --------
        drawPlayer(player.x, player.y);            // Draw player
        for (int i = 0; i < MAX_ENEMIES; i++)
            drawEnemy(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) drawBullet(bullets[i].x, bullets[i].y);

        // -------- Check collision: Player vs Enemies --------
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (collision(player.x, player.y, enemies[i].x, enemies[i].y)) {
                explosionEffect(player.x, player.y);    // Explosion animation
                gotoxy(WIDTH / 2 - 5, HEIGHT / 2);      // Centered message
                setColor(12); printf("GAME OVER!");     // Red text
                gotoxy(WIDTH / 2 - 8, HEIGHT / 2 + 1);
                setColor(14); printf("Final Score: %d", score);
                setColor(7);
                _getch();                               // Wait for key
                return;                                 // Exit playGame()
            }
        }

        // -------- Check collision: Bullets vs Enemies --------
        for (int i = 0; i < MAX_ENEMIES; i++) {
            for (int j = 0; j < MAX_BULLETS; j++) {
                if (bullets[j].active &&
                    (collision(bullets[j].x, bullets[j].y, enemies[i].x, enemies[i].y) || collisionAdj(bullets[j].x, bullets[j].y, enemies[i].x, enemies[i].y))) {
                    eraseBullet(bullets[j].x, bullets[j].y);
                    bullets[j].active = 0;               // Disable bullet
                    explosionEffect(enemies[i].x, enemies[i].y); // Visual hit feedback
                    enemies[i].x = rand() % (WIDTH - 2) + 1;     // Respawn enemy at top
                    enemies[i].y = 1;
                    score += 5;                          // Increment score
                }
            }
        }

        // -------- Display the score beside play area --------
        gotoxy(WIDTH + 5, 2);
        setColor(10);
        printf("Score: %d  ", score);
        setColor(7);

        // -------- Delay for smoother movement (controls speed) --------
        Sleep(75);    // 75 ms delay between frames
    }
}
