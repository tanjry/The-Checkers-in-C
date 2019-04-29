#ifndef UTILS_H
#define UTILS_H

int max(int a, int b) {
    return (a > b ? a : b);
}

int min(int a, int b) {
    return (a < b ? a : b);
}

int opponent() {
    /*
    return 2 if player 1 is playing
    return 1 if player 2 is playing
    */
    return (playing == 1 ? 2 : 1);
}

void swap_turn() {
    /* Swap to opponent's turn */
    playing = opponent();
}

int foward() {
    /* return a foward direction for a playing player
    return -1 if playing 1 is playing (player 1 will move upward)
    return 1 if playing 2 is playing (player 2 will move downward)
     */
    return (playing == 1 ? -1 : 1);
}

int can_move() {
    /* return 1 if a selected checker can move (men) */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty cond.
    && ((slct.selected_x + 1 == slct.current_x && slct.selected_y + foward() == slct.current_y) // foward-right is empty cell cond.
    || (slct.selected_x - 1 == slct.current_x && slct.selected_y + foward() == slct.current_y))) { // foward-left is empty cell cond.
        return 1;
    }
    return 0;
}

int can_kill_left() {
    /* return 1 if a selected checker can kill on the left (men) */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty
        && slct.selected_x - 2 == slct.current_x && slct.selected_y + (2 * foward()) == slct.current_y
        && gameboard[slct.selected_y + foward()][slct.selected_x - 1].owner == opponent()) {
        return 1;
    }
    return 0;
}

int can_kill_right() {
    /* return 1 if a selected checker can kill on the right (men) */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty
        && slct.selected_x + 2 == slct.current_x && slct.selected_y + (2 * foward()) == slct.current_y
        && gameboard[slct.selected_y + foward()][slct.selected_x + 1].owner == opponent()) {
        return 1;
    }
    return 0;
}

int king_move() {
    /* return 1 if a selected checker can move (king) */
    int x1, x2, y1, y2;
    int dif_x = abs(slct.current_x - slct.selected_x);
    int dif_y = abs(slct.current_y - slct.selected_y);
    if (dif_x != dif_y) return 0;   // can't walk straight !
    x1 = slct.current_x, y1 = slct.current_y;
    x2 = slct.selected_x, y2 = slct.selected_y;
    while (x1 != x2) {
        if (gameboard[y1][x1].owner != 0) {
            return 0;
        }
        (x1 > x2 ? x1-- : x1++);
        (y1 > y2 ? y1-- : y1++);
    }
    return 1;
}

int king_kill() {
    /* return 1 if a selected checker can kill (king) */
    int x1, x2, y1, y2;
    int dif_x = abs(slct.current_x - slct.selected_x);
    int dif_y = abs(slct.current_y - slct.selected_y);
    if (dif_x != dif_y) return 0;   // can't walk straight
    x1 = slct.selected_x, y1 = slct.selected_y;
    x2 = slct.current_x, y2 = slct.current_y;
    while (x1 != x2) {
        (x1 > x2 ? x1-- : x1++);
        (y1 > y2 ? y1-- : y1++);
        if (gameboard[y1][x1].owner == 0) {
            continue;
        }
        else if (gameboard[y1][x1].owner == opponent() && x1 + (x1 > x2 ? -1 : 1) == x2
                && y1 + (y1 > y2 ? -1 : 1) && gameboard[y2][x2].owner == 0) {
            // Kill enemy
            gameboard[y1][x1].owner = 0;
            gameboard[y1][x1].state = 0;
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

#endif