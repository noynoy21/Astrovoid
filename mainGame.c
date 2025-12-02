#include "game.h"
#include "mainGame.h"

int playGame()
{
    int b;

    if (playRound1()) {

        b = playBOSS();
    }
}
