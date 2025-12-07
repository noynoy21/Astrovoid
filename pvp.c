#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "render.h"
#include "entity.h"
#include "pvp.h"
#include "config.h"

// ===================== PVP GAMEPLAY (LANDSCAPE) =====================
void playPVP() {
    system("cls");
    drawBorderPVP();

    // Player 1 on LEFT side, Player 2 on RIGHT side
    Entity player1 = { 2, PVP_HEIGHT / 2, 1 };           // Left side, middle height
    Entity player2 = { PVP_WIDTH - 3, PVP_HEIGHT / 2, 1 };   // Right side, middle height
    PVPBullet bullets[PVP_MAX_BULLETS_PER_PLAYER * 2];  // Total bullets for both players
    
    int lives1 = PVP_MAX_LIVES;
    int lives2 = PVP_MAX_LIVES;
    int score1 = 0;
    int score2 = 0;
    
    srand(time(0));

    // Initialize bullets
    for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
        bullets[i].active = 0;
        bullets[i].owner = 0;
    }

    // Main PVP loop
    while (1) {
        // Erase old positions
        erasePlayer(player1.x, player1.y);
        erasePlayer(player2.x, player2.y);
        for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++)
            if (bullets[i].active) eraseBullet(bullets[i].x, bullets[i].y);

        // Handle input
        if (_kbhit()) {
            int key = _getch();
            
            // Player 1 controls (W/S for up/down + Space to shoot RIGHT)
            if (key == 'w' || key == 'W') player1.y--;
            if (key == 's' || key == 'S') player1.y++;
            
            if (key == 32) {  // Spacebar - Player 1 shoots RIGHT
                // Count Player 1's active bullets
                int p1ActiveBullets = 0;
                for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
                    if (bullets[i].active && bullets[i].owner == 1) {
                        p1ActiveBullets++;
                    }
                }
                
                // Only fire if Player 1 has less than PVP_MAX_BULLETS_PER_PLAYER active bullets
                if (p1ActiveBullets < PVP_MAX_BULLETS_PER_PLAYER) {
                    for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
                        if (!bullets[i].active) {
                            bullets[i].x = player1.x + 1;  // Spawn to the right
                            bullets[i].y = player1.y;
                            bullets[i].active = 1;
                            bullets[i].owner = 1;
                            break;
                        }
                    }
                }
            }
            
            // Player 2 controls (Arrow keys for up/down + Enter to shoot LEFT)
            if (key == 224) {  // Arrow key prefix
                key = _getch();
                if (key == 72) player2.y--;      // Up arrow
                if (key == 80) player2.y++;      // Down arrow
            }
            
            // Enter for Player 2 shooting LEFT
            if (key == 13) {  // Enter key
                // Count Player 2's active bullets
                int p2ActiveBullets = 0;
                for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
                    if (bullets[i].active && bullets[i].owner == 2) {
                        p2ActiveBullets++;
                    }
                }
                
                // Only fire if Player 2 has less than PVP_MAX_BULLETS_PER_PLAYER active bullets
                if (p2ActiveBullets < PVP_MAX_BULLETS_PER_PLAYER) {
                    for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
                        if (!bullets[i].active) {
                            bullets[i].x = player2.x - 1;  // Spawn to the left
                            bullets[i].y = player2.y;
                            bullets[i].active = 1;
                            bullets[i].owner = 2;
                            break;
                        }
                    }
                }
            }

            if (key == 27) return;  // ESC
        }

        // Boundary checking - players can only move UP/DOWN
        if (player1.y < 1) player1.y = 1;
        if (player1.y > PVP_HEIGHT - 1) player1.y = PVP_HEIGHT - 1;
        
        if (player2.y < 1) player2.y = 1;
        if (player2.y > PVP_HEIGHT - 1) player2.y = PVP_HEIGHT - 1;

        // Move bullets HORIZONTALLY
        for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
            if (bullets[i].active) {
                if (bullets[i].owner == 1) {
                    bullets[i].x++;  // Player1 bullets go RIGHT
                    if (bullets[i].x >= PVP_WIDTH - 1)
                        bullets[i].active = 0;
                } else if (bullets[i].owner == 2) {
                    bullets[i].x--;  // Player2 bullets go LEFT
                    if (bullets[i].x <= 1)
                        bullets[i].active = 0;
                }
            }
        }

        // Draw entities
        SetConsoleOutputCP(CP_UTF8);
        setColor(9);
        gotoxy(player1.x, player1.y);
        printf("\u25BA");  // Blue right-pointing triangle for P1
        
        setColor(10);
        gotoxy(player2.x, player2.y);
        printf("\u25C4");  // Green left-pointing triangle for P2
        
        setColor(7);
        for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
            if (bullets[i].active) {
                gotoxy(bullets[i].x, bullets[i].y);
                if (bullets[i].owner == 1) {
                    setColor(9);
                    printf("-");  // P1 bullets go right
                } else {
                    setColor(10);
                    printf("-");  // P2 bullets go left
                }
                setColor(7);
            }
        }

        // Check bullets vs players collision
        for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
            if (bullets[i].active) {
                if (bullets[i].owner == 2 && collision(bullets[i].x, bullets[i].y, player1.x, player1.y)) {
                    explosionEffect(player1.x, player1.y);
                    bullets[i].active = 0;
                    lives1--;
                    score2 += 10;
                    Sleep(500);
                }
                if (bullets[i].owner == 1 && collision(bullets[i].x, bullets[i].y, player2.x, player2.y)) {
                    explosionEffect(player2.x, player2.y);
                    bullets[i].active = 0;
                    lives2--;
                    score1 += 10;
                    Sleep(500);
                }
            }
        }

        // -------- Calculate available bullets for each player (SEPARATE POOLS) --------
        int p1ActiveBullets = 0;
        int p2ActiveBullets = 0;
        
        for (int i = 0; i < PVP_MAX_BULLETS_PER_PLAYER * 2; i++) {
            if (bullets[i].active) {
                if (bullets[i].owner == 1) p1ActiveBullets++;
                else if (bullets[i].owner == 2) p2ActiveBullets++;
            }
        }
        
        int p1AvailableBullets = PVP_MAX_BULLETS_PER_PLAYER - p1ActiveBullets;
        int p2AvailableBullets = PVP_MAX_BULLETS_PER_PLAYER - p2ActiveBullets;
        
        // Ensure bullet counts are valid
        if (p1AvailableBullets < 0) p1AvailableBullets = 0;
        if (p2AvailableBullets < 0) p2AvailableBullets = 0;
        if (p1AvailableBullets > PVP_MAX_BULLETS_PER_PLAYER) p1AvailableBullets = PVP_MAX_BULLETS_PER_PLAYER;
        if (p2AvailableBullets > PVP_MAX_BULLETS_PER_PLAYER) p2AvailableBullets = PVP_MAX_BULLETS_PER_PLAYER;

        // -------- Display stats with separate bullet counters --------
        gotoxy(PVP_WIDTH + 5, 2);
        setColor(9);
        printf("P1 Lives: %d", lives1);
        gotoxy(PVP_WIDTH + 5, 3);
        printf("P1 Score: %d", score1);
        gotoxy(PVP_WIDTH + 5, 4);
        printf("P1 Bull: ");
        setColor(2);
        for (int i = 0; i < p1AvailableBullets; i++) printf("-");
        for (int i = p1AvailableBullets; i < PVP_MAX_BULLETS_PER_PLAYER; i++) printf(" ");
        
        gotoxy(PVP_WIDTH + 5, 6);
        setColor(10);
        printf("P2 Lives: %d", lives2);
        gotoxy(PVP_WIDTH + 5, 7);
        printf("P2 Score: %d", score2);
        gotoxy(PVP_WIDTH + 5, 8);
        printf("P2 Bull: ");
        setColor(2);
        for (int i = 0; i < p2AvailableBullets; i++) printf("-");
        for (int i = p2AvailableBullets; i < PVP_MAX_BULLETS_PER_PLAYER; i++) printf(" ");
        
        setColor(7);

        // Check win conditions
        if (lives1 <= 0 || lives2 <= 0) {
            gotoxy(PVP_WIDTH / 2 - 8, PVP_HEIGHT / 2);
            if (lives1 <= 0 && lives2 <= 0) {
                setColor(14);
                printf("DRAW!");
            } else if (lives1 <= 0) {
                setColor(10);
                printf("PLAYER 2 WINS!");
            } else {
                setColor(9);
                printf("PLAYER 1 WINS!");
            }
            setColor(7);
            gotoxy(0, PVP_HEIGHT + 2);
            printf("Press any key to continue...");
            _getch();
            return;
        }

        Sleep(75);
    }
}