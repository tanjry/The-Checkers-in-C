#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "components.h"

int game_over = 1, i, j;

void game_init();
void main_menu();
void game_start(int p2);
void how_to_play();
void game_update();
void game_playing();

int main() {
    game_init();

    return 0;
}

void game_init() {
    main_menu();
}

void main_menu() {
    char cmd;
    system("cls");
    printf("\n\n%40s%-40s", "-------", "-------");
    printf("%40s%-40s", "|The Ch", "eckers|");
    printf("%40s%-40s", "-------", "-------");
    printf("\n\n\n\n\n");
    printf("%40s%-40s\n\n\n", "1. Player ", "VS Player");
    printf("%40s%-40s\n\n\n", "2. Player V", "S Computer");
    printf("%40s%-40s\n\n\n\n\n\n\n", "3. How t", "o play");
    while (1) {
        cmd = getch();
        if (cmd == '1') {
            // Play with friend
            game_start(0);
            break;
        }
        else if (cmd == '2') {
            // Play with bot
            game_start(1);
            break;
        }
        else if (cmd == '3') {
            // View how to play
            how_to_play();
            break;
        }
    }
}

void game_start(int p2) {
    /* p2 : status of player 2 (0 if human / 1 if bot) */
    game_over = 0;
    generate_components(p2);
    while (!game_over) {
        char end;
        game_update();
        game_playing();
        end = getch();
        if (end == 's') break;
    }
}

void how_to_play() {
    system("cls");
    printf("Go kill yourself.");
}

void game_update() {
    system("cls");
    printf("\n\n");
    for (i = 0; i < height; i++) {
        printf("\t\t\t+---+---+---+---+---+---+---+---+\n\t\t\t");
        printf("|");
        for (j = 0; j < width; j++) {
            if (gameboard[i][j].owner == 0) {
                printf("   |");
            }
            else if (gameboard[i][j].owner == 1) {
                printf(" x |");
            }
            else if (gameboard[i][j].owner == 2) {
                printf(" o |");
            }
        }
        printf("\n");
    }
    printf("\t\t\t+---+---+---+---+---+---+---+---+");
}

void game_playing() {

}