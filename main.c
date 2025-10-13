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
int score;

void setup();
void fruit_position();
void draw_board();
void movement();
void check_collision();

int main() {

    setup();

    //if the program has not quit, perform the loop
    while (quit==0) {

        //if the user has not pressed a key, perform the loop every 300 milliseconds
        while (!_kbhit()) {
            printf("\n");
            draw_board();
            printf("Score: %d\n", score);
            printf("Use WASD to move the snake or Q to quit: ");
            Sleep(300);
        }

        movement();
        check_collision();
    }
    return 0;
}

//this function will do the initial setup of the program
void setup() {

    //the program will not quit
    quit=0;
    score=0;

    //places snakes head in the centre of the board
    snake_X = WIDTH/2;
    snake_Y = HEIGHT/2;

    fruit_position();
}

//this function will randomise a location to put the fruit on the board
void fruit_position() {

    srand(time(NULL));

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

//draws the actual board that the user will see
void draw_board() {
    int i, j;

    printf("\n");

    //draws the top wall of board
    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }

    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {

            //draws the left and right walls of the board
            if (j==0||j==WIDTH-1) {
                printf("#");
            }

            //draws the fruit
            else if (i==fruit_Y && j==fruit_X) {
                printf("@");
            }

            //draws the snakes head
            else if (i==snake_Y && j==snake_X) {
                printf("o");
            }

            //leaves the rest as empty space
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    //draws the bottom wall of the board
    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }

    printf("\n");
}

//takes user input and makes the snake move on the board
void movement() {

    //gets the users input
    char key = _getch();

    //puts the character into lower case, so the user can use both lower and upper case
    switch (tolower(key)) {
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
            printf("\n\nThanks for playing!\n");
            quit = 1;
            break;
        default:
            printf("\n\n !!!!!!!!!!!!!!!invalid input!!!!!!!!!!!!!!!");
            break;
    }
}

//what happens when the snake collides with something
void check_collision() {

    //if the snakes head touches the fruit
    if (snake_X == fruit_X && snake_Y == fruit_Y) {
        printf("\n\n you got one fruit!");
        fruit_position();
        score++;
        return;
    }

    //if the snakes head hits the wall
    if (snake_X <= 0 || snake_X >= WIDTH-1 || snake_Y < 0 || snake_Y >= HEIGHT) {
        printf("\n\n game over!!\n");
        quit=1;
    }

}
