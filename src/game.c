#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
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
    printf("%40s%-40s\n\n\n", "1. Star", "t Game");
    printf("%40s%-40s\n\n\n\n\n\n\n", "2. How t", "o play");
    while (1) {
        cmd = getch();
        if (cmd == '1') {
            // Play with friend
            game_start(0);
            break;
        }
        else if (cmd == '2') {
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
    printf("Game Over !\nPlayer %d win !!", opponent());
}

void how_to_play() {
    system("cls");
    printf("Go kill yourself.");
}

void game_update() {
    game_playing();
}

void game_playing() {
    int key, temp_x1, temp_y1, temp_x2, temp_y2, can_kill = 0;
    while (1) {
        warp:
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
            temp_x1 = slct.current_x;
            temp_y1 = slct.current_y;
            temp_x2 = slct.selected_x;
            temp_y2 = slct.selected_y;
            can_kill = force_kill();

            slct.current_x = temp_x1;
            slct.current_y = temp_y1;
            slct.selected_x = temp_x2;
            slct.selected_y = temp_y2;

            /* Selecting */
            if (gameboard[slct.current_y][slct.current_x].owner == playing) {
                slct.selected_x = slct.current_x;
                slct.selected_y = slct.current_y;
            }

            else if (gameboard[slct.selected_y][slct.selected_x].state == 2) {
                if (king_kill()) {
                    // Move the checker
                    int dir_x, dir_y;
                    gameboard[slct.current_y][slct.current_x].owner = playing;
                    gameboard[slct.current_y][slct.current_x].state = gameboard[slct.selected_y][slct.selected_x].state;
                    gameboard[slct.selected_y][slct.selected_x].owner = 0;

                    // Kill enemy
                    dir_x = (slct.current_x < slct.selected_x ? 1 : -1);
                    dir_y = (slct.current_y < slct.selected_y ? 1 : -1);
                    gameboard[slct.current_y + dir_y][slct.current_x + dir_x].owner = 0;
                    gameboard[slct.current_y + dir_y][slct.current_x + dir_x].state = 0;

                    if (playing == 1) {
                        player2.remaining -= 1;
                    }
                    else {
                        player1.remaining -= 1;
                    }

                    // Move selector
                    slct.selected_x = slct.current_x;
                    slct.selected_y = slct.current_y;

                    // Keep killing
                    int end_x, end_y;
                    // Top Left
                    slct.current_x = slct.selected_x;
                    slct.current_y = slct.selected_y;
                    end_x = slct.current_x - min(slct.selected_x, slct.selected_y);
                    end_y = slct.current_y - min(slct.selected_x, slct.selected_y);
                    while (slct.current_x >= end_x) {
                        if (king_kill()) goto warp;
                        slct.current_x--;
                        slct.current_y--;
                    }
                    // Top Right
                    slct.current_x = slct.selected_x;
                    slct.current_y = slct.selected_y;
                    end_x = slct.current_x + min(7 - slct.selected_x, slct.selected_y);
                    end_y = slct.current_y - min(7 - slct.selected_x, slct.selected_y);
                    while (slct.current_x <= end_x) {
                        if (king_kill()) goto warp;
                        slct.current_x++;
                        slct.current_y--;
                    }
                    // Btm Left
                    slct.current_x = slct.selected_x;
                    slct.current_y = slct.selected_y;
                    end_x = slct.current_x - min(slct.selected_x, 7 - slct.selected_y);
                    end_y = slct.current_y + min(slct.selected_x, 7 - slct.selected_y);
                    while (slct.current_x >= end_x) {
                        if (king_kill()) goto warp;
                        slct.current_x--;
                        slct.current_y++;
                    }
                    // Btm Right
                    slct.current_x = slct.selected_x;
                    slct.current_y = slct.selected_y;
                    end_x = slct.current_x + min(7 - slct.selected_x, 7 - slct.selected_y);
                    end_y = slct.current_y + min(7 - slct.selected_x, 7 - slct.selected_y);
                    while (slct.current_x <= end_x) {
                        if (king_kill()) goto warp;
                        slct.current_x++;
                        slct.current_y++;
                    }

                    // Clear selector
                    slct.selected_x = width;
                    slct.selected_y = height;
                    swap_turn();
                }
                else if (king_move()) {
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
                    int dir = (can_kill_right() ? 1 : -1);
                    // Move the checker
                    gameboard[slct.current_y][slct.current_x].owner = playing;
                    gameboard[slct.current_y][slct.current_x].state = gameboard[slct.selected_y][slct.selected_x].state;
                    gameboard[slct.selected_y][slct.selected_x].owner = 0;

                    // Kill enemy
                    gameboard[slct.selected_y + foward()][slct.selected_x + dir].owner = 0;
                    gameboard[slct.selected_y + foward()][slct.selected_x + dir].state = 0;

                    // Become King
                    if ((playing == 1 && slct.current_y == 0) || (playing == 2 && slct.current_y == 7)) {
                        gameboard[slct.current_y][slct.current_x].state = 2;
                    }

                    if (playing == 1) {
                        player2.remaining -= 1;
                    }
                    else {
                        player1.remaining -= 1;
                    }

                    // Move selector
                    slct.selected_x = slct.current_x;
                    slct.selected_y = slct.current_y;

                    // Keep killing on the left
                    slct.current_x = max(slct.current_x - 2, 0);
                    slct.current_y += foward() * 2;
                    if (can_kill_left()) goto warp;

                    // Keep killing on the right
                    slct.current_x = slct.selected_x;
                    slct.current_x = min(slct.current_x + 2, 7);
                    if (can_kill_right()) goto warp;

                    // Clear selector
                    slct.selected_x = width;
                    slct.selected_y = height;
                    swap_turn();
                }

                /* Moving a checker */
                else if (can_move() && !can_kill) {
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
        if (player1.remaining == 0 || player2.remaining == 0) {
            update_board();
            game_over = 1;
            break;
        }
    }
}