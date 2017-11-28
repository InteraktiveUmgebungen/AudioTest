#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// load font at size 50
	myFont.load("KeepCalm-Medium.ttf", 50, true, true);

	// for OSC connection with input
	receiver.setup(PORT);

	//Codewort in Array als einzelne buchstaben speichern
	string input = ""; //hier könnte man auch das Codewort hardcoden
	cout << "Please enter a Codeword:\n>";
	getline(cin, input);
	for (int i = 0; i < input.length(); i++) {
		codeBuchstaben.insert(input.substr(i, 1));
	}

	// for visual output
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetVerticalSync(true);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	
	myFontText.load("../../assets/fonts/KeepCalm-Medium.ttf", 16, true, true);
	myFontBuchstabe.load("../../assets/fonts/GOUDYSTO.TTF", 16, true, true);

	// Box2d
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds();
	box2d.setFPS(60.0);
}

//--------------------------------------------------------------
void ofApp::update(){
	string sentence = "";

	// read OSC messages from input
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage msg;

		if (receiver.getNextMessage(msg)) {
			sentence = msg.getArgAsString(0);
		}

		istringstream phrase(sentence);
		string word;
		//Satz in Wörter zerlegen und in set speichern
		while (getline(phrase, word, ' ')) {
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);
			if (word.length() > 1) {
				wordsAsStrings.insert(word.c_str());
			}			
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
		for (set<string>::iterator i = codeBuchstaben.begin();
			i != codeBuchstaben.end(); i++) {
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

					//--------------------------
					// for visual output
					/*
					Bubble b;
					b.setWord(*word);
					b.setPhysics(1.0, 0.5, 0.3);
					b.setup(box2d.getWorld(), 0, 0, ofRandom(20, 60)); // welchen wert für x und y? aktuell 0, 0
					b.setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
					allBubbles.push_back(b);*/
					//---------------------------

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

	// visual output
	box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// set oder so durchgehen und alle objekte zeichnen - für gehighliteten part des strings farbe wechseln

	for (int i = 0; i < allBubbles.size(); i++) {
		allBubbles[i].get()->draw();
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
	//--------------------------
	// for visual output
	shared_ptr<Bubble> b = shared_ptr<Bubble>(new Bubble);
	b.get()->setWord(Word("hello", "h"));
	b.get()->setFonts(myFontText, myFontBuchstabe);
	b.get()->setPhysics(1.0, 0.5, 0.3);
	b.get()->setup(box2d.getWorld(), x, y, ofRandom(20, 60)); // welchen wert für x und y? 
	b.get()->setVelocity(ofRandom(-30, 30), ofRandom(-30, 30));
	allBubbles.push_back(b);
	//---------------------------
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


// Additional functions
//--------------------------------------------------------------

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