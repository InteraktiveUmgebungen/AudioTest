#include "keyLocation.h"
#include "ofApp.h"


keyLocation::keyLocation() {

}
keyLocation::keyLocation(string k) {
	key = k;
}
keyLocation::keyLocation(string k, Word w) {
	key = k;
	word = w;
}

keyLocation::~keyLocation() { }
