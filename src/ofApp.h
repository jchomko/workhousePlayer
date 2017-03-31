#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{

	public:
		GPIO	gpio17;
		string state_button;

		void setup();
		void update();
		void draw();
		void exit();
		void loadNextMovie();
		void keyPressed(int key);

		ofxOMXPlayer omxPlayer;

		ofDirectory dir;
		int dirIndex;
		
		vector<ofImage> masks;
		int maskIndex;


};

