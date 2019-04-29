#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "components.h"
#include "utils.h"

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
        game_update();
    }
}

void how_to_play() {
    system("cls");
    printf("Go kill yourself.");
}

void game_update() {
    game_playing();
}

void game_playing() {
    int key;
    while (1) {
        update_board();
        key = getch();
        if (key == 0 || key == 0xE0) key = getch();
        if (key == 72) {
            slct.current_y = max(slct.current_y - 1, 0);
        }
        else if (key == 80) {
            slct.current_y = min(slct.current_y + 1, height-1);
        }
        else if (key == 75) {
            slct.current_x = max(slct.current_x - 1, 0);
        }
        else if (key == 77) {
            slct.current_x = min(slct.current_x + 1, width-1);
        }
        else if (key == ' ') {

            /* Selecting */
            if (gameboard[slct.current_y][slct.current_x].owner == playing) {
                slct.selected_x = slct.current_x;
                slct.selected_y = slct.current_y;
            }

            else if (gameboard[slct.selected_y][slct.selected_x].state == 2) {
                if (king_move()) {
                    // Move the checker
                    gameboard[slct.current_y][slct.current_x].owner = playing;
                    gameboard[slct.current_y][slct.current_x].state = gameboard[slct.selected_y][slct.selected_x].state;
                    gameboard[slct.selected_y][slct.selected_x].owner = 0;

                    // Clear selector
                    slct.selected_x = width;
                    slct.selected_y = height;
                    swap_turn();
                }
            }

            else if (gameboard[slct.selected_y][slct.selected_x].state == 1) {
                /* Kill enemy while moving */
                if (can_kill_left() || can_kill_right()) {
                    int direction = (can_kill_right() ? 1 : -1);
                    // Move the checker
                    gameboard[slct.current_y][slct.current_x].owner = playing;
                    gameboard[slct.current_y][slct.current_x].state = gameboard[slct.selected_y][slct.selected_x].state;
                    gameboard[slct.selected_y][slct.selected_x].owner = 0;

                    // Become King
                    if ((playing == 1 && slct.current_y == 0) || (playing == 2 && slct.current_y == 7)) {
                        gameboard[slct.current_y][slct.current_x].state = 2;
                    }

                    // Kill enemy
                    gameboard[slct.selected_y + foward()][slct.selected_x + direction].owner = 0;
                    gameboard[slct.selected_y + foward()][slct.selected_x + direction].owner = 0;
                    if (playing == 1) {
                        player1.remaining -= 1;
                    }
                    else {
                        player2.remaining -= 1;
                    }

                    // Move selector
                    slct.selected_x = slct.current_x;
                    slct.selected_y = slct.current_y;

                    // Keep killing on the left
                    slct.current_x = max(slct.current_x-2, 0);
                    slct.current_y += foward() * 2;
                    if (can_kill_left()) continue;

                    // Keep killing on the right
                    slct.current_x = min(slct.current_x+4, 7);
                    if (can_kill_right()) continue;

                    // Clear selector
                    slct.selected_x = width;
                    slct.selected_y = height;
                    swap_turn();
                }

                /* Moving a checker */
                else if (can_move()) {
                    // Move the checker
                    gameboard[slct.current_y][slct.current_x].owner = playing;
                    gameboard[slct.current_y][slct.current_x].state = gameboard[slct.selected_y][slct.selected_x].state;
                    gameboard[slct.selected_y][slct.selected_x].owner = 0;

                    // Become King
                    if ((playing == 1 && slct.current_y == 0) || (playing == 2 && slct.current_y == 7)) {
                        gameboard[slct.current_y][slct.current_x].state = 2;
                    }

                    // Clear selector
                    slct.selected_x = width;
                    slct.selected_y = height;
                    swap_turn();
                }
            }
        }
        else if (key == 27) {
            game_over = 1;
            break;
        }
    }
}