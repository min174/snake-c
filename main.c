#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//board will always stay the same
const int HEIGHT=9;
const int WIDTH=25;

//position of the snakes head will be shared with the whole program
int snake_X;
int snake_Y;

//position of the fruit will be shared with the whole program
int fruit_X;
int fruit_Y;

int quit;

void starting_positions();
void draw_board();
void movement();
void check_collision();

int main() {

    starting_positions();

    while (quit==0) {
        while (!_kbhit()) {
            printf("\n");
            draw_board();
            printf("Use WASD to move the snake: ");
            Sleep(300);
        }

        movement();
        check_collision();
    }
    return 0;
}

void starting_positions() {
    srand(time(NULL));

    //the program will not quit
    quit=0;

    //places snakes head in the centre of the board
    snake_X = WIDTH/2;
    snake_Y = HEIGHT/2;

    //generates random X coordinate, if its zero, randomise again
    fruit_X = rand()%WIDTH;
    while (fruit_X == 0) {
        fruit_X = rand()%WIDTH;
    }

    //generates random Y coordinate, if its zero, randomise again
    fruit_Y = rand()%HEIGHT;
    while (fruit_Y == 0) {
        fruit_Y = rand()%HEIGHT;
    }
}

void draw_board() {
    int i, j;

    printf("\n");

    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }

    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j==0||j==WIDTH-1) {
                printf("#");
            }
            else if (i==fruit_Y && j==fruit_X) {
                printf("@");
            }
            else if (i==snake_Y && j==snake_X) {
                printf("o");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }

    printf("\n");
}

void movement() {

    char key = _getch();

    switch (key) {
        case 'w':
            snake_Y--;
            break;
        case 'a':
            snake_X--;
            break;
        case 's':
            snake_Y++;
            break;
        case 'd':
            snake_X++;
            break;
        case 'q':
            quit = 1;
            break;
        default:
            printf("\n\n !!!!!!!!!!!!!!!invalid input!!!!!!!!!!!!!!!");
            break;
    }
}

void check_collision() {

    if (snake_X <= 0 || snake_X >= WIDTH - 1) {
        printf("\n\n game over!!\n");
        quit = 1;
    }

    if (snake_Y < 0 || snake_Y >= HEIGHT) {
        printf("\n\n game over!!\n");
        quit = 1;
    }
}
