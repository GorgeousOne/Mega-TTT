#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//prevent screen tearing
	ofSetVerticalSync(true);
	//set background color to light gray
	ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofNoFill();
	float width	= ofGetWidth();
	float height = ofGetHeight();

	boardCenter = ofPoint(width/2, height/2);
	float scale = 0.8;
	boardSize = 0.5 * glm::min(width, height) * scale;

	drawBoard(boardCenter, boardSize);
	ofDrawBitmapStringHighlight(debugInfo, glm::vec3(10, 20, 0));
}


/*
 * Displays the game board with the current state of the game
 * @param center the center of the board
 * @param size half size of 3x3 board
 */
void ofApp::drawBoard(ofPoint center, float size) {
	funIndex = 0;
	float t = ofGetElapsedTimef();

	ofBackground(127+50*sin(t*0.01),127+30*cos(t*0.04),127-40*sin(t*0.03));
	ofSetColor(255);
	ofSetLineWidth(5);

	float tileSize = size / 3;

	ofTranslate(center);
	//top to bottom lines

	ofPoint fun1 = fun();
	ofPoint fun2 = fun();
	ofPoint fun3 = fun();
	ofPoint fun4 = fun();
	ofPoint fun5 = fun();
	ofPoint fun6 = fun();
	ofPoint fun7 = fun();
	ofPoint fun8 = fun();

	
	ofDrawLine(-size + fun1.x, -tileSize + fun1.y, size + fun2.x, -tileSize + fun2.y);
	ofDrawLine(-size + fun3.x, tileSize + fun3.y, size + fun4.x, tileSize + fun4.y);

	ofDrawLine(-tileSize + fun5.x, -size + fun5.y, -tileSize + fun6.x, size + fun6.y);
	ofDrawLine(tileSize + fun7.x, -size + fun7.y, tileSize + fun8.x, size + fun8.y);
	

	//draw the game markers
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			int marker = gameState.getMarker(x, y);
			fun1 = fun();
			
			float dx = (x - 1) * tileSize * 2 + fun1.x;
			float dy = (y - 1) * tileSize * 2 + fun1.y;

			switch (marker) {
				case 1:
					ofSetColor(0,255,0);
					ofSetCircleResolution(50);
					ofDrawCircle(dx, dy, tileSize * 0.7);
					break;
				case 2:
					ofSetColor(0,0,255);
					// ofSetCircleResolution(4);
					ofDrawRectangle(dx - tileSize * 0.6, dy - tileSize * 0.6, tileSize * 1.2, tileSize * 1.2);
					// ofDrawCircle(dx, dy, tileSize * 0.8);
					break;
				default:
					break;
			}

		}
	}
	ofTranslate(-center);
}


ofPoint ofApp::fun() {
	float amplitude = 2;
	float frequency = 10;

	if (funAngles.size() <= funIndex) {
		funAngles.push_back(ofRandom(0, 2 * PI));
		funSeeds.push_back(ofRandom(0, 100));
	}
	float t = ofGetElapsedTimef();
	float seed = funSeeds[funIndex];
	funAngles[funIndex] += ofSignedNoise(0.1 * t + seed) * 0.1;

	float motion = sin(frequency * t + seed * 0.1) * amplitude;
	float angle = funAngles[funIndex];
	float x = motion * cos(angle);
	float y = motion * sin(angle);

	funIndex++;
	return ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	auto [tileX, tileY] = getClickedTile(x, y);
	bool wasMoveSuccesful = gameState.setMarker(tileX,tileY,playerTurn);

	if (wasMoveSuccesful) {
		if (gameState.evaluateGame() != 0) {
			debugInfo = "Player " + std::to_string(playerTurn) + " wins!";
		}
		playerTurn = (playerTurn == 1) ? 2 : 1;
	}
}

/**
 * Returns the tile that was clicked
 * @param x the x coordinate of the click
 * @param y the y coordinate of the click
 * @return a tuple with the x and y coordinates of the clicked tile
 * 	   or (-1, -1) if the click was outside the board
 */
std::tuple<int, int> ofApp::getClickedTile(int x, int y) {

	ofPoint relPoint = ofPoint(x, y) - boardCenter + boardSize;
	relPoint /= 2 * boardSize;

	int tileX = glm::floor(relPoint.x * 3);
	int tileY = glm::floor(relPoint.y * 3);

	if (tileX < 0 || tileX > 2 || tileY < 0 || tileY > 2) {
		return std::make_tuple(-1, -1);
	}
	return std::make_tuple(tileX, tileY);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
