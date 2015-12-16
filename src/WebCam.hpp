//
//  WebCam.hpp
//  video-filter
//
//  Created by peterobbin on 12/16/15.
//
//

#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"


class WebCam{
public:
    void setup(int _width, int _height);
    void init();
    void update();
    void draw(ofVec2f _pos);
    void close();
    
    
    ofVideoGrabber vidGrabber;
    ofxFaceTracker tracker;
    int camWidth;
    int camHeight;
    bool initComplete;
    
    ofVec2f nosePos;
};