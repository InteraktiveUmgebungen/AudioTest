#include "ofApp.h"
#include "word.h"
#include <random>
#include "MSAPhysics2D.h"
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

	// for OSC connection with input
	receiver.setup(PORT);

	//Codewort in Array als einzelne buchstaben speichern
	string input = ""; //hier könnte man auch das Codewort hardcoden
	cout << "Please enter a Codeword:\n>";
	getline(cin, input);
	for (int i = 0; i < input.length(); i++) {
		codeBuchstaben.insert(input.substr(i, 1));
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	width = ofGetWidth();
	height = ofGetHeight();

	// update the world
	world->update();
	

	string sentence = "";
	// read OSC messages from input
	ofxOscMessage msg;
	receiver.getNextMessage(msg);
	sentence = msg.getArgAsString(0);

	if (sentence.begin() != sentence.end()) {
		printf("sentence: ", sentence);
		printf("msg: ", msg.getArgAsString(0));
	}

	//cout << "New message: " << msg.getArgAsString(0) << endl;
	

	istringstream phrase(sentence); 
	string word;
	//Satz in Wörter zerlegen und in set speichern
	while (getline(phrase, word, ' ')) {
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		wordsAsStrings.insert(word.c_str());
	}

	//überprüfen ob Wörter nur Buchstaben enthalten
	string zuUeberpruefen = "null";
	for (std::set<std::string>::iterator it = wordsAsStrings.begin();
		it != wordsAsStrings.end(); it++) {
		zuUeberpruefen = *it;
		
		if (checkIfOnlyCharacters(zuUeberpruefen)) {
			correctWords.insert(zuUeberpruefen);
		}
	}
	
	set<string> gefundeneBuchstaben;
	//codeBuchstaben durchiterieren
	for(set<string>::iterator i = codeBuchstaben.begin();
		i != codeBuchstaben.end(); i++)	{
		string buchstabe = *i;
		string wort = "null";
		string wortEnthaeltBuchstaben = "null";
		//gesprochenen Wörter durchiterieren
		for (std::set<std::string>::iterator it = correctWords.begin();
			it != correctWords.end(); it++) {
			wort = *it; //j-tes Wort aus dem gesprochenem Satz
			if (wort.find_first_of(buchstabe) != std::string::npos) { //durchsucht das wort nach dem i-ten buchstaben aus dem CodeWort
				Word* word = new Word(wort, buchstabe);
				words.insert(*word);
				wortEnthaeltBuchstaben = *it;
				gefundeneBuchstaben.insert(buchstabe);
				break; //jeder Buchstabe nur einmal
			}
		}
		correctWords.erase(wortEnthaeltBuchstaben); //wort aus der Liste entfernen -> nicht mehrere Buchstaben pro Wort
		
	}
	
	//die buchstaben die gefunden wurden werden aus der codewortbuchstaben liste gelöscht
	for (set<string>::iterator b = gefundeneBuchstaben.begin();
			b != gefundeneBuchstaben.end(); b++) {
		string gefunden = *b;
		codeBuchstaben.erase(gefunden);
	}


	//wörter liste leeren und von vorne anfangen mit neuen Wörtern
	wordsAsStrings.clear();
	correctWords.clear();
}



//--------------------------------------------------------------
void ofApp::draw(){
	// set oder so durchgehen und alle objekte zeichnen - für gehighliteten part des strings farbe wechseln
	int i = 20;
	for (const Word &word : words) {
		ofSetColor(0, 0, 0);
		//ofDrawRectangle(word.getBackground());
		ofSetColor(255, 0, 0);
		string buchstabe = "  " + word.getBuchstabe();
		myFont.drawString(word.getText() + buchstabe, 100, 100 + i);
		i = i + 50;
	}
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


//überprüft die gesprochenen Wörter auf Buchstaben (sonderzeichen werden aussortiert)
bool ofApp::checkIfOnlyCharacters(string wortZumUberpruefen)
{
	bool isOnlyCharacters = true;
	for (int i = 0; i < wortZumUberpruefen.size(); i++) {
		if (!isalpha(wortZumUberpruefen[i]) && !isspace(wortZumUberpruefen[i])) {
			isOnlyCharacters = false;
			break;
		}
	}
	return isOnlyCharacters;
}


