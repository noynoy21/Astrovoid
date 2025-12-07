HOW TO RUN THE PROGRAM (using GCC in Windows OS):
1. In the console/command line, navigate to the specific folder containing the program's files.
2. Once in the correct directory, compile by typing the following command in the command line:
    > gcc -o astrovoid entity.c gameRound1.c gameRound2.c gameFinalBoss.c main.c mainGame.c menu.c pvp.c render.c config.c
    - This will create an executable file with the name of astrovoid.exe
    - To have a different name for the executable file, simply change 'astrovoid' in the command to the file name of your choice.
3. Either click the executable file to open the program, or execute the following in the command line:
    > [fileName].exe (e.g astrovoid.exe)
    - if this does not work, try the following command:
    > .\astrovoid.exe 
4. Play and enjoy the game!

SOURCE FILES:
1. config.c 
    - This only contains the initialization of the globar player score variable (GPlayerScore) wherein it starts with a value of 0.
2. entity.h
    - This contains the function logics for the entity collision checks.
3. gameFinalBoss.c 
    - This is where the gameplay logic lies for the Boss Round.
4. gameRound1.c
    - This is where the gameplay logic lies for Round 1.
5. gameRound2.c 
    - This is where the gameplay logic lies for Round 2.
6. main.c 
    - This file contains the main() function.
    - Here also lies the menu-selection mechanism of choosing a game-mode.
7. mainGame.c 
    - This contains the playGame() function.
    - This is where the whole single-player game progression is handled, where checks are made to see whether to proceed to the next round or not.
8. menu.c 
    - This file contains the files functions responsible for generating the gameplay cutscenes and gameplay menus.
9. pvp.c 
    - Contains the playPVP() function, which when called, executes the gameplay loop for the PVP game-mode.
10. render.c 
    - Contains the functions responsible for console control, drawing entities and borders (aesthetics), erasing sprites, and special effects (animations).

HEADER FILES:
1. config.h 
    - A centralized header file where macros used by the different functions are defined.
    - Contains the declaration of a global int variable (extern int GPlayerScore;).
2. entity.h
    - Contains the declaration of structs that are essential for the game sprites (player, bullets, enemies, hittables, bosses, and boss' bullets).
    - Contains the function prototypes of the collision-checking functions.
3. gameFinalBoss.h
    - Contains the function prototype of the final Boss Round gameplay logic
4. gameRound1.h
    - Contains the function prototype of the Round 1 gameplay logic
5. gameRound2.h
    - Contains the function prototypes for the Round 2 and Miniboss Round gameplay logics
6. mainGame.h
    - Contains the function prototype for the playgame(); function, which is called in the main() function when the player chooses to play in single-player mode. This function contains how the game rounds are supposed to progress.
7. menu.h 
    - Contains the function prototypes for all of the functions generating the game menu, tutorial menu, and gameplay "cutscenes" which are featured before, during, and after game rounds.
    - Contains the struct declaration Sentences which is used for the credits roll scene at the end of beating the game.
8. pvp.h
    - Contains the protype function for the PVP gameplay logic
    - Contains the declaration of the PVP bullets entity 
9. render.h 
    - Contains the prototype functions responsible for console control, drawing entities and borders (aesthetics), erasing sprites, and special effects (animations).
