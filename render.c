#include <windows.h>
#include <stdio.h>
#include "render.h"
#define WIDTH 20         // The horizontal boundary of the game area
#define HEIGHT 15        // The vertical boundary of the game area
#define MAX_BULLETS 3    // Maximum number of bullets that can be fired simultaneously


// =============== Console Control Functions ===============
// Moves console cursor to position (x, y)
void gotoxy(int x, int y) {
    COORD coord = { x, y };                                // Define coordinate pair
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move cursor
}

// Hides cursor visibility for aesthetic presentation
void hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;             // Small size
    cursor.bVisible = FALSE;       // Make cursor invisible
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

// Changes console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


// =============== Drawing Functions ===============
// Draws rectangular boundary for the play area using '#'
void drawBorder() {
    setColor(8);                                           // Gray color
    for (int i = 0; i <= WIDTH; i++) {
        gotoxy(i, 0); printf("#");                         // Top border
        gotoxy(i, HEIGHT); printf("#");                    // Bottom border
    }
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); printf("#");                         // Left border
        gotoxy(WIDTH, i); printf("#");                     // Right border
    }
    setColor(7);                                           // Reset to white
}

// Draw player symbol '^'
void drawPlayer(int x, int y) {
    SetConsoleOutputCP(CP_UTF8);
    setColor(9);                // Blue
    gotoxy(x, y);               // Move to player position
    printf("\u25B2\n");                // Print symbol
    setColor(7);
}

// Draw enemy as red '*'
void drawEnemy(int x, int y) {
    setColor(12);
    gotoxy(x, y);
    printf("*");
    setColor(7);
}

// Draw enemy as red '*'
void drawHittable(int x, int y) {
    setColor(9);
    gotoxy(x, y);
    printf("O");
    setColor(7);
}

// Draw bullet symbol '|'
void drawBullet(int x, int y) {
    setColor(14);              // Yellow
    gotoxy(x, y);
    printf("|");
    setColor(7);
}

//Draw boss
void drawBoss(int x, int y, char size[BOSS_H][BOSS_W]) {
    for (int i = 0; i < BOSS_H; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < BOSS_W; j++) {

            if (!isspace(size[i][j]) && size[i][j] == 'o') {
                setColor(14);   // Yellow
            } else {
                setColor(4);    // Red
            }

            printf("%c", size[i][j]);
        }
    }
    setColor(7); // Reset color
}

// Draw boss bullet
void drawBossBullet(int x, int y) {   // Use actual coordinates
    setColor(12);
    gotoxy(x, y);
    printf("!");
    setColor(7);
}

// Draw Headsup display (HUD)
void drawHud(int score, int life, int numBullets, int level) {
    // -------- Display the round and score beside play area (if not boss round) --------
    if (level != 3) {
        gotoxy(WIDTH + 5, 1);
        setColor(10);
        printf("ROUND %d  ", level);
        setColor(7);

        // -------- Display the score beside play area --------
        gotoxy(WIDTH + 5, 2);
        setColor(10);
        printf("Score: %d  ", score);
        setColor(7);
    }

    // -------- Display the bullets below play area --------
    gotoxy(0, HEIGHT + 2);
    setColor(10);
    printf("Bull:");
    setColor(2);
    for (int i = 0; i < numBullets; i++) {
        printf("|");
    }
    for (int i = numBullets; i < MAX_BULLETS; i++) printf(" ");
    setColor(7);

    // -------- Display the player's lives below play area --------
    printf(" ");
    setColor(10);
    printf("Life: ");
    setColor(12);
    for(int i = 0; i< life; i++){
        printf("o");
    }
    for (int i = life; i < 5; i++) printf(" "); // erase leftover markers when life decreases
    setColor(7);
}

// =============== Erasing Functions ===============
// Erase player by printing space at old location

// Erase one char length entities
void eraseObj(int x, int y) {
    gotoxy(x, y);
    printf(" ");
}

// Erase the boss
void clearBoss(int x, int y) {
    for (int i = 0; i < BOSS_H; i++) {
        int drawY = y + i;
        if (drawY <= 0 || drawY >= HEIGHT) continue;  // Skip border rows

        gotoxy(x, drawY);
        for (int j = 0; j < BOSS_W; j++) {
            int drawX = x + j;
            if (drawX <= 0 || drawX >= WIDTH) continue; // Skip border columns
            printf(" ");
        }
    }
}

// =============== Special Effects Functions ===============
// Simple explosion animation effect (flashing 'X')
void explosionEffect(int x, int y) {
    for (int i = 0; i < 3; i++) {          // Repeat 3 flashes
        setColor(12);
        gotoxy(x, y); printf("X");         // Red 'X'
        Sleep(8);
        setColor(14);
        gotoxy(x, y); printf("X");         // Yellow flash
        Sleep(8);
        gotoxy(x, y); printf(" ");         // Clear
    }
    setColor(7);                           // Reset color
}

void explosionBossEffect(int x, int y) {
    setColor(12);
    gotoxy(x, y); printf("X");         // Red 'X'
    Sleep(2);
    setColor(14);
    gotoxy(x, y); printf("X");         // Yellow flash
    Sleep(2);
    gotoxy(x, y); printf(" ");         // Clear
    setColor(7);                       // Reset color
}

// Movements for special enemies
// First pattern
void move1(float *x, float *y, float *dx) {
    *x += *dx;

    if (*x < 1) {
        *x = 1;
        *dx *= -1;
    }
    if (*x > WIDTH - BOSS_W - 1) {
        *x = WIDTH - BOSS_W - 1;
        *dx *= -1;
    }
}

// Second pattern
void move2(float *x, float *y, float *dx, float *dy) {
    *x += *dx;
    *y += *dy;

    // Horizontal bounce
    if (*x < 1) {
        *x = 1;
        *dx *= -1;
    }
    if (*x > WIDTH - BOSS_W - 1) {
        *x = WIDTH - BOSS_W - 1;
        *dx *= -1;
    }

    // Vertical bounce
    if (*y < 1) {
        *y = 1;
        *dy *= -1;
    }
    if (*y > (HEIGHT/2)-3) {
        *y = (HEIGHT/2)-3;
        *dy *= -1;
    }
}
