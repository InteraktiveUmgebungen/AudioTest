#pragma once
#include "ofMain.h"
#include "word.h"

class keyLocation
{
public:
	keyLocation();
	keyLocation(string k);
	keyLocation(string k, Word w);
	~keyLocation();

	string key;
	Word word;
};

