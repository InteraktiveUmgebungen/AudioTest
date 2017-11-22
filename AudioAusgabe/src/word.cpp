#include "word.h"
#include "ofApp.h"
#include <iostream>

// ctor & dtor
//---------------------------------------------------------------------
	Word::Word(string s) {
		text = s;
	}

	Word::Word(string wort, string b) {
		text = wort;
		buchstabe = b;
	}

	Word::~Word() {	}

// methods
//---------------------------------------------------------------------
	
	string Word::getText() const {
		return text;
	}

	string Word::getBuchstabe() const {
		return buchstabe;
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