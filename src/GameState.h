#pragma once
// #include "ofMain.h"

class GameState {
private:
    int board[3][3];

public:
    GameState() {
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                board[x][y] = 0;
            }
        }
    }
    void setMarker(int x, int y, int marker);
    int getMarker(int x, int y);
    int evaluateGame();
};
