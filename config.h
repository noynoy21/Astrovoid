#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define BOSS_W 9
#define BOSS_H 4
#define WIDTH 20         // The horizontal boundary of the game area
#define HEIGHT 15        // The vertical boundary of the game area
#define MAX_ENEMIES 6    // Maximum number of enemies active on screen at once
#define MAX_BULLETS 3    // Maximum number of bullets that can be fired simultaneously
#define MAX_HITTABLES 3  // Maximum number of hittable objects
#define MAX_BULL_BOSS 3
#define BOSS_SPEED 1
#define BOSS_LIFE_LAYER 3
#define BOSS_LIFE 30
#define MAX_PLAYER_LIFE 6
#define MINI_BOSS_LIFE 15    // Half of full boss
#define MINI_BOSS_MAX_ENEMIES 4
#define PVP_WIDTH 25    
#define PVP_HEIGHT 7
#define PVP_MAX_BULLETS_PER_PLAYER 6  // Each player gets 3 bullets
#define PVP_MAX_LIVES 3

extern int GPlayerScore;

#endif // CONFIG_H_INCLUDED