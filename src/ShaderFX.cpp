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
    

}


void ShaderFX::update(){
    
}


void ShaderFX::draw(){
    
}


void ShaderFX::blur(float bluramt, ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output){
    
    //image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    if (vid.isFrameNew()) {
        
        ofFbo           fboBlurOnePass;
        ofFbo           fboBlurTwoPass;
        
        fboBlurOnePass.allocate(vid.getWidth(), vid.getHeight());
        fboBlurTwoPass.allocate(vid.getWidth(), vid.getHeight());
        
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
}


void ShaderFX::bw(float bwShift, ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output){
    if (vid.isFrameNew()) {

        output.begin();
        shaderBW.begin();
        shaderBW.setUniform1f("u_bwshift", bwShift);
        shaderBW.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        shaderBW.setUniform2f("u_tex0Resolution", vid.getWidth(), vid.getHeight());
        output.draw(0, 0);
        shaderBW.end();
        output.end();
        
        
    }
}

void ShaderFX::rawOutput(ofVideoPlayer &vid, ofVec2f &vidPos, ofFbo &output){
    if (vid.isFrameNew()) {
        output.allocate(vid.getWidth(), vid.getHeight());
        output.begin();
        vid.draw(0,0);
        output.end();
        processOutput = output;
    }
    
}
