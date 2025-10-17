#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

//board will always stay the same
const int HEIGHT=15;
const int WIDTH=50;

//position of the snakes head will be shared with the whole program
int snake_X;
int snake_Y;

int direction;

int tail_X[100];
int tail_Y[100];
int tail_length;

//position of the fruit will be shared with the whole program
int fruit_X;
int fruit_Y;

int quit, score;

void setup();
void fruit_position();
void draw_board();
void userinput();
void update_logic();
void check_collision();

int main() {

    setup();

    //if the program has not quit, perform the loop
    while (!quit) {
        draw_board();
        userinput();
        update_logic();
        printf("Score: %d\n", score);
        printf("Use WASD to move the snake or Q to quit:\n");
        Sleep(150);
    }

    printf("\nThanks for playing!\nYour final score is: %d", score);

    return 0;
}

//this function will do the initial setup of the program
void setup() {

    //the program will not quit and the score is 0
    quit=0;
    score=0;
    tail_length=0;
    srand(time(NULL));

    //places snakes head in the centre of the board
    snake_X = WIDTH/2;
    snake_Y = HEIGHT/2;

    //generates the first position for the fruit
    fruit_position();
}

//this function will randomise a location to put the fruit on the board
void fruit_position() {

    int valid_position=0;

    while (!valid_position) {

        //assume its a valid position
        valid_position = 1;

        //generates random coordinates, doesnt allow zero or on the walls of the board
        fruit_X = 1 + rand()%(WIDTH-2);
        fruit_Y = rand()%HEIGHT;

        //if the fruit is on the fruit its an invalid position
        if (fruit_X ==  snake_X && fruit_Y == snake_Y) {
            valid_position = 0;
        }

        //if the position is still valid, we check if the fruit is on the tail
        if (valid_position == 1) {

            //if the fruit is on the tail, its an invalid position and we leave the loop
            for (int i=0; i<tail_length; i++) {
                if (fruit_X == tail_X[i] && fruit_Y == tail_Y[i]) {
                    valid_position=0;
                    break;
                }
            }

        }

    }
}

//draws the actual board that the user will see
void draw_board() {

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
            else if (i==fruit_Y && j==fruit_X) {
                printf("@");
            }

            //draws the snakes head
            else if (i==snake_Y && j==snake_X) {
                printf("Q");
            }

            //will draw either tail part or white space
            else {
                int tail_found = 0;

                for (int k=0; k<tail_length; k++) {
                    if (i==tail_Y[k] && j==tail_X[k] ) {
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
                direction=1;
                break;
            case 'a':
                direction=2;
                break;
            case 's':
                direction=3;
                break;
            case 'd':
                direction=4;
                break;
            case 'q':
                quit = 1;
                break;
            default:
                printf("\n !!!!!!!!!!!!!!!invalid input!!!!!!!!!!!!!!!");
                break;
        }

    }
}

void update_logic() {

    int tempX1 = tail_X[0];
    int tempY1 = tail_Y[0];

    tail_X[0] = snake_X;
    tail_Y[0] = snake_Y;

    int tempX2, tempY2;

    for (int i=1; i<tail_length; i++) {
        tempX2 = tail_X[i];
        tempY2 = tail_Y[i];

        tail_X[i] = tempX1;
        tail_Y[i] = tempY1;

        tempX1 = tempX2;
        tempY1 = tempY2;
    }

    switch (direction) {
        case 1:
            snake_Y--;
            break;
        case 2:
            snake_X--;
            break;
        case 3:
            snake_Y++;
            break;
        case 4:
            snake_X++;
            break;
    }

    check_collision();
}

//what happens when the snake collides with something
void check_collision() {

    //if the snakes head touches the fruit
    if (snake_X == fruit_X && snake_Y == fruit_Y) {
        printf("\n you got one fruit!\n\n");
        fruit_position();
        score++;
        tail_length++;
        return;
    }

    //if the snakes head hits the wall
    if (snake_X <= 0 || snake_X >= WIDTH-1 || snake_Y < 0 || snake_Y >= HEIGHT) {
        quit = ;
    }

    //if the snakes head touches her tail
    for (int i=0; i<tail_length; i++) {
        if (snake_X == tail_X[i] && snake_Y == tail_Y[i]) {
            quit = 1;
        }
    }

}
