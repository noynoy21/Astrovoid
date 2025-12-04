#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameRound2.h"

#define WIDTH 20
#define HEIGHT 15
#define MAX_ENEMIES 8        // More enemies in round 2
#define MAX_BULLETS 3
#define MAX_HITTABLES 4      // More hittables in round 2
#define MINIBOSS_W 7
#define MINIBOSS_H 3
#define MAX_BULL_BOSS 2
#define MINI_BOSS_LIFE 15    // Half of full boss
#define MAX_PLAYER_LIFE 5

// ===================== ROUND 2 GAMEPLAY =====================
int playRound2() {
    system("cls");
    drawBorder();

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity hitts[MAX_HITTABLES];
    int score = 0;
    int life = 5;
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
    drawBorder();

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
            if (key == 'w' || key == 'W') player.y--;
            if (key == 's' || key == 'S') player.y++;

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

            if (key == 27) return 0;
        }

        // Boundary checking
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;
        if (player.y < 1) player.y = 1;
        if (player.y > HEIGHT - 2) player.y = HEIGHT - 2;

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
        drawHud(score, life, numBullets);

        // Check if mini-boss should spawn
        if (score >= 5) {
            // Warning message
            system("cls");
            gotoxy(WIDTH / 2 - 4, HEIGHT / 2);
            setColor(12);
            printf("Uh oh...\n");
            setColor(7);
            printf("press 1 to continue...");
            while(1) {
                if (_kbhit()) {
                    char choice = _getch();
                    if (choice == '1') {
                        break;
                    } else if (choice == 27) {
                        return 0;  // ESC to exit
                    }
                    }
                }
            // Sleep(2000);

            return playMiniBoss();
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
int playMiniBoss() {
    system("cls");
    drawBorder();
    srand(time(NULL));

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity bullets[MAX_BULLETS];
    Entity bullets1[MAX_BULL_BOSS];
    Entity bullets2[MAX_BULL_BOSS];

    int life_Boss = MINI_BOSS_LIFE;
    int life = 5;
    int score = 0;
    char key;

    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;
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
    drawBorder();

    while (1) {
        // Erase previous characters
        erasePlayer(player.x, player.y);
        clearBossEntity((int)MiniBoss.boss.x, (int)MiniBoss.boss.y, MINIBOSS_H, MINIBOSS_W);

        // Erase bullets
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) eraseBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) eraseBossBullet(bullets2[i].x, bullets2[i].y);
        }

        // Handle Player Input
        if (_kbhit()) {
            key = _getch();
            if (key == 'a' || key == 'A') player.x--;
            if (key == 'd' || key == 'D') player.x++;
            if (key == 'w' || key == 'W') player.y--;
            if (key == 's' || key == 'S') player.y++;

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

            if (key == 27) return 0;
        }

        // Boundary checking
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;
        if (player.y < 1) player.y = 1;
        if (player.y > HEIGHT - 2) player.y = HEIGHT - 2;

        // Move bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;
                if (bullets[i].y < 1)
                    bullets[i].active = 0;
            }
        }

        // Draw player and bullets
        drawPlayer(player.x, player.y);
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

            if (life_Boss <= 0) {
                clearBossEntity((int)MiniBoss.boss.x, (int)MiniBoss.boss.y, MINIBOSS_H, MINIBOSS_W);
                gotoxy(WIDTH/2-4, HEIGHT/2);
                setColor(10);
                printf("YOU WIN!");
                Sleep(1500);
                setColor(7);
                _getch();
                bossRound();
                while(1) {
                if (_kbhit()) {
                    char choice = _getch();
                    if (choice == '1') {
                        bossRound();
                        break;
                    } else if (choice == 27) {
                        return 0;  // ESC to exit
                    }
                    }
                }
                
                /*
                while(1) {
                if (_kbhit()) {
                    char choice = _getch();
                    if (choice == '1') {
                        bossRound();
                        break;
                    } else if (choice == 27) {
                        return 0;  // ESC to exit
                    }
                    }
                }
                */
            return 1;
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

        int numBullets = MAX_BULLETS;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                numBullets--;
            }
        }
        drawHud(score, life, numBullets);

        /* changes ni denz
        if (score >= 10) {
            system("cls");
            gotoxy(WIDTH / 2 - 7, HEIGHT / 2 - 1);
            setColor(10);
            printf("Here it comes...");

            gotoxy(WIDTH / 2 - 10, HEIGHT / 2);
            setColor(14);
            printf("Press 1 to continue to");
            gotoxy(WIDTH / 2 - 4, HEIGHT / 2 + 1);
            printf("Round 2");
            setColor(7);


            while(1) {
                if (_kbhit()) {
                    char choice = _getch();
                    if (choice == '1') {
                        return life;  // Return life to continue to round 2
                    } else if (choice == 27) {
                        return 0;  // ESC to exit
                    }
                }
            }
        }
        */
        //changes ni denz

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