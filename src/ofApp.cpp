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

			switch (marker) {
				case 1:
					//draw X
					break;
				case 2:
					//draw O
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
	debugInfo = "Tile clicked: " + std::to_string(tileX) + ", " + std::to_string(tileY);
	ofBackground(255,0,0);
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
	ofBackground(0);
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
