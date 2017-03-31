#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{	

	ofHideCursor();
	
	//load mask images
	dir.open(ofToDataPath("masks", true));

	dir.listDir();
	ofImage temp;

	 for(int i = 0; i < dir.size(); i++){
	    ofLogNotice("loading mask :"  + dir.getPath(i));
		temp.load(dir.getPath(i));
		masks.push_back(temp);	
	}


	//ofSetLogLevel(OF_LOG_VERBOSE);

	// string videoPath = ofToDataPath("pieroomfar.mov", true);

	// //Somewhat like ofFboSettings we may have a lot of options so this is the current model
	// ofxOMXPlayerSettings settings;
	// settings.videoPath = videoPath;
	// settings.useHDMIForAudio = true;	//default true
	// settings.enableTexture = true;		//default true
	// settings.enableLooping = false;		//default true
	// settings.enableAudio = false;		//default true, save resources by disabling
	// //settings.doFlipTexture = true;		//default false
	// //so either pass in the settings
	// omxPlayer.setup(settings);
	// omxPlayer.setPaused(true);


	gpio17.setup("17");
    gpio17.export_gpio();
    gpio17.setdir_gpio("in");

	//or live with the defaults
	//omxPlayer.loadMovie(videoPath);
    

    dir.open(ofToDataPath("",true));

    dir.listDir();

    for(int i = 0; i < dir.size(); i++){
	    ofLogNotice(dir.getPath(i));
	}
	
	dirIndex = 0;
	
	loadNextMovie();


}	


void ofApp::loadNextMovie(){


	string videoPath = dir.getPath(dirIndex);

	//Somewhat like ofFboSettings we may have a lot of options so this is the current model
	ofxOMXPlayerSettings settings;
	settings.videoPath = videoPath;
	settings.useHDMIForAudio = true;	//default true
	settings.enableTexture = true;		//default true
	settings.enableLooping = false;		//default true
	settings.enableAudio = false;		//default true, save resources by disabling
	//settings.doFlipTexture = true;		//default false
	//so either pass in the settings
	omxPlayer.setup(settings);
	omxPlayer.setPaused(true);
	// omxPlayer.seekToTimeInSeconds(0);
	// omxPlayer.setPaused(true);
	ofLog() << "loading video :"<< videoPath << endl;
	ofLog() << "dirIndex  :"  << dirIndex << endl;
	
	dirIndex ++;

	if(dirIndex >= dir.size()){
		dirIndex = 0;
	}

}

//--------------------------------------------------------------
void ofApp::update()
{
	gpio17.getval_gpio(state_button);
    

    //Play Loaded Movie
	if(stoi(state_button, nullptr,0) == 1 && omxPlayer.isPaused()){
		
		ofLog()<<state_button;
		ofLog() << "starting " << endl;
		
		omxPlayer.setPaused(false);
		

	//Movie is done, no-one is there, load next movie
	}else if(	stoi(state_button, nullptr,0) == 0 &&
				omxPlayer.getCurrentFrame() >= omxPlayer.getTotalNumFrames()-2 && 
				!omxPlayer.isPaused() ){
		
		loadNextMovie();
		

		maskIndex ++;
		
		if(maskIndex >= masks.size()){
			maskIndex = 0;
		}

		ofLog()<<state_button;
		ofLog() << "restarting " << endl;
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	if(!omxPlayer.isTextureEnabled())
	{
		return;
	}

	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
	//draw a smaller version in the lower right
	int scaledHeight	= omxPlayer.getHeight()/4;
	int scaledWidth		= omxPlayer.getWidth()/4;
	omxPlayer.draw(ofGetWidth()-scaledWidth, ofGetHeight()-scaledHeight, scaledWidth, scaledHeight);

	masks[maskIndex].draw(0,0);

	ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);


}

void ofApp::keyPressed(int key){

    if (key == OF_KEY_UP){
    
    	maskIndex ++;
    	if(maskIndex >= masks.size()){
    		maskIndex = 0;
    	}

    } else if (key == OF_KEY_DOWN){
    	
    	maskIndex --;   
    	if(maskIndex <= 0){
    		maskIndex = masks.size();
    	}
    
    }

}


void ofApp::exit(){

	 gpio17.unexport_gpio();

}
