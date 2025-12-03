#include "gameRound1.h"
#include "gameRound2.h"
#include "mainGame.h"

int playGame()
{
    // Play Round 1
    int playerLife = playRound1();

    // If player survived Round 1, proceed to Round 2
    if (playerLife > 0) {
        playerLife = playRound2(playerLife);
        
        // If player survived Round 2, proceed to Final Boss
        if (playerLife > 0) {
            playBOSS(playerLife);
        }
    }
    
    return 0;
}