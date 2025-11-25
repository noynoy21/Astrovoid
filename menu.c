#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "menu.h"
#include "render.h"

// ===================== MENU FUNCTION =====================
void showMenu() {
    system("cls");         // Clears screen before printing menu
    setColor(11);          // Light cyan color for header
    printf("=====================================\n");
    printf("              ASTROVOID      \n"); // Game title
    printf("=====================================\n");
    setColor(14);          // Yellow for options
    printf("1. Start Game\n");
    printf("2. Exit\n");
    setColor(7);           // Reset color to white
    printf("=====================================\n");
}

// ===================== TUTORIAL DISPLAY =====================
void tutorialRound() {
    system("cls");         // Clear screen for tutorial section
    setColor(10);          // Green for title
    printf("============== TUTORIAL ROUND ==============\n");
    setColor(7);           // Reset color
    printf("Use 'A' and 'D' to move left/right.\n");
    printf("Use 'W' and 'S' to move up/down.\n");
    printf("Press 'SPACEBAR' to shoot upward.\n");
    printf("Avoid falling enemies '*'.\n");
    setColor(14);printf("\nNote: if the meteor is too near. You will be hit.\n\n"); setColor(10);
    printf("Your ship: ");
    setColor(9); printf("^"); setColor(7);      // Shows player symbol
    printf(" | Enemies: ");
    setColor(12); printf("*"); setColor(7);     // Shows enemy symbol
    printf("\n\nPress any key to start your mission...");
    _getch();              // Waits for any key press (pause until player is ready)
}
