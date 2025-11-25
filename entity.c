#include "entity.h"

// Returns 1 if coordinates overlap, else 0
int collision(int x1, int y1, int x2, int y2) {
    return (x1 == x2 && y1 == y2);         // True if same position
}

// for nearer meteors
int collisionAdj(int x1, int y1, int x2, int y2){
    return (x1 == x2 && (y1 == y2+1 || y1 == y2-1));
}
