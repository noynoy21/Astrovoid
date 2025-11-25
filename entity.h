#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

typedef struct {
    int x, y;        // X and Y coordinates on the screen
    int active;      // Whether the entity is currently active (1 = true, 0 = false)
} Entity;

int collision(int, int, int, int);  // Checks if two entities overlap
int collisionAdj(int, int, int, int); // Checks if two entities are adjacent

#endif // ENTITY_H_INCLUDED
