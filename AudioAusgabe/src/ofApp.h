#pragma once

#include "ofMain.h"
#include "word.h"
#include "MSAPhysics2D.h"
#include "keyLocation.h"
#include "ofxOsc.h"

using namespace msa::physics;

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
		

		ofTrueTypeFont myFont;
		set <Word> words;
		set <string> strings;
		int padding = 20;
		int windowPadding = 40;

		void initScene();

		int width;
		int height;
		World2D_ptr world;

		string codeWord;
		vector<string> keys;
		vector<keyLocation> keysFound;

		// for OSC connection to input
		ofxOscReceiver receiver;

};
