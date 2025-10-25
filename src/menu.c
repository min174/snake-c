#include "../include/menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

static const char* title_art[] = {
    "####################################################",
    "#  _____   ___     _   ______   _   __  _____   _  #",
    "# |  ___| |   \\   | | |  __  | | | / / |  ___| | | #",
    "# | |___  | |\\ \\  | | | |__| | | |/ /  | |_    | | #",
    "# |___  | | | \\ \\ | | |  __  | |   <   |  _|   |_| #",
    "#  ___| | | |  \\ \\| | | |  | | | |\\ \\  | |___   _  #",
    "# |_____| |_|   \\___| |_|  |_| |_| \\_\\ |_____| |_| #",
    "#                                                  #",
    "#                 [P] Play                         #",
    "#                 [L] Leaderboard                  #",
    "#                 [Q] Quit                         #",
    "#                                                  #",
    "####################################################"
};

static struct leaderboard{
    int rank;
    int score;
    char name[8];
}lb;

void title_screen() {
    system("cls");
    char choice;

    //calculates how many lines are in the art array
    int number_lines = sizeof(title_art)/sizeof(title_art[0]);

    for (int i=0; i<number_lines; i++) {
        printf("%s\n", title_art[i]);
    }

    printf("Type your choice here: ");
    scanf(" %c", &choice);

    choice = tolower(choice);

    if (choice=='p') {
        return;
    }
    if (choice == 'l') {
        leaderboard();
    }
    if (choice == 'q') {
        exit(0);
    }

}

void leaderboard() {
    system("cls");

    FILE* fptr;
    fptr = fopen("leaderboard.txt", "r");

    printf("----------------LEADERBOARD----------------\nRANK\tNAME\tSCORE\n");


    if (fptr == NULL) {
        printf("ERROR: COULD NOT OPEN FILE");
    }
    else {
        while (fscanf(fptr,"%d %d %s", &lb.rank, &lb.score, lb.name) == 3) {
            printf("%d.\t%s\t%d\n", lb.rank, lb.name, lb.score);
        }
    }
    fclose(fptr);

    for (int i=0; i<43;i++) {
        printf("-");
    }

    printf("\nPress any button to go back to main menu: \n");

    //breaks loop only once a button is pressed
    while (1) {
        if (_kbhit()) {
            //removes letter pressed
            _getch();
            break;
        }
    }
    title_screen();
}

int quit_menu(int final_score) {
    system("cls");

    char answer;

    printf("Thank you for playing!\nYour final score is: %d\n", final_score);

    while (1) {
        printf("Play again?\nY/N\n");
        while (1) {
            if (_kbhit()) {
                answer = _getch();
                answer = tolower(answer);
                break;
            }
        }

        if (answer=='y') {
            return 1;
        }
        else if (answer == 'n') {
            return 0;
        }
        else{
            system("cls");
            printf("Invalid input, please try again!\n");
        }

    }

}