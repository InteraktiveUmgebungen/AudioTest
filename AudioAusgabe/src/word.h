#pragma once

#include "ofMain.h"

class Word {
	private:
		ofRectangle background;
		string text;
		vector<string> stringParts;
		int textWidth;
		int textHeight;
		string key;

	public:
		Word(string s = "");
		Word(string s, ofRectangle rect);
		Word(string s, vector<string> stringParts, ofRectangle rect, int width, int height);
		~Word();

		ofRectangle getBackground() const;
		void setBackground(ofRectangle rect);
		string getText() const;
		vector<string> getStringParts() const;

		int getTextWidth();
		void setTextWidth(int w);
		int getTextHeight() const;
		void setTextHeight(int h);

		friend std::ostream& operator<<(std::ostream& out, const Word &word);
		friend bool operator==(const Word &word1, const Word &word2);
		friend bool operator<(const Word &word1, const Word &word2);
		friend bool operator>(const Word &word1, const Word &word2);
};