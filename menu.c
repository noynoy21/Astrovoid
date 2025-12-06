#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "menu.h"
#include "render.h"
#include "config.h"

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
void tutorialRound1() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    setColor(10);
    printf("============== TUTORIAL ROUND ==============\n");
    setColor(7);
    printf("Use 'A' and 'D' to move left/right.\n");
    printf("Use 'W' and 'S' to move up/down.\n");
    printf("Press 'SPACEBAR' to shoot upward.\n");
    printf("Avoid falling enemies '*'.\nThey cannot be hit.\n");
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

int WINRound1()
{
    system("cls");
    drawTitleBorder(23, 0, 4, HEIGHT / 2 - 2); // Specific parameters for the printed texts
    gotoxy(WIDTH / 2 - 6, HEIGHT / 2 - 1);
    setColor(10);
    printf("CONGRATULATIONS!");
    gotoxy(WIDTH / 2 - 9, HEIGHT / 2);
    setColor(14);
    printf("Press 1 to continue to");
    gotoxy(WIDTH / 2 - 3, HEIGHT / 2 + 1);
    printf("Round 2");
    setColor(7);
    
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                return 1;  // Return life to continue to round 2
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

int WINRound2()
{
    system("cls");
    drawTitleBorder(23, 0, 4, HEIGHT / 2 - 2); // Specific parameters for the printed texts
    gotoxy(WIDTH / 2 - 6, HEIGHT / 2 - 1);
    setColor(10);
    printf("CONGRATULATIONS!");
    gotoxy(WIDTH / 2 - 9, HEIGHT / 2);
    setColor(14);
    printf("Press 1 to continue to");
    gotoxy(WIDTH / 2 - 3, HEIGHT / 2 + 1);
    setColor(4);
    printf("MiniBoss");
    setColor(7);
    
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                return 1;  // player wants to continue to miniboss
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

int miniBossIntro(int width, int height){
    system("cls");
    drawTitleBorder(23, 0, 3, HEIGHT / 2 - 1); // Specific parameters for the printed texts
    gotoxy(WIDTH / 2 - 2, HEIGHT / 2 - 2);
    setColor(12);
    printf("+2 lives!");
    gotoxy(WIDTH / 2 - 2, HEIGHT / 2);
    setColor(12);
    printf("Uh oh...\n");
    gotoxy(WIDTH / 2 - 9, HEIGHT / 2+1);
    setColor(4); printf("SOMETHING"); setColor(12); printf(" is coming...");
    setColor(7);
    gotoxy(WIDTH / 2 - 9, HEIGHT / 2+3);
    printf("press 1 to continue...");
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                break;
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

int WINMiniBoss()
{
    system("cls");
    drawTitleBorder(27, 0, 2, HEIGHT / 2 - 1); // Specific parameters for the printed texts
    gotoxy(WIDTH/2-4, HEIGHT/2-2);
    setColor(10);
    printf("Miniboss Killed!");
    gotoxy(WIDTH/2-6, HEIGHT/2);
    printf("\"ARRGH! YOU GOT ME!\"");
    Sleep(3000);
    // New text box
    system("cls");
    drawTitleBorder(27, 0, 2, HEIGHT / 2 - 1); // Specific parameters for the printed texts
    gotoxy(WIDTH/2-2, HEIGHT/2-2);
    setColor(10);
    printf("+2 Lives!");
    gotoxy(WIDTH/2-9, HEIGHT/2);
    setColor(12);
    printf("\"BUT THIS IS ");
    setColor(4);
    printf("NOT THE END!\"");

    setColor(10);
    gotoxy(WIDTH/2-7, HEIGHT/2+2);
    printf("Press 1 to continue to");
    gotoxy(WIDTH / 2 - 2, HEIGHT / 2 + 3);
    setColor(4);
    printf("Final Boss");

    setColor(7);

    _getch();
    //bossRoundMenu();
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                return 1;  // player wants to continue to final boss
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

int WINBoss()
{
    system("cls");
    drawTitleBorder(27, 0, 2, HEIGHT / 2 - 1); // Specific parameters for the printed texts
    gotoxy(WIDTH/2-2, HEIGHT/2-2);
    setColor(10);
    printf("BOSS Killed!");
    gotoxy(WIDTH/2-8, HEIGHT/2);
    printf("\"WHAAT?! YOU BEAT ME?!\"");
    Sleep(3000);

    // New text box
    system("cls");
    drawTitleBorder(27, 0, 2, HEIGHT / 2 - 1); // Specific parameters for the printed texts
    gotoxy(WIDTH/2-1, HEIGHT/2-2);
    setColor(10);
    printf("Congrats!");
    gotoxy(WIDTH/2-9, HEIGHT/2);
    setColor(12);
    printf("\"CURSE YOU,  ");
    setColor(4);
    printf("CURSE YOU!!!\"");

    setColor(10);
    gotoxy(WIDTH/2-7, HEIGHT/2+2);
    printf("Press 1 to finish game");

    setColor(7);

    _getch();
    //bossRoundMenu();
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                return 1;  // player wants to finish
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

int creditsRoll()
{
    char words[][50] = {
        "    Made as a Machine Problem",
        "     project for the CMSC 11",
        "     class of the developers:",
        "       Benjamin A. Deypalan",
        "    Constantino T. Cesista Jr.",
        "       Dave Javenn G. Suan",
        "     Denzil John B. Claridad",
        "",
        "   A message to our instructor,",
        "            Sir Allan:",
        "   Thank you for the wonderful",
        "   semester! We really learned",
        "  a lot, and tried to implement",
        " all of the lessons you gave us.",
        "    Keep on soaring high, Sir!",
        "",
        "      Thank you for playing!",
        "  'till we meet again, Guardian!",
        "        Press 1 to finish",
    };

    int numWords = sizeof(words) / sizeof(words[0]);

    Sentences lines[numWords];

    for (int i = 0; i < numWords; i++) {
        lines[i].x = 1; lines[i].y = HEIGHT+i-1;
        lines[i].active = 1;
        strcpy(lines[i].sentence, words[i]);
    }

    while (1) {
        system("cls");
        drawBorder(WIDTH+15, HEIGHT);
        int tempNum = numWords-1;
        for (int i = 0; i < numWords-1; i++) {
            if (lines[i].y < HEIGHT && lines[i].y > 0) 
                lines[i].active = 1;
            else 
                lines[i].active = 0;
            if (lines[i].active) {  
                setColor(9);
                gotoxy(lines[i].x, lines[i].y);
                puts(lines[i].sentence);
            }

            lines[i].y--;
        }

        if (lines[tempNum].y <= HEIGHT/2) {
            setColor(1);
            gotoxy(lines[tempNum].x, lines[tempNum].y);
            puts(lines[tempNum].sentence);
            break;
        } 
        else if (lines[tempNum].y < HEIGHT) {
            setColor(1);
            gotoxy(lines[tempNum].x, lines[tempNum].y);
            puts(lines[tempNum].sentence);
        }
        
        lines[tempNum].y--;
        Sleep(1000);
    }
    while(1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == '1') {
                return 1;  // player wants to finish
            } else if (choice == 27) {
                return 0;  // ESC to exit
            }
        }
    }
}

void bossRoundMenu() {
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    setColor(10);
    printf("============== BOSS ROUND ==============\n");
    setColor(7);
    printf("The boss's attack speed increases as its health decreases.\n");
    setColor(14);
    printf("\nGOOD LUCK.\n\n");
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

void transitionText();
