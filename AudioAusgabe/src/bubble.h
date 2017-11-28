#pragma once
#include "ofxBox2dCircle.h"
#include "word.h"

class Bubble :
	public ofxBox2dCircle
{
public:
	Word word;

	void draw();
	void setWord(Word w);
	Word getWord();
	void setFonts(ofTrueTypeFont text, ofTrueTypeFont buchstabe);


	ofTrueTypeFont myFontText;
	ofTrueTypeFont myFontBuchstabe;
};

