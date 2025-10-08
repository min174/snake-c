#include <stdio.h>

const int HEIGHT=10;
const int WIDTH=33;

void draw_board();

int main() {
    draw_board();
    return 0;
}

void draw_board() {
    int i;

    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }

    printf("\n");

    for (i=0;i<HEIGHT;i++) {
        printf("#\t\t\t\t#\n");
    }

    for (i = 0; i < WIDTH; i++) {
        printf("#");
    }
}
