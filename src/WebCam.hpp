//
//  WebCam.hpp
//  video-filter
//
//  Created by peterobbin on 12/16/15.
//
//

#pragma once
#include "ofMain.h"


class WebCam{
public:
    void setup(int _width, int _height);
    void init();
    void update();
    void draw(ofVec2f _pos);
    void close();
    
    
    ofVideoGrabber vidGrabber;
    int camWidth;
    int camHeight;
    bool initComplete;
};