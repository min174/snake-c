#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

const int HEIGHT=9;
const int WIDTH=33;

int snake_X;
int snake_Y;

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
        printf("\n");
    }

    return 0;
}

void starting_position() {
    srand(time(NULL));

    snake_X = WIDTH/2;
    snake_Y = HEIGHT/2;

    fruit_X = rand()%WIDTH;
    while (fruit_X == 0) {
        fruit_X = rand()%WIDTH;
    }

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
