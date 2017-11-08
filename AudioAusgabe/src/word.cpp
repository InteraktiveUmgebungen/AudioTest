#include "word.h"
#include "ofApp.h"
#include <iostream>

// ctor & dtor
//---------------------------------------------------------------------
	Word::Word(string s) {
		text = s;
	}

	Word::Word(string s, ofRectangle rect) {
		text = s;
		background = rect;
	}

	// preferred ctor
	Word::Word(string s, vector<string> sp, ofRectangle rect, int width, int height) {
		text = s;
		stringParts = sp;
		background = rect;
		textWidth = width;
		textHeight = height;
	}

	Word::~Word() {	}

// methods
//---------------------------------------------------------------------
	ofRectangle Word::getBackground() const {
		return background;
	}
	void Word::setBackground(ofRectangle rect) {
		background = rect;
	}

	string Word::getText() const {
		return text;
	}

	vector<string> Word::getStringParts() const {
		return stringParts;
	}

	int Word::getTextWidth() {
		return textWidth;
	}

	void Word::setTextWidth(int w) {
		textWidth = w;
	}

	int Word::getTextHeight() const {
		return textHeight;
	}
	void Word::setTextHeight(int h) {
		textHeight = h;
	}


// overloaded operators
//---------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& out, const Word &word) {
		out << word.text;
		return out;
	}

	bool operator==(const Word &word1, const Word &word2) {
		return (word1.text == word2.text);
	}
	bool operator<(const Word &word1, const Word &word2) {
		return (word1.text < word2.text);
	}
	bool operator>(const Word &word1, const Word &word2) {
		return (word1.text > word2.text);
	}