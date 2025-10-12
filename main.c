#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//board will always stay the same
const int HEIGHT=9;
const int WIDTH=33;

//position of the snakes head will be shared with the whole program
int snake_X;
int snake_Y;

//position of the fruit will be shared with the whole program
int fruit_X;
int fruit_Y;

void starting_position();
void draw_board();

int main() {

    starting_position();

    while (!_kbhit()) {
        draw_board();
        printf("Use WASD to move the snake: ");
        Sleep(300);
    }

    return 0;
}

void starting_position() {
    srand(time(NULL));

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

