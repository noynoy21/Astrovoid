#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"
#include "render.h"

// ===================== MENU FUNCTION =====================
void showMenu() {
    system("cls");
    setColor(11);
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
    setColor(7);
}

// ===================== TUTORIAL DISPLAY =====================
void tutorialRound() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    setColor(10);
    printf("============== TUTORIAL ROUND ==============\n");
    setColor(7);
    printf("Use 'A' and 'D' to move left/right.\n");
    printf("Use 'W' and 'S' to move up/down.\n");
    printf("Press 'SPACEBAR' to shoot upward.\n");
    printf("Avoid falling enemies '*'.\n");
    setColor(14);
    printf("\nNote: if the meteor is too near. You will be hit.\n\n");
    setColor(10);
    printf("Your ship: ");
    setColor(9); printf("\u25B2"); setColor(7);
    printf(" | Enemies: ");
    setColor(12); printf("*"); setColor(7);
    printf("\n\nPress any key to start your mission...");
    _getch();
}

// ===================== PVP TUTORIAL =====================
void tutorialPVP() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    setColor(10);
    printf("============== PVP TUTORIAL ==============\n");
    setColor(7);
    printf("PLAYER 1 (Blue ");
    setColor(9); printf("\u25B2"); setColor(7);
    printf("):\n");
    printf("  Move: W/A/S/D\n");
    printf("  Shoot: SPACEBAR\n\n");
    
    printf("PLAYER 2 (Green ");
    setColor(10); printf("\u25BC"); setColor(7);
    printf("):\n");
    printf("  Move: ARROW KEYS\n");
    printf("  Shoot: ENTER\n\n");
    
    printf("Each player has 3 lives.\n");
    printf("Shoot your opponent to win!\n");
    printf("Pure PVP - No asteroids!\n");
    printf("\nPress any key to begin battle...");
    _getch();
}