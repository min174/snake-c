#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

//board will always stay the same
const int HEIGHT=15;
const int WIDTH=50;

const char* title_art[] = {
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

enum D {
    STOP = 0,
    UP,
    RIGHT,
    LEFT,
    DOWN
};

int direction;
int last_direction;

struct game_state {
    int speed;
    int quit;
    int score;
}gs;

struct position{
    int x;
    int y;
}snake, fruit;

struct tail_position {
    int x[100];
    int y[100];
    int length;
}tail;

void setup();
void fruit_position();
void draw_board();
void userinput();
void update_logic();
void check_collision();
int quit_menu();
void title_screen();

int main() {
    int play_again=1;
    gs.speed = 150;

    title_screen();

    while (play_again) {

        setup();

        //if the program has not quit, perform the loop
        while (!gs.quit) {
            draw_board();
            userinput();
            update_logic();
            printf("Use WASD to move the snake\nP to pause\nQ to quit\n");
            printf("Score: %d\n", gs.score);
            Sleep(gs.speed);
        }
        play_again = quit_menu();
    }

    return 0;
}

void title_screen() {

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
    if (choice=='q') {
        exit(0);
    }

}

//this function will do the initial setup of the program
void setup() {
    srand(time(NULL));

    //the program will not quit and the score is 0
    gs.quit=0;
    gs.score=0;
    tail.length=0;
    direction=STOP;

    //places snakes head in the centre of the board
    snake.x = WIDTH/2;
    snake.y = HEIGHT/2;

    //generates the first position for the fruit
    fruit_position();
}

int quit_menu() {
    system("cls");

    char answer;

    printf("Thank you for playing!\nYour final score is: %d\n", gs.score);

    while (1) {
        printf("Play again?\nY/N\n");
        scanf(" %c", &answer);

        answer = tolower(answer);

        if (answer=='y') {
            gs.quit=0;
            return 1;
        }
        else if (answer == 'n') {
            return 0;
        }
        else{
            printf("\nInvalid input, please try again!\n");
        }
    }

}

//this function will randomise a location to put the fruit on the board
void fruit_position() {

    int valid_position=0;

    while (!valid_position) {

        //assume its a valid position
        valid_position = 1;

        //generates random coordinates, doesnt allow zero or on the walls of the board
        fruit.x = 1 + rand()%(WIDTH-2);
        fruit.y = rand()%HEIGHT;

        //if the fruit is on the fruit its an invalid position
        if (fruit.x ==  snake.x && fruit.y == snake.y) {
            valid_position = 0;
        }

        //if the position is still valid, we check if the fruit is on the tail
        if (valid_position == 1) {

            //if the fruit is on the tail, its an invalid position and we leave the loop
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
                gs.quit = 1;
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
        printf("\n you got one fruit!\n\n");
        fruit_position();
        gs.score++;
        tail.length++;

        //the higher the score, the faster the snake moves
        gs.speed = gs.speed-(gs.score*5);
        if (gs.speed<50) {
            gs.speed = 50;
        }

        return;
    }

    //if the snakes head hits the wall
    if (snake.x <= 0 || snake.x >= WIDTH-1 || snake.y < 0 || snake.y >= HEIGHT) {
        gs.quit=1;
    }

    //if the snakes head touches her tail
    for (int i=0; i<tail.length; i++) {
        if (snake.x == tail.x[i] && snake.y == tail.y[i]) {
            gs.quit=1;
        }
    }

}
