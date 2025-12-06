#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct {
    int x;
    int y;
    int active;
    char sentence[50];
} Sentences;

void showMenu();        // Displays the main menu
void tutorialRound1();   // Displays tutorial before starting
int WINRound1();
int WINRound2();
int miniBossIntro();
int WINMiniBoss();
int WINBoss();
int creditsRoll();
void bossRoundMenu();
void tutorialPVP();     // Displays PVP tutorial

#endif // MENU_H_INCLUDED