#include "ofApp.h"
#include "word.h"
#include <random>
#include "keyLocation.h"


using namespace msa::physics;
#define MIN_MASS				1
#define MAX_MASS				3
#define	GRAVITY					0
#define SECTOR_COUNT			1		// currently there is a bug at sector borders, so setting this to 1



//--------------------------------------------------------------
void ofApp::setup(){
	// load font at size 50
	myFont.load("KeepCalm-Medium.ttf", 50, true, true);

	windowResized(ofGetWidth(), ofGetHeight());

	// define codeWord and save characters as keys
	codeWord = "hello";
	for (int i = 0; i < codeWord.length(); i++) {
		keys.push_back(codeWord.substr(i, 1));
	}

	// for OSC connection with input
	receiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
	width = ofGetWidth();
	height = ofGetHeight();

	// update the world
	world->update();


	// read OSC messages from input
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		cout << "New message: " << msg.getArgAsString(0) << endl;
	}


	// read osc input --> TODO connect to audioInput project
	string s1 = "so";
	string s2 = "long";
	string s3 = "and";
	string s4 = "thanks";
	string s5 = "for";
	string s6 = "all";
	string s7 = "the";
	string s8 = "fish";
	string s9 = "äöüumlß"; // TODO: äöüß not displayed in graphical output, strange output on console
	string s10 = "don't";
	string s11 = "panic";
	// process strings: convert to upper-case and save in set
	strings.insert(ofToUpper(s1));
	strings.insert(ofToUpper(s2));
	strings.insert(ofToUpper(s3));
	strings.insert(ofToUpper(s4));
	strings.insert(ofToUpper(s5));
	strings.insert(ofToUpper(s6));
	strings.insert(ofToUpper(s7));
	strings.insert(ofToUpper(s8));
	strings.insert(ofToUpper(s9));
	strings.insert(ofToUpper(s10));
	strings.insert(ofToUpper(s11));

	int x = windowPadding;
	int y = windowPadding;
	// iterate through strings and convert to word objects
	for (const string &s : strings) {
		// get size of string
		int stringWidth = (int)myFont.stringWidth(s);
		int stringHeight = (int)myFont.stringHeight(s);
		int rectWidth = stringWidth + 2 * padding;
		int rectHeight = stringHeight + 2 * padding;

		// create rectangle 
		if (!((x + rectWidth) < (width - windowPadding))) {
			x = windowPadding;
			y = y + rectHeight + windowPadding;
		}
		ofRectangle background(x, y, rectWidth, rectHeight);

		// define key in string for codeWord
		vector<string> stringParts;
		for (int i = 0; i < keys.size(); i++) {
			if (s.find(keys[i]) != string::npos) {
				vector<string> split = ofSplitString(s, keys[i]);
				stringParts.push_back(split[0]);
				stringParts.push_back(keys[i]);
				stringParts.push_back(split[2]);

				cout << "key found: " << keys[i] << endl; // TODO: not working!

			}
			else {
				stringParts.push_back(s);
			}
		}

		// create word using string, rectangle and string dimensions
		Word word(s, stringParts, background, stringWidth, stringHeight);
		// add word to set with all words
		words.insert(word);

		x = x + rectWidth + windowPadding;
	}



	// print out all words on console
	/*for (const Word &word : words) {
		cout << word <<endl;
	}*/

	// schlüsselwort definieren, nötige buchstaben aus strings von input raussuchen
	// für jedes wort ein rechteck und einen string generieren --> string aufteilen in normalen und hervorgehobenen teil
	// positionen der rechtecke zufällig bestimmen
	// positionen über kollisionserkennung abstimmen --> überlappungsfrei
	// aktuell gültige rechtecke und strings in set oder so speichern
}

//--------------------------------------------------------------
void ofApp::draw(){
	// set oder so durchgehen und alle objekte zeichnen - für gehighliteten part des strings farbe wechseln

	for (const Word &word : words) {
		ofSetColor(0, 0, 0);
		ofDrawRectangle(word.getBackground());
		ofSetColor(255, 0, 0);
		myFont.drawString(word.getText(), word.getBackground().getX() + padding, word.getBackground().getY() + word.getTextHeight() + padding);
	}

	/*
	ofEnableDepthTest(); // rendering happens according to z-depth rather than draw order
	ofPushMatrix();
	ofTranslate(width / 2, 0, -width / 3);	// center scene
	ofPopMatrix();

	ofSetColor(255, 0, 0);
	ofDrawRectangle(10, 10, 100, 100);
	ofSetColor(0, 0, 255);
	ofDrawRectangle(10, 10, 100, 100);
	ofSetColor(0, 0, 0); */
	// --> über openGL zeichnen, damit collisions und gravity funktionieren
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'f':
		ofToggleFullscreen();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
	initScene();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


// Additional functions
//--------------------------------------------------------------


void ofApp::initScene() {
	width = ofGetWidth();
	height = ofGetHeight();

	// initialize our physics world
	world = World2D::create();

	world->setGravity(ofVec2f(0, GRAVITY));

	// set world dimensions, not essential, but speeds up collision
	world->setWorldSize(ofVec2f(-width / 2, -height), ofVec2f(width / 2, height));
	world->setSectorCount(SECTOR_COUNT);
	world->setDrag(0.97f);
	world->setDrag(1);		// FIXTHIS
	world->enableCollision();
}