#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// ===============  GAME AREA SETTINGS (Single Player)  =================
#define WIDTH 20          // Horizontal size of the game area (columns)
#define HEIGHT 15         // Vertical size of the game area (rows)

// ===============  GAME AREA SETTINGS (Single PVP)  =================


// ====================  PLAYER  ========================
#define MAX_PLAYER_LIFE 5 // Maximum health the player can have

// ====================  ENEMIES  =======================
#define MAX_ENEMIES 6     // How many enemies can exist on screen at once
#define MAX_HITTABLES 3   // Number of non-enemy objects that can be damaged (e.g., obstacles)

// ====================  BULLETS  =======================
#define MAX_BULLETS 3     // Maximum number of player bullets that can exist at once

// =====================  BOSS  =========================
#define BOSS_W 7          // Boss sprite width (in characters)
#define BOSS_H 3          // Boss sprite height (in characters)
#define MAX_BULL_BOSS 3   // Maximum number of boss bullets allowed on screen
#define BOSS_SPEED 1      // Boss movement speed (cells per update)
#define BOSS_LIFE 30      // Boss health value


#endif // CONFIG_H_INCLUDED
