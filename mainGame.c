#include "gameRound1.h"
#include "mainGame.h"

int playGame()
{
    int playerLife = playRound1();

    if (playerLife) {
        playBOSS();
    }
}
