#include <stdio.h>

#include "menu.h"
#include "gameplay.h"

int main() {
    int play_again=1;
    int final_score=0;

    title_screen();

    while (play_again) {
        setup();
        game_loop();
        final_score = get_score();
        play_again = quit_menu(final_score);
    }
    return 0;
}