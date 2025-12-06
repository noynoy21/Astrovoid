#include "gameRound1.h"
#include "gameRound2.h"
#include "mainGame.h"

int playGame()
{
    // Play Round 1 
    int playerLife = playRound1();

<<<<<<< Updated upstream
    // If player survived Round 1, proceed to Round 2 
    if (playerLife > 0) {
        playerLife = playRound2();  
        
        // If player survived Round 2, proceed to Final Boss 
        if (playerLife > 0) {
            playBOSS();  
        }
=======
    // terminate gameplay sequence if the player lost the first round or the player does not want to continue (or both)
    if (!playerLife || !WINRound1()) {
        return 0;
    }

    playerLife = playRound2(playerLife);

    // terminate gameplay sequence if the player lost the first round or the player does not want to continue (or both)
    if (!playerLife || !WINRound2()) {
        return 0;
    }

    miniBossIntro(WIDTH, HEIGHT);                        // Intro cutscene for the miniboss
    playerLife = playMiniBoss(playerLife);  // Executes the miniboss round

    
    // Terminate gameplay sequence if the player lost the 
    if (!playerLife || !WINMiniBoss()) {
        return 0;
    }

    if (playBOSS(playerLife)) {
        WINBoss();
        creditsRoll();
>>>>>>> Stashed changes
    }
    
    return 0;
}