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
    
    void rawOutput(ofVideoPlayer &vid, ofFbo &output);
    void blur(float bluramt, ofFbo &output);
    void bw(float bwShift, ofFbo &output);

    
    ofShader        shaderBlurX;
    ofShader        shaderBlurY;
    ofShader        shaderBW;
    
    ofFbo           processOutput;

};