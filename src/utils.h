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
    /* return 1 if a selected checker can move */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty cond.
    && ((slct.selected_x + 1 == slct.current_x && slct.selected_y + foward() == slct.current_y) // foward-right is empty cell cond.
    || (slct.selected_x - 1 == slct.current_x && slct.selected_y + foward() == slct.current_y))) { // foward-left is empty cell cond.
        return 1;
    }
    return 0;
}

int can_kill_left() {
    /* return 1 if a selected checker can kill on the left */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty
        && slct.selected_x - 2 == slct.current_x && slct.selected_y + (2 * foward()) == slct.current_y
        && gameboard[slct.selected_y + foward()][slct.selected_x - 1].owner == opponent()) {
        return 1;
    }
    return 0;
}


int can_kill_right() {
    /* return 1 if a selected checker can kill on the right */
    if (gameboard[slct.current_y][slct.current_x].owner == 0    // current cell is empty
        && slct.selected_x + 2 == slct.current_x && slct.selected_y + (2 * foward()) == slct.current_y
        && gameboard[slct.selected_y + foward()][slct.selected_x + 1].owner == opponent()) {
        return 1;
    }
    return 0;
}

#endif