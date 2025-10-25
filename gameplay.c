#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#include "gameplay.h"

static struct settings {
    int speed;
    int quit;
    int score;
}s;

static int direction;
static int last_direction;

//preset directions
enum D {
    STOP = 0,
    UP,
    RIGHT,
    LEFT,
    DOWN
};

static struct position{
    int x;
    int y;
}snake, fruit;

static struct tail_position {
    int x[100];
    int y[100];
    int length;
}tail;

//board will always stay the same
static const int HEIGHT=15;
static const int WIDTH=50;

//this function will do the initial setup of the program
void setup() {
    srand(time(NULL));

    //the program will not quit and the score is 0
    s.quit=0;
    s.score=0;
    s.speed=150;
    tail.length=0;
    direction=STOP;

    //places snakes head in the centre of the board
    snake.x = WIDTH/2;
    snake.y = HEIGHT/2;

    //generates the first position for the fruit
    fruit_position();
}

void game_loop() {
    //if the program has not quit, perform the loop
    while (!is_game_over()) {
        draw_board();
        printf("Use WASD to move the snake\nP to pause\nQ to quit\n");
        printf("Score: %d\n", s.score);
        fflush(stdout);
        userinput();
        update_logic();
        Sleep(s.speed);
    }
}

//this function will randomise a location to put the fruit on the board
void fruit_position() {

    int valid_position=0;

    while (!valid_position) {

        //assume it's a valid position
        valid_position = 1;

        //generates random coordinates, doesn't allow zero or on the walls of the board
        fruit.x = 1 + rand()%(WIDTH-2);
        fruit.y = rand()%HEIGHT;

        //if the fruit is on the fruit it's an invalid position
        if (fruit.x ==  snake.x && fruit.y == snake.y) {
            valid_position = 0;
        }

        //if the position is still valid, we check if the fruit is on the tail
        if (valid_position == 1) {

            //if the fruit is on the tail, it's an invalid position and we leave the loop
            for (int i=0; i<tail.length; i++) {
                if (fruit.x == tail.x[i] && fruit.y == tail.y[i]) {
                    valid_position=0;
                    break;
                }
            }

        }

    }
}

//draws the actual board that the user will see
void draw_board() {

    //clears screen
    system("cls");

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
            else if (i==fruit.y && j==fruit.x) {
                printf("@");
            }

            //draws the snakes head
            else if (i==snake.y && j==snake.x) {
                printf("Q");
            }

            //will draw either tail part or white space
            else {
                int tail_found = 0;

                for (int k=0; k<tail.length; k++) {
                    if (i==tail.y[k] && j==tail.x[k] ) {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found) {
                    printf(" ");
                }

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
void userinput() {

    //if a key is pressed perform the loop
    if (_kbhit()){

        //puts the character into lower case, so the user can use both lower and upper case
        switch (tolower(_getch())) {
            case 'w':
                if (direction!=DOWN)
                    direction=UP;
                    break;
            case 'a':
                if (direction!=RIGHT)
                    direction=LEFT;
                    break;
            case 's':
                if (direction!=UP)
                    direction=DOWN;
                    break;
            case 'd':
                if (direction!=LEFT)
                    direction=RIGHT;
                    break;
            case 'p':
                if (direction!=STOP) {
                    last_direction=direction;
                    direction=STOP;
                    break;
                }
                else {
                    direction=last_direction;
                    break;
                }
            case 'q':
                s.quit = 1;
                break;
            default:
                printf("\n !!!!!!!!!!!!!!!invalid input!!!!!!!!!!!!!!!");
                break;
        }

    }
}

void update_logic() {

    //if the user did not pause the program, update the tail logic
    if (direction!=STOP) {
        int tempX1 = tail.x[0];
        int tempY1 = tail.y[0];

        tail.x[0] = snake.x;
        tail.y[0] = snake.y;

        int tempX2, tempY2;

        for (int i=1; i<tail.length; i++) {
            tempX2 = tail.x[i];
            tempY2 = tail.y[i];

            tail.x[i] = tempX1;
            tail.y[i] = tempY1;

            tempX1 = tempX2;
            tempY1 = tempY2;
        }
    }

    //moves the snake
    switch (direction) {
        case UP:
            snake.y--;
            break;
        case LEFT:
            snake.x--;
            break;
        case DOWN:
            snake.y++;
            break;
        case RIGHT:
            snake.x++;
            break;
    }

    check_collision();
}

//what happens when the snake collides with something
void check_collision() {

    //if the snakes head touches the fruit
    if (snake.x == fruit.x && snake.y == fruit.y) {
        fruit_position();
        s.score++;
        tail.length++;

        //the higher the score, the faster the snake moves
        s.speed = s.speed-(s.score*5);
        if (s.speed<50) {
            s.speed = 50;
        }

        return;
    }

    //if the snakes head hits the wall
    if (snake.x <= 0 || snake.x >= WIDTH-1 || snake.y < 0 || snake.y >= HEIGHT) {
        s.quit=1;
    }

    //if the snakes head touches her tail
    for (int i=0; i<tail.length; i++) {
        if (snake.x == tail.x[i] && snake.y == tail.y[i]) {
            s.quit=1;
        }
    }

}

int is_game_over() {
    return s.quit;
}

int get_score() {
    return s.score;
}

int game_speed() {
    return s.speed;
}