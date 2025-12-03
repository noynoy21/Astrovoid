#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#define BOSS_W 7
#define BOSS_H 3

// =============== Console Control Functions ===============
void gotoxy(int, int);              // Moves the console cursor to (x, y)
void hideCursor();                  // Hides the blinking cursor
void setColor(int);                 // Sets text color


// =============== Drawing Functions ===============
void drawBorder();                  // Draws the play area boundary
void drawPlayer(int, int);          // Draws the player symbol '^'
void drawEnemy(int, int);           // Draws an enemy '*'
void drawHittable(int, int);           // Draws a hittable 'O'
void drawBullet(int, int);          // Draws a bullet '|'
void drawBoss(int, int, char [BOSS_H][BOSS_W]); // Draws the Boss
void drawBossBullet(int, int);      // Draws the bullet of boss
void drawHud(int, int, int, int);


// =============== Erasing Functions ===============
void eraseObj(int, int);          // Erases the enemy symbol
void clearBoss(int, int);           // Erases the boss


// =============== Special Effects Functions ===============
void explosionEffect(int, int);     // Displays explosion animation
void explosionBossEffect(int, int);
void move1(float*, float*, float*); // First pattern (sideways)
void move2(float*, float*, float*, float*); // Second pattern (diagonal)

#endif // RENDER_H_INCLUDED
