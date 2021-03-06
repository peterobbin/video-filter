//
//  shaderFX.cpp
//  video-filter
//
//  Created by peterobbin on 12/15/15.
//
//

#include "ShaderFX.hpp"

void ShaderFX::setup(){
    
    shaderBlurX.load("blurx.vert","blurx.frag");
    shaderBlurY.load("blury.vert","blury.frag");
    shaderBW.load("bw.vert", "bw.frag");
    shaderDistortion.load("distort.vert", "distort.frag");
    shaderMix.load("mix.vert", "mix.frag");
    shaderWarp.load("warp.vert", "warp.frag");
    //ofDisableArbTex();

}

void ShaderFX::update(){
    // uncomment for live shader update
    shaderBlurX.load("blurx.vert","blurx.frag");
    shaderBlurY.load("blury.vert","blury.frag");
    shaderBW.load("bw.vert", "bw.frag");
    shaderMix.load("mix.vert", "mix.frag");
    shaderDistortion.load("distort.vert", "distort.frag");
    shaderWarp.load("warp.vert", "warp.frag");
}


void ShaderFX::blur(float bluramt, ofFbo &output){
    
    ofFbo fboBlurOnePass;
    ofFbo fboBlurTwoPass;
    
    fboBlurOnePass.allocate(output.getWidth(), output.getHeight());
    fboBlurTwoPass.allocate(output.getWidth(), output.getHeight());
    
    float blur = bluramt;

    // horizonal pass
    //----------------------------------------------------------
    fboBlurOnePass.begin();
    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);
    output.draw(0, 0);
    shaderBlurX.end();
    fboBlurOnePass.end();
        
    // vertical pass
    //----------------------------------------------------------
    fboBlurTwoPass.begin();
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);
    fboBlurOnePass.draw(0, 0);
    shaderBlurY.end();
    fboBlurTwoPass.end();
        
    //----------------------------------------------------------
        
    output = fboBlurTwoPass;
}


void ShaderFX::bw(float bwShift, ofFbo &output){
    ofFbo bwFX;
    bwFX.allocate(output.getWidth(), output.getHeight());
    bwFX.begin();
    shaderBW.begin();
    shaderBW.setUniform1f("u_bwshift", bwShift);
    shaderBW.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shaderBW.setUniform2f("u_tex0Resolution", output.getWidth(), output.getHeight());
    output.draw(0, 0);
    shaderBW.end();
    bwFX.end();
    output = bwFX;

}

void ShaderFX::distortion(ofFbo &output){
    ofFbo distortFX;
    distortFX.allocate(output.getWidth(), output.getHeight());
    distortFX.begin();
    
    shaderDistortion.begin();
    //shaderDistortion.setUniformTexture("tex0", output.getTexture(), 0);
    shaderDistortion.setUniform1f("u_time", ofGetElapsedTimef());
    shaderDistortion.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
    shaderDistortion.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shaderDistortion.setUniform2f("u_tex0Resolution", output.getWidth(), output.getHeight());
    output.draw(0, 0);
    
    shaderDistortion.end();
    distortFX.end();
    //cout<<ofGetElapsedTimef()<<endl;
    
    output = distortFX;

}


void ShaderFX::faceWarp(ofFbo &output, bool useCam, ofVec2f &nosePos, ofVec2f &vidPos, float warpAmt){
    ofFbo warpFX;
    warpFX.allocate(output.getWidth(), output.getHeight());
    warpFX.begin();
    
    
    ofVec2f mousePos;
    
    if (useCam){
        mousePos = nosePos;
    }else{
       // mousePos = ofVec2f(ofGetMouseX(), ofGetMouseY());
        mousePos = ofVec2f(ofGetMouseX() - vidPos.x, ofGetMouseY());
    }
    
    shaderWarp.begin();
    shaderWarp.setUniform1f("u_time", ofGetElapsedTimef());
    shaderWarp.setUniform1f("u_amount", warpAmt);
    shaderWarp.setUniform2f("u_mouse", mousePos.x, mousePos.y);
    shaderWarp.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shaderWarp.setUniform2f("u_tex0Resolution", output.getWidth(), output.getHeight());
    output.draw(0, 0);
    
    shaderWarp.end();
    warpFX.end();
    //cout<<ofGetElapsedTimef()<<endl;
    
    output = warpFX;
    
}

void ShaderFX::mixVid(ofVideoPlayer &vid2, ofFbo &output, ofFbo &output2, int mode, float opacity, bool swap){
    if (vid2.isFrameNew()) {
        
        
        int swapMode = 0;
        
        if (swap) {
            swapMode = 0;
        }else{
            swapMode = 1;
        }
        
        output2.begin();
        vid2.draw(0, 0);
        output2.end();
        
        ofFbo mixFX;
        ofFbo mixFX2;
        mixFX.allocate(output.getWidth(), output.getHeight());
        mixFX2.allocate(output.getWidth(), output.getHeight());
        
        mixFX.begin();
        shaderMix.begin();
        shaderMix.setUniformTexture("u_tex0", output.getTexture(), 0);
        shaderMix.setUniformTexture("u_tex1", vid2.getTexture(), 1);
        shaderMix.setUniform1f("u_opacity", opacity);
        shaderMix.setUniform1i("u_mode", mode);
        shaderMix.setUniform1i("u_swap", swapMode);
        shaderMix.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        shaderMix.setUniform2f("u_tex0Resolution", output.getWidth(), output.getHeight());
        output.draw(0,0);
        shaderMix.end();
        mixFX.end();
        output = mixFX;
        
    }
    
}

void ShaderFX::rawOutput(ofVideoPlayer &vid, ofFbo &output){
    if (vid.isFrameNew()) {
        output.begin();
        vid.draw(0,0);
        output.end();
        processOutput = output;
    }
    
}

void ShaderFX::rawOutput(ofVideoGrabber &vidGrabber, ofFbo &output){
    if (vidGrabber.isFrameNew()) {
        output.begin();
        vidGrabber.draw(0,0);
        output.end();
        processOutput = output;
    }
    
}
