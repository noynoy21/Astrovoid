#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "render.h"
#include "menu.h"
#include "mainGame.h"
#include "pvp.h"
#include "gameRound2.h"

// Compile command:
// gcc -o astrovoid entity.c gameRound1.c gameRound2.c main.c mainGame.c menu.c render.c pvp.c

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
                tutorialRound();
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
            default:
                printf("Invalid choice! Try again.\n");
                Sleep(1000);
        }
    }
    return 0;
}