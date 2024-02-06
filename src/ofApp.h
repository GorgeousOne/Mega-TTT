#pragma once

#include "ofMain.h"
#include "GameState.h"
#include <tuple>
#include <string>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void drawBoard(ofPoint center, float size);
	std::tuple<int, int> getClickedTile(int x, int y);

	GameState gameState{};
	int pressedX = -1;
	int pressedY = -1;

	float boardSize;
	ofPoint boardCenter;

	bool isPlayer1Turn = true;
	std::string debugInfo = "";
};
