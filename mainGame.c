#include "gameRound1.h"
#include "gameRound2.h"
#include "gameFinalBoss.h"
#include "mainGame.h"
#include "config.h"
#include "menu.h"

int playGame()
{
    // Play Round 1 
    int playerLife = playRound1();

    // terminate gameplay sequence if the player lost the first round or the player does not want to continue (or both)
    if (!playerLife || !WINRound1()) {
        return 0;
    }

    playerLife = playRound2(playerLife);

    // terminate gameplay sequence if the player lost the first round or the player does not want to continue (or both)
    if (!playerLife || !WINRound2()) {
        return 0;
    }

    miniBossIntro();
    playerLife = playMiniBoss(playerLife);

    if (!playerLife || !WINMiniBoss()) {
        return 0;
    }

    if (playBOSS(playerLife)) {
        WINBoss();
        creditsRoll();
    }

    // Terminate gameplay sequence if the player lost the 
    
    return 0;
}

/*
int executeRound1()
{
    return playRound1;
}

int executeRound2(int life)
{
    int playerLife = playRound2(life);
    if 
}*/