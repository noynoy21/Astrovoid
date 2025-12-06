#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameRound1.h"
#include "config.h"

int playRound1() {
    system("cls");
    drawBorder(WIDTH, HEIGHT);

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity hitts[MAX_HITTABLES];
    int score = 0;
    int life = MAX_PLAYER_LIFE;
    int maxLife = life;
    char key;
    srand(time(0));

    // Initialize enemies with random positions
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = rand() % (WIDTH - 2) + 1;
        enemies[i].y = rand() % 5 + 1;
        enemies[i].active = 1;
    }

    // Initialize hittables with random positions
    for (int i = 0; i < MAX_HITTABLES; i++) {
        hitts[i].x = rand() % (WIDTH - 2) + 1;
        hitts[i].y = rand() % 5 + 1;
        hitts[i].active = 1;
    }

    // Deactivate all bullets at game start
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    // ===================== MAIN GAME LOOP =====================
    while (1) {
        // Erase old positions
        erasePlayer(player.x, player.y);
        for (int i = 0; i < MAX_ENEMIES; i++)
            eraseEnemy(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_HITTABLES; i++)
            eraseObj(hitts[i].x, hitts[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);

        // Handle Player Input
        if (_kbhit()) {
            key = _getch();
            if (key == 'a' || key == 'A') player.x--;
            if (key == 'd' || key == 'D') player.x++;

            // SPACEBAR: Fire a bullet upward
            if (key == 32) {
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bullets[i].active) {
                        bullets[i].x = player.x;
                        bullets[i].y = HEIGHT - 2;
                        bullets[i].active = 1;
                        break;
                    }
                }
            }

            if (key == 27) return 0; // If player exits
        }

        // Prevent player from leaving play area
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;

        // Move enemies downward
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].y++;
            if (enemies[i].y > HEIGHT - 1) {
                enemies[i].y = 1;
                enemies[i].x = rand() % (WIDTH - 2) + 1;
            }
        }

        // Move hittables downward
        for (int i = 0; i < MAX_HITTABLES; i++) {
            hitts[i].y++;
            if (hitts[i].y > HEIGHT - 1) {
                hitts[i].y = 1;
                hitts[i].x = rand() % (WIDTH - 2) + 1;
            }
        }

        // Move bullets upward
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;
                if (bullets[i].y < 1)
                    bullets[i].active = 0;
            }
        }

        // Draw updated objects
        drawPlayer(player.x, player.y);
        for (int i = 0; i < MAX_ENEMIES; i++)
            drawEnemy(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_HITTABLES; i++)
            drawHittable(hitts[i].x, hitts[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) drawBullet(bullets[i].x, bullets[i].y);

        // Check collision: Player vs Enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (collision(player.x, player.y, enemies[i].x, enemies[i].y)) {
                explosionEffect(player.x, player.y);
                life--;
            }
        }

        // Check collision: Bullets vs Hittables
        for (int i = 0; i < MAX_HITTABLES; i++) {
            for (int j = 0; j < MAX_BULLETS; j++) {
                int coll = (collision(bullets[j].x, bullets[j].y, hitts[i].x, hitts[i].y) || 
                           collisionAdj(bullets[j].x, bullets[j].y, hitts[i].x, hitts[i].y));

                if (bullets[j].active && coll) {
                    eraseBullet(bullets[j].x, bullets[j].y);
                    bullets[j].active = 0;
                    explosionEffect(hitts[i].x, hitts[i].y);
                    hitts[i].x = rand() % (WIDTH - 2) + 1;
                    hitts[i].y = 1;
                    score += 1;
                }
            }
        }

        int numBullets = MAX_BULLETS;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                numBullets--;
            }
        }
        drawHud(score, life, maxLife, numBullets);

        // Player wins round 1
        if (score >= 10) {
            GPlayerScore = score;
            return life;
        }
        
        // Player loses round 1
        if (life <= 0) {
            gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
            setColor(12); printf("GAME OVER!");
            gotoxy(WIDTH / 2 - 8, HEIGHT / 2 + 1);
            setColor(14); printf("Final Score: %d", score);
            setColor(7);
            _getch();
            return 0;
        }

        Sleep(75);
    }
}