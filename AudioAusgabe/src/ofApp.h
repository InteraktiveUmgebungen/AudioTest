#pragma once
#include "ofMain.h"
#include "word.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"
#include "bubble.h"

// listen on port 55555
#define PORT 55555

class ofApp : public ofBaseApp{

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
		
		// for text processing
		set <Word> words;
		std::set<std::string> wordsAsStrings;
		std::set<std::string> correctWords;
		bool checkIfOnlyCharacters(string wort);

		set<string> codeWord;
		set<string> codeBuchstaben;

		// for visual output
		ofTrueTypeFont myFont;
		ofxBox2d box2d;
		vector <shared_ptr<Bubble>> allBubbles;
		ofTrueTypeFont myFontText;
		ofTrueTypeFont myFontBuchstabe;

		// for OSC connection to input
		ofxOscReceiver receiver;
};
