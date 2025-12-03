#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "gameBoss.h"
#include "config.h"

#define CURRENT_ROUND 3

// ===================== GAMEPLAY w/ BOSS FUNCTION =====================
int playBOSS(){
    system("cls");
    drawBorder();
    srand(time(NULL));

    Entity player = { WIDTH / 2, HEIGHT - 2, 1 }; // Player starts near bottom center
    Entity bullets[MAX_BULLETS];                  // Array of bullets
    Entity bullets1[MAX_BULL_BOSS];
    Entity bullets2[MAX_BULL_BOSS];
    Entity bulletsAdd1[MAX_BULL_BOSS];
    Entity bulletsAdd2[MAX_BULL_BOSS];

    int life_Boss = BOSS_LIFE;
    int life = MAX_PLAYER_LIFE;
    int score = 0;            // Tracks player's score
    char key;                 // Stores input key
    for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets1[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bullets2[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bulletsAdd1[i].active = 0;
    for (int i = 0; i < MAX_BULL_BOSS; i++) bulletsAdd2[i].active = 0;

    body Boss = {
        { WIDTH / 4, 1, BOSS_SPEED},  // Start slightly below top border
        {
            "xvvvvvx",
            " Iv!vI ",
            " ! o ! ",
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
            moveCounter = 10 + rand() % 11; // changes pattern every after 10-20 frames
        }

        // Erase previous characters
        eraseObj(player.x, player.y);
        clearBoss((int)Boss.boss.x, (int)Boss.boss.y);

        // Erase bullets
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) eraseObj(bullets[i].x, bullets[i].y);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) eraseObj(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) eraseObj(bullets2[i].x, bullets2[i].y);
            if (bulletsAdd1[i].active) eraseObj(bulletsAdd1[i].x, bulletsAdd1[i].y);
            if (bulletsAdd2[i].active) eraseObj(bulletsAdd2[i].x, bulletsAdd2[i].y);
        }

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

            if (key == 27) return 0;          // ESC (ASCII 27) exits game
        }

        // -------- Prevent player from leaving play area --------
        if (player.x < 1) player.x = 1;
        if (player.x > WIDTH - 2) player.x = WIDTH - 2;
        if (player.y < 1) player.y = 1;
        if (player.y > HEIGHT - 2) player.y = HEIGHT - 2;

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
        for (int i = 0; i < MAX_BULLETS; i++)
            if (bullets[i].active) drawBullet(bullets[i].x, bullets[i].y);

        // Move boss
        if (moveMode == 1) move1(&Boss.boss.x, &Boss.boss.y, &Boss.boss.direction);
        else move2(&Boss.boss.x, &Boss.boss.y, &dx, &dy);

        moveCounter--;

        // ---------- SPAWN BULLETS FROM BOTH '!' ----------
        if (bulletCooldown <= 0) {
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets1[i].active) {
                    bullets1[i].active = 1;
                    bullets1[i].x = (int)Boss.boss.x + 1; // left '!'
                    bullets1[i].y = (int)Boss.boss.y + 2; // bottom row
                    break;
                }
            }
            for (int i = 0; i < MAX_BULL_BOSS; i++) {
                if (!bullets2[i].active) {
                    bullets2[i].active = 1;
                    bullets2[i].x = (int)Boss.boss.x + 5; // right '!'
                    bullets2[i].y = (int)Boss.boss.y + 2; // bottom row
                    break;
                }
            }
            if(life_Boss >= 0 && life_Boss <= 10){
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd1[i].active) {
                        bulletsAdd1[i].active = 1;
                        bulletsAdd1[i].x = (int)Boss.boss.x; // left '!'
                        bulletsAdd1[i].y = (int)Boss.boss.y + 2; // bottom row
                        break;
                    }
                }
                for (int i = 0; i < MAX_BULL_BOSS; i++) {
                    if (!bulletsAdd2[i].active) {
                        bulletsAdd2[i].active = 1;
                        bulletsAdd2[i].x = (int)Boss.boss.x + 6; // right '!'
                        bulletsAdd2[i].y = (int)Boss.boss.y + 2; // bottom row
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
        drawBoss((int)Boss.boss.x, (int)Boss.boss.y, Boss.sizes);
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active) drawBossBullet(bullets1[i].x, bullets1[i].y);
            if (bullets2[i].active) drawBossBullet(bullets2[i].x, bullets2[i].y);
            if (bulletsAdd1[i].active) drawBossBullet(bulletsAdd1[i].x, bulletsAdd1[i].y);
            if (bulletsAdd2[i].active) drawBossBullet(bulletsAdd2[i].x, bulletsAdd2[i].y);
        }

        // -------- Check collision --------
        // -------- PLAYER BULLETS vs BOSS --------
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (!bullets[i].active) continue;

            // Check if bullet hits boss area
            if (bullets[i].x >= (int)Boss.boss.x &&
                bullets[i].x <= (int)Boss.boss.x + 6 &&
                bullets[i].y >= (int)Boss.boss.y &&
                bullets[i].y <= (int)Boss.boss.y + 2) {

                bullets[i].active = 0;   // remove bullet
                life_Boss--;             // damage boss
                explosionBossEffect(bullets[i].x, bullets[i].y);
            }

            if (life_Boss <= 0) {
                // BOSS DEATH
                clearBoss((int)Boss.boss.x, (int)Boss.boss.y);
                gotoxy(WIDTH/2-4, HEIGHT/2);
                setColor(10);
                printf("YOU WIN!");
                Sleep(1500);
                setColor(7);
                _getch();
                return 1; // player wins round
            }
        }

        // -------- BOSS BULLETS vs PLAYER --------
        for (int i = 0; i < MAX_BULL_BOSS; i++) {
            if (bullets1[i].active &&
                bullets1[i].x == player.x &&
                bullets1[i].y == player.y) {

                bullets1[i].active = 0;
                life--;     // player takes damage
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
                life--;     // player takes damage
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

        // ---- Displays ----
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
            gotoxy(WIDTH + 5, 3 + row);   // move to next line
            for (int col = 0; col < maxPerLine; col++) {

                int hpIndex = row * maxPerLine + col;

                if (hpIndex < life_Boss)
                    printf("#");
                else
                    printf(" ");
            }
        }
        // display bullets and life (HUD)
        int numBullets = MAX_BULLETS;
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                numBullets--;
            }
        }
        drawHud(score, life, numBullets, CURRENT_ROUND);

        if (life <= 0) {
            gotoxy(WIDTH/2 - 5, HEIGHT/2);
            setColor(12);
            printf("GAME OVER!");
            Sleep(1500);
            setColor(7);
            _getch();
            return 0; //player loses round
        }

        burst++;
        Sleep(75);
    }
}