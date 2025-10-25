#include <stdio.h>
#include <windows.h>

#include "menu.h"
#include "gameplay.h"

int main() {
    int play_again=1;

    title_screen();

    while (play_again) {
        setup();

        //if the program has not quit, perform the loop
        while (!game_over()) {
            draw_board();
            userinput();
            update_logic();
            printf("Use WASD to move the snake\nP to pause\nQ to quit\n");
            printf("Score: %d\n", get_score());
            Sleep(game_speed());
        }
        int score = get_score();
        play_again = quit_menu(score);
    }

    return 0;
}