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
	float t = ofGetElapsedTimef();
	ofBackground(127+50*sin(t*0.01),127+30*cos(t*0.04),127-40*sin(t*0.03));
	ofSetColor(255);
	ofSetLineWidth(1);

	float tileSize = size / 3;

	ofPolyline line1;
	ofPolyline line2;
	ofPolyline line3;
	ofPolyline line4;
	//draw lines of the tiles

	ofPoint pt;
	ofTranslate(center);

	//top to bottom lines
	pt.set(tileSize, -size);
	line1.addVertex(pt);
	pt.set(tileSize, size);
	line1.addVertex(pt);

	pt.set(-tileSize, -size);
	line2.addVertex(pt);
	pt.set(-tileSize, size);
	line2.addVertex(pt);

	//left to right lines
	pt.set(-size, tileSize);
	line3.addVertex(pt);
	pt.set(size, tileSize);
	line3.addVertex(pt);

	pt.set(-size, -tileSize);
	line4.addVertex(pt);
	pt.set(size, -tileSize);
	line4.addVertex(pt);

	line1.draw();
	line2.draw();
	line3.draw();
	line4.draw();


	//draw the game markers
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			int marker = gameState.getMarker(x, y);
			float dx = (x - 1) * tileSize * 2;
			float dy = (y - 1) * tileSize * 2;

			switch (marker) {
				case 1:
					ofSetColor(0,255,0);
					ofSetCircleResolution(20);
					ofDrawCircle(dx, dy, tileSize);
					break;
				case 2:
					ofSetColor(0,0,255);
					ofSetCircleResolution(4);
					ofDrawCircle(dx, dy, tileSize);
					break;
				default:
					break;
			}

		}
	}
	ofTranslate(-center);
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
