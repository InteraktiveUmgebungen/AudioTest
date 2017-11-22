#pragma once
#include "C:\Users\Denise\Documents\ofx-workspace\of_v0.9.8_vs_release\addons\ofxBox2d\src\ofxBox2dCircle.h"
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

