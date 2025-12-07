#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "render.h"
#include "menu.h"
#include "mainGame.h"
#include "pvp.h"
#include "gameRound1.h"
#include "gameRound2.h"
#include "gameFinalBoss.h"
#include "config.h"

/* 
    CMSC 11 Machine Problem
    Astrovoid
    Group Members:
    - Cesista, Constantino T. Jr.
    - Claridad, Denzil John B.
    - Deypalan, Benjamin A.
    - Suan, Dave Javenn G.
*/

// Compile command:
// gcc -o astrovoid entity.c gameRound1.c gameRound2.c gameFinalBoss.c main.c mainGame.c menu.c pvp.c render.c config.c

// ===================== MAIN FUNCTION =====================
int main() {
    system("cls");
    hideCursor();

    int choice;
    while (1) {
        showMenu();
        printf("\nSelect an option: ");
        
        // Better input handling
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1:        // Single Player
                tutorialRound1();
                playGame();
                break;
            case 2:        // PVP Mode
                tutorialPVP();
                playPVP();
                break;
            case 3:        // Exit
                printf("\nThanks for playing, Guardian!\n");
                Sleep(1000);
                return 0;
            // Testing Cases (developer easter eggs)
            case 67:
                playRound2(7);
                break;
            case 69:
                playMiniBoss(MAX_PLAYER_LIFE);
                break;
            case 420:
                playBOSS(MAX_PLAYER_LIFE);
                WINBoss();
                creditsRoll();
                break;
            case 666:
                creditsRoll();
                break;
            default:
                printf("Invalid choice! Try again.\n");
                Sleep(1000);
        }
    }
    return 0;
}