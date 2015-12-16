#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ShaderFX.hpp"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

    ShaderFX effects;
    
    
    ofVideoPlayer   video;
    ofVideoPlayer   video2;
    ofVec2f         videoPos;
    ofxPanel        gui;
    
    ofFbo           output;
    ofFbo           output2;
    

    
    float videoAspectRatio;
    bool vidDropped;
    bool twoVideos;
    string greeting;
    string filepath;
    string filepath2;
    
    ofParameter<bool> enableBlur;
    ofParameter<float> bluramt;
    ofParameter<bool> enableBW;
    ofParameter<float> bwShift;
    ofParameter<bool> enableDistort;
    ofParameter<bool> enableMix;
    ofParameter<int> mixMode;
    ofParameter<float> mixOpacity;
    
};
