#ifndef COMPONENTS_H
#define COMPONENTS_H

#define height 8
#define width 8

struct player {
    /*
    is_playing: 1 if it is this player's turn
    remaining: amount of this player's checker(s) left
    is_computer: 1 if this player is a bot
    */
    int is_playing;
    int remaining;
    int is_computer;
} player1, player2;

struct cell {
    /* Variables
    owner: owner of this cell
    state:  0 => Empty
            1 => Men
            2 => King
    */
    int owner;
    int state;
    int is_hovered;
    int is_selected;
};

struct selector {
    int current_x;
    int current_y;
    int selected_x;
    int selected_y;
} slct;

int i, j;
struct cell gameboard[height][width];

void generate_components(int p2) {
    /* Generate cell */
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            gameboard[i][j].is_hovered = 0;
            gameboard[i][j].is_selected = 0;

            // Generate Player 2's Checkers
            if ((i == 0 && j % 2 == 1) || (i == 1 && j % 2 == 0)) {
                gameboard[i][j].owner = 2;
                gameboard[i][j].state = 1;
            }

            // Generate Player 1's Checkers
            else if ((i == 6 & j % 2 == 1) || (i == 7 && j % 2 == 0)) {
                gameboard[i][j].owner = 1;
                gameboard[i][j].state = 1;
            }

            // Generate empty cells
            else {
                gameboard[i][j].owner = 0;
                gameboard[i][j].state = 0;
            }
        }
    }

    /* Generate Player */
    player1.is_computer = 0;
    player1.is_playing = 0;
    player1.remaining = 0;
    player2.is_computer = p2;
    player2.is_playing = 0;
    player2.remaining = 0;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (gameboard[i][j].owner == 1) {
                player1.remaining += 1;
            }
            else if (gameboard[i][j].owner == 2) {
                player2.remaining += 1;
            }
        }
    }

    gameboard[0][0].is_hovered = 1;
    slct.current_x = 0;
    slct.current_y = 0;
    slct.selected_x = 8;
    slct.selected_y = 8;
}

void update_board() {
    system("cls");

    // Update hovered
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            gameboard[i][j].is_hovered = 0;
        }
    }
    // Update selected
    gameboard[slct.current_y][slct.current_x].is_hovered = 1;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            gameboard[i][j].is_selected = 0;
        }
    }
    gameboard[slct.selected_y][slct.selected_x].is_selected = 1;

    // Update gameboard
    printf("\n\n");
    printf("+---+---+---+---+---+---+---+---+\n");
    char line1[80], line2[80], line3[80];
    for (i = 0; i < height; i++) {
        strcpy(line1, "|");
        strcpy(line2, "|");
        strcpy(line3, "|");
        for (j = 0; j < width; j++) {
            if (gameboard[i][j].is_selected) {
                strcat(line1, "***|");
                strcat(line3, "***|");
                if (gameboard[i][j].owner == 0) {
                    strcat(line2, "* *|");
                }
                else if (gameboard[i][j].owner == 1) {
                    (gameboard[i][j].state == 1 ? strcat(line2, "*x*|") : strcat(line2, "*X*|"));
                }
                else if (gameboard[i][j].owner == 2) {
                    (gameboard[i][j].state == 1 ? strcat(line2, "*o*|") : strcat(line2, "*O*|"));
                }
            }
            else if (gameboard[i][j].is_hovered) {
                strcat(line1, "===|");
                strcat(line3, "===|");
                if (gameboard[i][j].owner == 0) {
                    strcat(line2, "= =|");
                }
                else if (gameboard[i][j].owner == 1) {
                    (gameboard[i][j].state == 1 ? strcat(line2, "=x=|") : strcat(line2, "=X=|"));
                }
                else if (gameboard[i][j].owner == 2) {
                    (gameboard[i][j].state == 1 ? strcat(line2, "=o=|") : strcat(line2, "=O=|"));
                }
            }
            else {
                strcat(line1, "   |");
                strcat(line3, "   |");
                if (gameboard[i][j].owner == 0) {
                    strcat(line2, "   |");
                }
                else if (gameboard[i][j].owner == 1) {
                    (gameboard[i][j].state == 1 ? strcat(line2, " x |") : strcat(line2, " X |"));
                }
                else if (gameboard[i][j].owner == 2) {
                    (gameboard[i][j].state == 1 ? strcat(line2, " o |") : strcat(line2, " O |"));
                }
            }
        }
        printf("%s\n%s\n%s\n", line1, line2, line3);
        printf("+---+---+---+---+---+---+---+---+\n");
    }
}

#endif