#include "bubble.h"

void Bubble::draw() {

	float radius = 120; // change to constant or variable in config file
	ofPushMatrix();
		ofTranslate(getPosition());
		ofRotateZ(getRotation());
		ofSetColor(0, 0, 255);
		ofFill();
		ofCircle(0, 0, radius);

		ofPushMatrix();
			ofSetColor(255, 255, 255);
			myFontText.drawString(word.getText(), 0, 0);
			myFontBuchstabe.drawString(word.getBuchstabe(), myFontText.stringWidth(word.getText()), 0);

			// TODO: Wort zentrieren
			// Radius an Textlänge anpassen mit myFontText.stringWidth() von allen Textkomponenten + Padding

		ofPopMatrix();

	ofPopMatrix();

}

Word Bubble::getWord() 
{
	return word;
}

void Bubble::setWord(Word w)
{
	word = w;
}

void Bubble::setFonts(ofTrueTypeFont text, ofTrueTypeFont buchstabe) 
{
	myFontText = text;
	myFontBuchstabe = buchstabe;
}