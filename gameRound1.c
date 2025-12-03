#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameRound1.h"

#define WIDTH 20         // The horizontal boundary of the game area
#define HEIGHT 15        // The vertical boundary of the game area
#define MAX_ENEMIES 6    // Maximum number of enemies active on screen at once
#define MAX_BULLETS 3    // Maximum number of bullets that can be fired simultaneously
#define MAX_HITTABLES 3  // Maximum number of hittable objects
#define BOSS_W 9
#define BOSS_H 4
#define MAX_BULL_BOSS 3
#define BOSS_SPEED 1
#define BOSS_LIFE_LAYER 3
#define BOSS_LIFE 30
#define MAX_PLAYER_LIFE 5

int playRound1() {
    system("cls");
    drawBorder();

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity enemies[MAX_ENEMIES];
    Entity bullets[MAX_BULLETS];
    Entity hitts[MAX_HITTABLES];
    int score = 0;
    int life = MAX_PLAYER_LIFE;
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

            if (key == 27) return 0;
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
        drawHud(score, life, numBullets);

        // Check if player reached 10 points
        if (score >= 10) {
            system("cls");
            gotoxy(WIDTH / 2 - 7, HEIGHT / 2 - 1);
            setColor(10);
            printf("CONGRATULATIONS!");
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

// ===================== GAMEPLAY w/ BOSS FUNCTION =====================
int playBOSS(){
    system("cls");
    drawBorder();
    srand(time(NULL));

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 };
    Entity bullets[MAX_BULLETS];
    Entity bullets1[MAX_BULL_BOSS];
    Entity bullets2[MAX_BULL_BOSS];
    Entity bulletsAdd1[MAX_BULL_BOSS];
    Entity bulletsAdd2[MAX_BULL_BOSS];

    int life_Boss = BOSS_LIFE;
    int life = 5;
    int score = 0;
    char key;
    
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
        clearBoss((int)Boss.boss.x, (int)Boss.boss.y);

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

        // Move boss
        if (moveMode == 1) move1(&Boss.boss.x, &Boss.boss.y, &Boss.boss.direction);
        else move2(&Boss.boss.x, &Boss.boss.y, &dx, &dy);

        moveCounter--;

        // Spawn bullets from both '!'
        if (bulletCooldown <= 0) {
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets1[i].active) {
                    bullets1[i].active = 1;
                    bullets1[i].x = (int)Boss.boss.x + 2;
                    bullets1[i].y = (int)Boss.boss.y + 3;
                    break;
                }
            }
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets2[i].active) {
                    bullets2[i].active = 1;
                    bullets2[i].x = (int)Boss.boss.x + 6;
                    bullets2[i].y = (int)Boss.boss.y + 3;
                    break;
                }
            }
            if(life_Boss >= 0 && life_Boss <= 10){
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd1[i].active) {
                        bulletsAdd1[i].active = 1;
                        bulletsAdd1[i].x = (int)Boss.boss.x;
                        bulletsAdd1[i].y = (int)Boss.boss.y + 1;
                        break;
                    }
                }
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd2[i].active) {
                        bulletsAdd2[i].active = 1;
                        bulletsAdd2[i].x = (int)Boss.boss.x + 8;
                        bulletsAdd2[i].y = (int)Boss.boss.y + 1;
                        break;
                    }
                }
            }
            if(burst>=5000 && burst <= 9000){
                if(change<=0){
                    bulletCooldown = 0;
                    change = 10 + rand() % 21;
                }
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
        drawBoss((int)Boss.boss.x, (int)Boss.boss.y, Boss.sizes);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) drawBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) drawBossBullet(bullets2[i].x, bullets2[i].y);
            if (bulletsAdd1[i].active) drawBossBullet(bulletsAdd1[i].x, bulletsAdd1[i].y);
            if (bulletsAdd2[i].active) drawBossBullet(bulletsAdd2[i].x, bulletsAdd2[i].y);
        }

        // Check collision: PLAYER BULLETS vs BOSS
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) continue;

            if (bullets[i].x >= (int)Boss.boss.x &&
                bullets[i].x <= (int)Boss.boss.x + 8 &&
                bullets[i].y >= (int)Boss.boss.y &&
                bullets[i].y <= (int)Boss.boss.y + 3) {

                bullets[i].active = 0;
                life_Boss--;
                explosionBossEffect(bullets[i].x, bullets[i].y);
            }

            if (life_Boss <= 0) {
                clearBoss((int)Boss.boss.x, (int)Boss.boss.y);
                gotoxy(WIDTH/2-4, HEIGHT/2);
                setColor(10);
                printf("YOU WIN!");
                Sleep(1500);
                setColor(7);
                _getch();
                return 1;
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
        drawHud(score, life, numBullets);

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