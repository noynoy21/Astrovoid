#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

// =============== Console Control Functions ===============
void gotoxy(int, int);              // Moves the console cursor to (x, y)
void hideCursor();                  // Hides the blinking cursor
void setColor(int);                 // Sets text color


// =============== Drawing Functions ===============
void drawBorder();                  // Draws the play area boundary
void drawPlayer(int, int);          // Draws the player symbol '^'
void drawEnemy(int, int);           // Draws an enemy '*'
void drawBullet(int, int);          // Draws a bullet '|'


// =============== Erasing Functions ===============
void erasePlayer(int, int);         // Erases the player symbol
void eraseEnemy(int, int);          // Erases the enemy symbol
void eraseBullet(int, int);         // Erases the bullet

// =============== Special Effects Functions ===============
void explosionEffect(int, int);     // Displays explosion animation

#endif // RENDER_H_INCLUDED
