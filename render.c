#include <windows.h>
#include <stdio.h>
#include "render.h"
#define WIDTH 20         // The horizontal boundary of the game area
#define HEIGHT 20        // The vertical boundary of the game area

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
    setColor(9);                // Blue
    gotoxy(x, y);               // Move to player position
    printf("^");                // Print symbol
    setColor(7);
}

// Draw enemy as red '*'
void drawEnemy(int x, int y) {
    setColor(12);
    gotoxy(x, y);
    printf("*");
    setColor(7);
}

// Draw bullet symbol '|'
void drawBullet(int x, int y) {
    setColor(14);              // Yellow
    gotoxy(x, y);
    printf("|");
    setColor(7);
}

// =============== Erasing Functions ===============
// Erase player by printing space at old location
void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf(" ");
}

// Erase enemy
void eraseEnemy(int x, int y) {
    gotoxy(x, y);
    printf(" ");
}

// Erase bullet
void eraseBullet(int x, int y) {
    gotoxy(x, y);
    printf(" ");
}

// =============== Special Effects Functions ===============
// Simple explosion animation effect (flashing 'X')
void explosionEffect(int x, int y) {
    for (int i = 0; i < 3; i++) {          // Repeat 3 flashes
        setColor(12);
        gotoxy(x, y); printf("X");         // Red 'X'
        Sleep(20);
        setColor(14);
        gotoxy(x, y); printf("X");         // Yellow flash
        Sleep(20);
        gotoxy(x, y); printf(" ");         // Clear
    }
    setColor(7);                           // Reset color
}
