#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "config.h"

typedef struct {
    int x, y;        // X and Y coordinates on the screen
    int active;      // Whether the entity is currently active (1 = true, 0 = false)
} Entity;

typedef struct {
    float x, y;
    float direction;   // +1 = right, -1 = left
} Entity2;

typedef struct {
    Entity2 boss;
    char sizes[BOSS_H][BOSS_W];
} body;

int collision(int, int, int, int);  // Checks if two entities overlap
int collisionAdj(int, int, int, int); // Checks if two entities are adjacent

#endif // ENTITY_H_INCLUDED
