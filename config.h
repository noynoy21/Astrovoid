#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/*==============================*
 *       GAME AREA SIZE         *
 *==============================*/
#define WIDTH 20              // Horizontal boundary of the main game area
#define HEIGHT 15             // Vertical boundary of the main game area
#define PVP_WIDTH 25          // Width of the PvP arena
#define PVP_HEIGHT 7          // Height of the PvP arena


/*==============================*
 *       PLAYER PROPERTIES      *
 *==============================*/
#define MAX_PLAYER_LIFE 6     // Maximum health of the player in single-player
#define PVP_MAX_LIVES 3       // Lives per player in PvP mode
#define PVP_MAX_BULLETS_PER_PLAYER 6   // Total bullets available to each PvP player


/*==============================*
 *      ENEMY / OBJECT LIMITS   *
 *==============================*/
#define MAX_ENEMIES 6         // Max enemies on screen during the first and second (before the miniboss) rounds
#define MAX_HITTABLES 3       // Max number of hittable objects 
#define MAX_BULLETS 3         // Max bullets the player can fire at once


/*==============================*
 *          BOSS STATS          *
 *==============================*/
#define BOSS_W 9              // Boss width
#define BOSS_H 4              // Boss height
#define BOSS_SPEED 1          // Boss movement speed
#define BOSS_LIFE_LAYER 3     // Number of boss layers to break
#define BOSS_LIFE 30          // Total boss HP (full-form)
#define MAX_BULL_BOSS 3       // Max bullets a boss can fire at once

#define MINI_BOSS_LIFE 15     // HP of mini-boss (half of full boss)
#define MINI_BOSS_MAX_ENEMIES 4  // Max enemy sprites during mini-boss rounds 

/*==============================*
 *       GLOBAL VARIABLE        *
 *==============================*/
extern int GPlayerScore;      // Global (for the whole folder) variable holding the score of the player throughout the rounds

#endif // CONFIG_H_INCLUDED