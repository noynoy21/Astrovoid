#include "gameRound1.h"
#include "gameRound2.h"
#include "gameBoss.h"
#include "mainGame.h"

int playGame()
{
    int playerLife = playRound1();

    if (playerLife) {
        playerLife = playRound2(playerLife);
    }

    if (playerLife) {
        playBOSS();
    }
}
