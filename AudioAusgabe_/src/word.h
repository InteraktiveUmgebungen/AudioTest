#pragma once

#include "ofMain.h"

class Word {
	private:
		string text;
		string buchstabe;

	public:
		Word(string s = "");
		Word(string wort, string b);
		~Word();

		string getText() const;
		string getBuchstabe() const;

		friend std::ostream& operator<<(std::ostream& out, const Word &word);
		friend bool operator==(const Word &word1, const Word &word2);
		friend bool operator<(const Word &word1, const Word &word2);
		friend bool operator>(const Word &word1, const Word &word2);

		
};