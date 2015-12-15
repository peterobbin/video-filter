//
//  shaderFX.hpp
//  video-filter
//
//  Created by peterobbin on 12/15/15.
//
//

#pragma once
#include "ofMain.h"

class ShaderFX{
public:
    void setup();
    void update();
    void draw();
    
    void rawOutput(ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output);
    void blur(float bluramt, ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output);
    void bw(float bwShift, ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output);

    
    ofShader        shaderBlurX;
    ofShader        shaderBlurY;
    ofShader        shaderBW;
    
    ofFbo           processOutput;

};