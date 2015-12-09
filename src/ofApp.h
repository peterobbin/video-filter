#pragma once

#include "ofMain.h"
#include "ofxGui.h"



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
    
    void blur(float bluramt, ofVideoPlayer &vid, ofVec2f &vidPos);
    void bw(float bwShift, ofVideoPlayer &vid, ofVec2f &vidPos);
    
    ofVideoPlayer   video;
    ofVec2f         videoPos;
    ofxPanel        gui;
    
    ofImage         image;
    ofFbo           fboBlurOnePass;
    ofShader        shaderBlurX;
    ofFbo           fboBlurTwoPass;
    ofShader        shaderBlurY;
    
    ofShader        shaderBW;
    ofFbo           bwPass;
    
    ofFbo           output;
    
    float videoAspectRatio;
    bool vidDropped;
    string greeting;
    string filepath;
    
    ofParameter<bool> enableBlur;
    ofParameter<float> bluramt;
    ofParameter<bool> enableBW;
    ofParameter<float> bwShift;
    
    
};
