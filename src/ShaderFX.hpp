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
    
    void rawOutput(ofVideoPlayer &vid, ofFbo &output);
    void rawOutput(ofVideoGrabber &vidGrabber, ofFbo &output);
    void blur(float bluramt, ofFbo &output);
    void bw(float bwShift, ofFbo &output);
    void distortion(ofFbo &output);
    void faceWarp(ofFbo &output , bool useCam, ofVec2f &nosePos);
    void mixVid(ofVideoPlayer &vid2, ofFbo &output, ofFbo &output2, int mode, float opacity, bool swap);
    
    ofTexture texture;
    
    ofShader        shaderBlurX;
    ofShader        shaderBlurY;
    ofShader        shaderBW;
    ofShader        shaderDistortion;
    ofShader        shaderMix;
    ofShader        shaderWarp;
    
    ofFbo           processOutput;

};