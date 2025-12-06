#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "config.h"

// Basic entity with integer coordinates and activity flag.
// Commonly used for players, bullets, enemies, etc.
typedef struct {
    int x, y;        // X and Y coordinates on the screen (top-left origin)
    int active;      // Activity state: 1 = active/visible, 0 = inactive/hidden
} Entity;

// Entity with floating-point position and a movement direction.
// Used when smoother movement or directional control is needed (e.g., bosses).
typedef struct {
    float x, y;        // X and Y coordinates (float for smooth movement)
    float direction;   // Direction of movement: +1 = right, -1 = left
} Entity2;

// Boss body container holding its positional data and sprite shape.
// 'sizes' stores the ASCII art or shape of the boss using BOSS_H × BOSS_W.
typedef struct {
    Entity2 boss;                   // Boss position and movement data
    char sizes[BOSS_H][BOSS_W];     // 2D array representing the boss's sprite
} body;

// Collision detection between two rectangular areas (overlap check).
// Parameters represent x1, y1, x2, y2 coordinates.
int collision(int, int, int, int);  

// Checks whether two entities are adjacent (touching but not overlapping).
// Useful for hit detection or edge-based interactions.
int collisionAdj(int, int, int, int);

#endif // ENTITY_H_INCLUDED
