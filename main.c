#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "render.h"
#include "entity.h"
#include "menu.h"
#include "game.h"

// ===================== MAIN FUNCTION =====================
int main() {
    system("cls");         // Clears the screen before starting
    hideCursor();          // Removes blinking cursor for aesthetic gameplay

    int choice;            // Stores user menu choice
    while (1) {            // Infinite loop for continuous menu display
        showMenu();        // Draws the menu
        printf("\nSelect an option: ");  // Prompts user for input
        scanf("%d", &choice);            // Reads user's choice

        switch (choice) {  // Evaluates user’s input
            case 1:        // If user selects “Start Game”
                tutorialRound();         // Show tutorial instructions
                playGame();              // Start actual gameplay
                break;
            case 2:        // If user selects “Exit”
                printf("\nThanks for playing, Guardian!\n");
                Sleep(1000);             // Short delay before closing
                return 0;                // Exit program
            default:       // Handles invalid inputs
                printf("Invalid choice! Try again.\n");
                Sleep(1000);
        }
    }
    return 0;              // Program never reaches here due to infinite loop
}
