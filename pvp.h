#ifndef PVP_H_INCLUDED
#define PVP_H_INCLUDED

typedef struct {
    int x, y;
    int active;
    int owner;  // 1 for player1, 2 for player2
} PVPBullet;

void playPVP();  // PVP game mode

#endif // PVP_H_INCLUDED