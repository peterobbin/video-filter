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
    //ofDisableArbTex();

}

void ShaderFX::update(){
    // uncomment for live shader update
    shaderBlurX.load("blurx.vert","blurx.frag");
    shaderBlurY.load("blury.vert","blury.frag");
    shaderBW.load("bw.vert", "bw.frag");
    
    shaderDistortion.load("distort.vert", "distort.frag");
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
        output.begin();
        shaderBW.begin();
        shaderBW.setUniform1f("u_bwshift", bwShift);
        shaderBW.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        shaderBW.setUniform2f("u_tex0Resolution", output.getWidth(), output.getHeight());
        output.draw(0, 0);
        shaderBW.end();
        output.end();

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

void ShaderFX::rawOutput(ofVideoPlayer &vid, ofFbo &output){
    if (vid.isFrameNew()) {
        output.begin();
        vid.draw(0,0);
        output.end();
        processOutput = output;
    }
    
}
