#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    shaderBlurX.load("blurx.vert","blurx.frag");
    shaderBlurY.load("blury.vert","blury.frag");
    shaderBW.load("bw.vert", "bw.frag");
    
    
    gui.setup();
    gui.add(enableBlur.set("enable Blur",false));
    gui.add(bluramt.set("blur amount", 0.0, 0.0, 5.0));
    gui.add(enableBW.set("enable B/W",false));
    gui.add(bwShift.set("B/W shift", 0.0, -1.0, 1.0));
    
    ofBackground(50);
    videoPos = ofVec2f(gui.getWidth() + 20, 0);
    greeting = "Drag & Drop Video to Start";
    
    ofSetWindowShape(8 * greeting.length() + 40, 13.6 + 40);
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight());


}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if (!vidDropped) {
        ofDrawBitmapString(greeting, 20, 20);
    }else{
        
        rawOutput(video, videoPos);
        
        if (enableBlur) {
            blur(bluramt, video, videoPos);
        }
        if (enableBW){
            bw(bwShift, video, videoPos);
        }
        
        output.draw(videoPos);
        
        
        gui.draw();
        ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
        ofSetWindowShape(gui.getWidth() + video.getWidth() + 20, video.getHeight());
    }
}
//-------------------------------------------
void ofApp::blur(float bluramt, ofVideoPlayer &vid, ofVec2f &vidPos){
    
    //image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    if (vid.isFrameNew()) {
        
        fboBlurOnePass.allocate(vid.getWidth(), vid.getHeight());
        fboBlurTwoPass.allocate(vid.getWidth(), vid.getHeight());
        
        float blur = bluramt;
        
        // modified from oF blur tutorial
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
        ofSetColor(ofColor::white);
        //fboBlurTwoPass.draw(vidPos);
        output = fboBlurTwoPass;
    }
}

//--------------------------------------------------------------

void ofApp::bw(float bwShift, ofVideoPlayer &vid, ofVec2f &vidPos){
     if (vid.isFrameNew()) {
         
         bwPass.allocate(vid.getWidth(), vid.getHeight());
         
         //----------------------------------------------------------
         bwPass.begin();
         shaderBW.begin();
         shaderBW.setUniform1f("u_bwshift", bwShift);
         shaderBW.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
         shaderBW.setUniform2f("u_tex0Resolution", image.getWidth(), image.getHeight());
         image.draw(0, 0);
         shaderBW.end();
         bwPass.end();
         //----------------------------------------------------------
         ofSetColor(ofColor::white);
         output = bwPass;
      
         
     }
}

//--------------------------------------------------------------
void ofApp::rawOutput(ofVideoPlayer &vid, ofVec2f &vidPos){
    if (vid.isFrameNew()) {
        image.setFromPixels(vid.getPixels());
        output.allocate(image.getWidth(), image.getHeight());
        output.begin();
        image.draw(0,0);
        output.end();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    if (dragInfo.files.size() > 0  &&  dragInfo.files.size() < 2) {
        filepath = dragInfo.files[0];
        try {
            video.load(filepath);
            videoAspectRatio = video.getWidth()/video.getHeight();
            video.play();
            vidDropped = true;
            output.allocate(video.getWidth(), video.getHeight());
            
        } catch (exception e) {
            cout<<e.what()<<endl;
        }
        
    }

   
}
