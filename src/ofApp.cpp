#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	//ofSetLogLevel(OF_LOG_VERBOSE);

	string videoPath = ofToDataPath("pieroomNear.mov", true);

	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio = true;	//default true
	settings.enableTexture = true;		//default true
	settings.enableLooping = true;		//default true
	settings.enableAudio = true;		//default true, save resources by disabling
	//settings.doFlipTexture = true;		//default false
	//so either pass in the settings
	omxPlayer.setup(settings);
	omxPlayer.setPaused(true);

	 gpio17.setup("17");
         gpio17.export_gpio();
         gpio17.setdir_gpio("in");

	//or live with the defaults
	//omxPlayer.loadMovie(videoPath);

}



//--------------------------------------------------------------
void ofApp::update()
{
	gpio17.getval_gpio(state_button);
        ofLog()<<state_button;
	if(stoi(state_button, nullptr,0) == 1){
		omxPlayer.setPaused(false);
	}else{
		omxPlayer.setPaused(true);
	}
                        //usleep(50000);
}


//--------------------------------------------------------------
void ofApp::draw(){
	if(!omxPlayer.isTextureEnabled())
	{
		return;
	}

	omxPlayer.draw(0, 0, 800,800);//ofGetWidth(), ofGetHeight());
	//draw a smaller version in the lower right
	int scaledHeight	= omxPlayer.getHeight()/4;
	int scaledWidth		= omxPlayer.getWidth()/4;
	omxPlayer.draw(ofGetWidth()-scaledWidth, ofGetHeight()-scaledHeight, scaledWidth, scaledHeight);

	ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
}


void ofApp::exit(){
	 gpio17.unexport_gpio();
}
