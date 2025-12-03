#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#define BOSS_W 9
#define BOSS_H 4
#define MINIBOSS_H 7
#define MINIBOSS_W 3

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
void drawMiniBoss(int, int, char [MINIBOSS_H][MINIBOSS_W]); // Draw the MiniBoss
void drawBossBullet(int, int);      // Draws the bullet of boss
void drawHud(int, int, int);


// =============== Erasing Functions ===============
void erasePlayer(int, int);         // Erases the player symbol
void eraseEnemy(int, int);          // Erases the enemy symbol
void eraseObj(int, int);          // Erases the enemy symbol
void eraseBullet(int, int);         // Erases the bullet
void clearBoss(int, int);           // Erases the boss
void clearMiniBoss(int, int);       // Erases the miniboss
void eraseBossBullet (int, int);    // Erases the bullet of boss


// =============== Special Effects Functions ===============
void explosionEffect(int, int);     // Displays explosion animation
void explosionBossEffect(int, int);
void move1(float*, float*, float*); // First pattern (sideways)
void move2(float*, float*, float*, float*); // Second pattern (diagonal)

#endif // RENDER_H_INCLUDED
