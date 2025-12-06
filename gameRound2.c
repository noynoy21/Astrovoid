#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameRound2.h"
#include "menu.h"
#include "config.h"

#define ADDITIONAL_LIFE 2

// ===================== ROUND 2 GAMEPLAY =====================
int playRound2(int life) {
    system("cls");
    drawBorder(WIDTH, HEIGHT);

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity hitts[MAX_HITTABLES];
    int score = GPlayerScore;
    int maxLife = life;
    char key;
    srand(time(0));

    // Initialize enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = rand() % (WIDTH - 2) + 1;
        enemies[i].y = rand() % 5 + 1;
        enemies[i].active = 1;
    }

    // Initialize hittables
    for (int i = 0; i < MAX_HITTABLES; i++) {
        hitts[i].x = rand() % (WIDTH - 2) + 1;
        hitts[i].y = rand() % 5 + 1;
        hitts[i].active = 1;
    }

    // Deactivate all bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    // Display Round 2 message
    gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
    setColor(14);
    printf("ROUND 2!");
    Sleep(1500);
    system("cls");
    drawBorder(WIDTH, HEIGHT);

    // ===================== MAIN GAME LOOP =====================
    while (1) {
        // Erase old positions
        erasePlayer(player.x, player.y);
        for (int i = 0; i < MAX_ENEMIES; i++)
            eraseObj(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_HITTABLES; i++)
            eraseObj(hitts[i].x, hitts[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseObj(bullets[i].x, bullets[i].y);

        // Handle Player Input
        if (_kbhit()) {
            key = _getch();
            if (key == 'a' || key == 'A') player.x--;
            if (key == 'd' || key == 'D') player.x++;

            // SPACEBAR: Fire a bullet
            if (key == 32) {
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bullets[i].active) {
                        bullets[i].x = player.x;
                        bullets[i].y = player.y;
                        bullets[i].active = 1;
                        break;
                    }
                }
            }

            if (key == 27) return 0; // If player wants to exit
        }

        // Boundary checking
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;

        // Move enemies (slightly faster in round 2)
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].y++;
            if (enemies[i].y > HEIGHT - 1) {
                enemies[i].y = 1;
                enemies[i].x = rand() % (WIDTH - 2) + 1;
            }
        }

        // Move hittables
        for (int i = 0; i < MAX_HITTABLES; i++) {
            hitts[i].y++;
            if (hitts[i].y > HEIGHT - 1) {
                hitts[i].y = 1;
                hitts[i].x = rand() % (WIDTH - 2) + 1;
            }
        }

        // Move bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;
                if (bullets[i].y < 1)
                    bullets[i].active = 0;
            }
        }

        // Draw updated positions
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

        // Check if mini-boss should spawn (15 is when the miniboss spawns)
        if (score >= 15) {
            GPlayerScore = score;
            return life;
        }

        if (life <= 0) {
            gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
            setColor(12); printf("GAME OVER!");
            gotoxy(WIDTH / 2 - 8, HEIGHT / 2 + 1);
            setColor(14); printf("Final Score: %d", score);
            setColor(7);
            _getch();
            return 0;
        }

        Sleep(65);  // Slightly faster than round 1
    }
}




// ===================== MINI-BOSS BATTLE =====================
int playMiniBoss(int life) {
    system("cls");
    drawBorder(WIDTH, HEIGHT);
    srand(time(NULL));

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MINI_BOSS_MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity bullets1[MAX_BULL_BOSS];
    Entity bullets2[MAX_BULL_BOSS];

    int life_Boss = MINI_BOSS_LIFE;
    life += 2;
    int maxLife = life;
    int score = GPlayerScore;
    char key;

    // Initialize enemies
    for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++) {
        enemies[i].x = rand() % (WIDTH - 2) + 1;
        enemies[i].y = rand() % 5 + 1;
        enemies[i].active = 1;
    }
    // Initialize player bullets
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;
    //Initialize miniboss bullets
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets1[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets2[i].active = 0;

    body MiniBoss = {
        { WIDTH / 4, 1, 1.0},
        {
            "xvvvvvx",
            " Iv!vI ",
            " ! o ! ",
        }
    };

    int bulletCooldown = 0;

    // Display Mini-Boss warning
    gotoxy(WIDTH / 2 - 6, HEIGHT / 2);
    setColor(14);
    printf("MINI-BOFF!");
    Sleep(1500);
    system("cls");
    drawBorder(WIDTH, HEIGHT);

    while (1) {
        // Erase previous player sprite
        erasePlayer(player.x, player.y);
        // Erase previous boss character
        clearBossEntity((int)MiniBoss.boss.x, (int)MiniBoss.boss.y, MINIBOSS_H, MINIBOSS_W);
        // Erase previous enemy sprites
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++)
            eraseObj(enemies[i].x, enemies[i].y);
        // Erase player bullets
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);
        // Erase miniboss bullets
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) eraseBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) eraseBossBullet(bullets2[i].x, bullets2[i].y);
        }

        // Handle Player Input
        if (_kbhit()) {
            key = _getch();
            // move player in case of valid player input
            if (key == 'a' || key == 'A') player.x--;
            if (key == 'd' || key == 'D') player.x++;

            if (key == 32) { // player hits spacebar
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bullets[i].active) {
                        bullets[i].x = player.x;
                        bullets[i].y = player.y;
                        bullets[i].active = 1;
                        break;
                    }
                }
            }

            if (key == 27) return 0;
        }

        // Boundary checking
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;

        // Move enemies (slightly faster in round 2)
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++) {
            enemies[i].y++;
            if (enemies[i].y > HEIGHT - 1) {
                enemies[i].y = 1;
                enemies[i].x = rand() % (WIDTH - 2) + 1;
            }
        }

        // Move bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;
                if (bullets[i].y < 1)
                    bullets[i].active = 0;
            }
        }

        // Draw player and bullets and enemies
        drawPlayer(player.x, player.y);
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++)
            drawEnemy(enemies[i].x, enemies[i].y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) drawBullet(bullets[i].x, bullets[i].y);

        // Move mini-boss (simple left-right pattern)
        move1(&MiniBoss.boss.x, &MiniBoss.boss.y, &MiniBoss.boss.direction);

        // Spawn bullets from mini-boss (less frequent)
        if (bulletCooldown <= 0) {
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets1[i].active) {
                    bullets1[i].active = 1;
                    bullets1[i].x = (int)MiniBoss.boss.x + 1;
                    bullets1[i].y = (int)MiniBoss.boss.y + 2;
                    break;
                }
            }
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets2[i].active) {
                    bullets2[i].active = 1;
                    bullets2[i].x = (int)MiniBoss.boss.x + 5;
                    bullets2[i].y = (int)MiniBoss.boss.y + 2;
                    break;
                }
            }
            bulletCooldown = 25;  // Slower than full boss
        } else bulletCooldown--;

        // Move boss bullets downward
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) {
                bullets1[i].y++;
                if (bullets1[i].y > HEIGHT-1) bullets1[i].active = 0;
            }
            if (bullets2[i].active) {
                bullets2[i].y++;
                if (bullets2[i].y > HEIGHT-1) bullets2[i].active = 0;
            }
        }

        // Draw mini-boss and bullets
        drawBossEntity((int)MiniBoss.boss.x, (int)MiniBoss.boss.y, MiniBoss.sizes, MINIBOSS_H, MINIBOSS_W);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) drawBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) drawBossBullet(bullets2[i].x, bullets2[i].y);
        }

        // Check collision: Player bullets vs Mini-Boss
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) continue;

            if (bullets[i].x >= (int)MiniBoss.boss.x &&
                bullets[i].x <= (int)MiniBoss.boss.x + 6 &&
                bullets[i].y >= (int)MiniBoss.boss.y &&
                bullets[i].y <= (int)MiniBoss.boss.y + 2) {

                bullets[i].active = 0;
                life_Boss--;
                explosionBossEffect(bullets[i].x, bullets[i].y);
            }
        }

        // Check collision: Boss bullets vs Player
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active &&
                bullets1[i].x == player.x &&
                bullets1[i].y == player.y) {
                bullets1[i].active = 0;
                life--;
                explosionBossEffect(player.x, player.y);
            }

            if (bullets2[i].active &&
                bullets2[i].x == player.x &&
                bullets2[i].y == player.y) {
                bullets2[i].active = 0;
                life--;
                explosionBossEffect(player.x, player.y);
            }
        }

        // Check collision: Player vs Enemies
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++) {
            if (collision(player.x, player.y, enemies[i].x, enemies[i].y)) {
                explosionEffect(player.x, player.y);
                life--;
            }
        }

        // Display Mini-Boss health
        gotoxy(WIDTH + 5, 2);
        setColor(10);
        printf("MINI-BOSS:");

        int maxPerLine = 10;
        int lines = 2;
        if(life_Boss >= 10) {
            setColor(10);
        } else if(life_Boss >= 5) {
            setColor(14);
        } else {
            setColor(12);
        }
        for (int row = 0; row < lines; row++) {
            gotoxy(WIDTH + 5, 3 + row);
            for (int col = 0; col < maxPerLine; col++) {
                int hpIndex = row * maxPerLine + col;
                if (hpIndex < life_Boss)
                    printf("#");
                else
                    printf(" ");
            }
        }

        // Draw HUD
        int numBullets = MAX_BULLETS;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                numBullets--;
            }
        }
        drawHud(score, life, maxLife, numBullets);

        // if boss has been killed
        if (life_Boss <= 0) {
            GPlayerScore = score;
            return life;
        }

        if (life <= 0) {
            gotoxy(WIDTH/2 - 5, HEIGHT/2);
            setColor(12);
            printf("GAME OVER!");
            Sleep(1500);
            setColor(7);
            _getch();
            return 0;
        }

        Sleep(75);
    }
}