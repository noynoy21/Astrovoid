#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameRound1.h"
#include "config.h"

#define ADDITIONAL_LIFE 2

// ===================== GAMEPLAY w/ BOSS FUNCTION =====================
int playBOSS(int life){
    system("cls");
    drawBorder(WIDTH, HEIGHT);
    srand(time(NULL));

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MINI_BOSS_MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity bullets1[MAX_BULL_BOSS];
    Entity bullets2[MAX_BULL_BOSS];
    Entity bulletsAdd1[MAX_BULL_BOSS];
    Entity bulletsAdd2[MAX_BULL_BOSS];

    int life_Boss = BOSS_LIFE;
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
    // Initialize Boss bullets
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets1[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets2[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bulletsAdd1[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bulletsAdd2[i].active = 0;

    body Boss = {
        { WIDTH / 4, 1, BOSS_SPEED},
        {
            "    o    ",
            "<<|000|>>",
            " 0<v!v>0 ",
            "  ! v !  ",
        }
    };

    float dx = 0.5, dy = 0.3;
    int moveMode = 1;
    int moveCounter = 0;
    int change = 0;
    long long burst = 0;

    int bulletCooldown = 0;

    while (1) {
        if (moveCounter <= 0) {
            int cue = (rand() % 6) + 1;
            moveMode = (cue < 3) ? 1 : 2;
            moveCounter = 10 + rand() % 11;
        }

        // Erase previous characters
        erasePlayer(player.x, player.y);
        clearBossEntity((int)Boss.boss.x, (int)Boss.boss.y, BOSS_H, BOSS_W);
        // Erase previous enemy sprites
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++)
            eraseObj(enemies[i].x, enemies[i].y);
        // Erase bullets
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) eraseBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) eraseBossBullet(bullets2[i].x, bullets2[i].y);
            if (bulletsAdd1[i].active) eraseBossBullet(bulletsAdd1[i].x, bulletsAdd1[i].y);
            if (bulletsAdd2[i].active) eraseBossBullet(bulletsAdd2[i].x, bulletsAdd2[i].y);
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

        // Move enemies (slightly faster in round 2)
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++) {
            enemies[i].y++;
            if (enemies[i].y > HEIGHT - 1) {
                enemies[i].y = 1;
                enemies[i].x = rand() % (WIDTH - 2) + 1;
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

        // Draw updated positions
        drawPlayer(player.x, player.y);
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) drawBullet(bullets[i].x, bullets[i].y);
        for (int i = 0; i < MINI_BOSS_MAX_ENEMIES; i++)
            drawEnemy(enemies[i].x, enemies[i].y);

        // Move boss
        if (moveMode == 1) move1(&Boss.boss.x, &Boss.boss.y, &Boss.boss.direction);
        else move2(&Boss.boss.x, &Boss.boss.y, &dx, &dy);

        moveCounter--;

        // Spawn bullets from both '!'
        if (bulletCooldown <= 0) {
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets1[i].active) {
                    bullets1[i].active = 1;
                    bullets1[i].x = (int)Boss.boss.x + 2; // left '!'
                    bullets1[i].y = (int)Boss.boss.y + 3; // bottom row
                    break;
                }
            }
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets2[i].active) {
                    bullets2[i].active = 1;
                    bullets2[i].x = (int)Boss.boss.x + 6; // right '!'
                    bullets2[i].y = (int)Boss.boss.y + 3; // bottom row
                    break;
                }
            }
            if(life_Boss >= 0 && life_Boss <= 10){
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd1[i].active) {
                        bulletsAdd1[i].active = 1;
                        bulletsAdd1[i].x = (int)Boss.boss.x; // left '!'
                        bulletsAdd1[i].y = (int)Boss.boss.y+2; // bottom row
                        break;
                    }
                }
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd2[i].active) {
                        bulletsAdd2[i].active = 1;
                        bulletsAdd2[i].x = (int)Boss.boss.x + 8; // right '!'
                        bulletsAdd2[i].y = (int)Boss.boss.y+2; // bottom row
                        break;
                    }
                }
            }
            if(burst>=5000 && burst <= 9000){
                if(change<=0){
                    bulletCooldown = 0;
                    change = 10 + rand() % 21;
                } // frames between bullets
            }else if(burst<=4999){
                bulletCooldown -= 2;
            }else{
                bulletCooldown -= 5;
                burst = 0;
            }
        } else bulletCooldown--;

        // Move bullets downward
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) {
                bullets1[i].y++;
                if (bullets1[i].y > HEIGHT-1) bullets1[i].active = 0;
            }
            if (bullets2[i].active) {
                bullets2[i].y++;
                if (bullets2[i].y > HEIGHT-1) bullets2[i].active = 0;
            }
            if (bulletsAdd1[i].active) {
                bulletsAdd1[i].y++;
                if (bulletsAdd1[i].y > HEIGHT-1) bulletsAdd1[i].active = 0;
            }
            if (bulletsAdd2[i].active) {
                bulletsAdd2[i].y++;
                if (bulletsAdd2[i].y > HEIGHT-1) bulletsAdd2[i].active = 0;
            }
        }

        // Draw boss and bullets
        drawBossEntity((int)Boss.boss.x, (int)Boss.boss.y, Boss.sizes, BOSS_H, BOSS_W);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) drawBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) drawBossBullet(bullets2[i].x, bullets2[i].y);
            if (bulletsAdd1[i].active) drawBossBullet(bulletsAdd1[i].x, bulletsAdd1[i].y);
            if (bulletsAdd2[i].active) drawBossBullet(bulletsAdd2[i].x, bulletsAdd2[i].y);
        }

        // Check collision: PLAYER BULLETS vs BOSS
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) continue;

            // Check if bullet hits boss area
            if (bullets[i].x >= (int)Boss.boss.x &&
                bullets[i].x <= (int)Boss.boss.x + 8 &&
                bullets[i].y >= (int)Boss.boss.y &&
                bullets[i].y <= (int)Boss.boss.y + 3) {

                bullets[i].active = 0;   // remove bullet
                life_Boss--;             // damage boss
                explosionBossEffect(bullets[i].x, bullets[i].y);
            }
        }

        // Check collision: BOSS BULLETS vs PLAYER
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
            if (bulletsAdd1[i].active &&
                bulletsAdd1[i].x == player.x &&
                bulletsAdd1[i].y == player.y) {
                bulletsAdd1[i].active = 0;
                life--;
                explosionBossEffect(player.x, player.y);
            }

            if (bulletsAdd2[i].active &&
                bulletsAdd2[i].x == player.x &&
                bulletsAdd2[i].y == player.y) {
                bulletsAdd2[i].active = 0;
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

        // Display Boss health
        gotoxy(WIDTH + 5, 2);
        setColor(10);
        printf("BOSS:");

        int maxPerLine = 10;
        int lines = 3;
        if(life_Boss>=20 && life_Boss<=30){
            setColor(10);
        }else if(life_Boss>=10 && life_Boss<=19){
            setColor(9);
        }else{
            setColor(4);
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
        drawHud(score, life, maxLife, numBullets);

        if (life_Boss <= 0) {
            GPlayerScore = 0;
            return score;
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

        burst++;
        Sleep(75);
    }
}