#include "GameState.h"


/*
 * Set the marker on the board
 * @param x x-coordinate of the board
 * @param y y-coordinate of the board
 * @param marker the marker to set (1 or 2)
 * @return true if the marker was set, false if the marker could not be set
*/
bool GameState::setMarker(int x, int y, int marker) {
    if (x < 0 || x > 2 || y < 0 || y > 2) {
        return false;
    }
    if (board[x][y] != 0) {
        return false;
    }
    board[x][y] = marker;
    return true;
}

//--------------------------------------------------------------
int GameState::getMarker(int x, int y) {
    return board[x][y];
}

//--------------------------------------------------------------
int GameState::evaluateGame() {
    //check if win in rows
    int winningMarker = 0;
    for (int y = 0; y < 3; y++) {
        winningMarker = getMarker(0, y);

        if (winningMarker && winningMarker == getMarker(1, y) && winningMarker == getMarker(2, y)) {
            return winningMarker;
        }
    }

    //check for win in columns
    for (int x = 0; x < 3; x++) {
        winningMarker = getMarker(x, 0);

        if (winningMarker && winningMarker == getMarker(x, 1) && winningMarker == getMarker(x, 2)) {
            return winningMarker;
        }
    }


    //check for win in diagonals
    winningMarker = getMarker(0, 0);

    if (winningMarker && winningMarker == getMarker(1, 1) && winningMarker == getMarker(2, 2)) {
        return winningMarker;
    }

    winningMarker = getMarker(2, 0);

    if (winningMarker && winningMarker == getMarker(1, 1) && winningMarker == getMarker(0, 2)) {
        return winningMarker;
    }

    return 0;
}







