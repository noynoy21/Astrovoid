#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "menu.h"
#include "render.h"

// ===================== MENU FUNCTION =====================
void showMenu() {
    system("cls");         // Clears screen before printing menu
    setColor(11);          // Light cyan color for header
printf("  ___   _____ ___________ _____  _   _  _____ ___________                                            \n");
    printf(" / _ \\ /  ___|_   _| ___ \\  _  || | | ||  _  |_   _|  _  \\                                           \n");
    printf("/ /_\\ \\\\ `--.  | | | |_/ / | | || | | || | | | | | | | | |                                           \n");
    printf("|  _  | `--. \\ | | |    /| | | || | | || | | | | | | | | |                                           \n");
    printf("| | | |/\\__/ / | | | |\\ \\\\ \\_/ /\\ \\_/ /\\ \\_/ /_| |_| |/ /                                            \n");
    printf("\\_| |_/\\____/  \\_/ \\_| \\_|\\___/  \\___/  \\___/ \\___/|___/                                             \n");
    printf("                                                                                                      \n");
    printf("                                                                                                      \n");
    printf(" ___   __    ___     _____ _____ _   _ _____  _      _____      ______ _       _____   _____________ \n");
    printf("|  _| /  |  |_  |   /  ___|_   _| \\ | |  __ \\| |    |  ___|     | ___ \\ |     / _ \\ \\ / /  ___| ___ \\ \n");
    printf("| |   `| |    | |   \\ `--.  | | |  \\| | |  \\/| |    | |__ ______| |_/ / |    / /_\\ \\ V /| |__ | |_/ / \n");
    printf("| |    | |    | |    `--. \\ | | | . ` | | __ | |    |  __|______|  __/| |    |  _  |\\ / |  __||    /  \n");
    printf("| |   _| |_   | |   /\\__/ /_| |_| |\\  | |_\\ \\| |____| |___      | |   | |____| | | || | | |___| |\\ \\  \n");
    printf("| |_  \\___/  _| |   \\____/ \\___/\\_| \\_/\\____/\\_____/\\____/      \\_|   \\_____/\\_| |_/\\_/ \\____/\\_| \\_| \n");
    printf("|___|       |___|                                                                                    \n");
    printf("                                                                                                      \n");
    printf(" ___   _____   ___   ______      ______                                                               \n");
    printf("|  _| / __  \\ |_  |  | ___ \\     | ___ \\                                                              \n");
    printf("| |   `' / /'   | |  | |_/ /_   _| |_/ /                                                              \n");
    printf("| |     / /     | |  |  __/\\ \\ / /  __/                                                               \n");
    printf("| |   ./ /___   | |  | |    \\ V /| |                                                                  \n");
    printf("| |_  \\_____/  _| |  \\_|     \\_/ \\_|                                                                  \n");
    printf("|___|         |___|                                                                                   \n");
    printf("                                                                                                      \n");
    printf(" ___   _____   ___    _______   _______ _____                                                         \n");
    printf("|  _| |____ | |_  |  |  ___\\ \\ / /_   _|_   _|                                                        \n");
    printf("| |       / /   | |  | |__  \\ V /  | |   | |                                                          \n");
    printf("| |       \\ \\   | |  |  __| /   \\  | |   | |                                                          \n");
    printf("| |   .___/ /   | |  | |___/ /^\\ \\_| |_  | |                                                          \n");
    printf("| |_  \\____/   _| |  \\____/\\/   \\/\\___/  \\_/                                                          \n");
    printf("|___|         |___|                                                                                   \n");

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
