#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    shaderBlurX.load("blurx.vert","blurx.frag");
    shaderBlurY.load("blury.vert","blury.frag");
    
    gui.setup();
    gui.add(enableBlur.set("enable Blur",true));
    gui.add(bluramt.set("blur amount", 0.0, 0.0, 5.0));
    
    ofBackground(50);
    videoPos = ofVec2f(gui.getWidth() + 20, 0);
    greeting = "Drag & Drop Video to Start";
    cout<<greeting.length()<<endl;
    
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
        if (enableBlur) {
            blur(bluramt, video, videoPos);
        }else{
            video.draw(videoPos);
        }
        gui.draw();
        ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
        ofSetWindowShape(gui.getWidth() + video.getWidth() + 20, video.getHeight());
    }
}
//-------------------------------------------
void ofApp::blur(float bluramt, ofVideoPlayer &vid, ofVec2f &vidPos){
    
    //image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    if (vid.isFrameNew()) {
        image.setFromPixels(vid.getPixels());
        
        fboBlurOnePass.allocate(image.getWidth(), image.getHeight());
        fboBlurTwoPass.allocate(image.getWidth(), image.getHeight());
        
        
        
        float blur = bluramt;
        
        // modified from oF blur tutorial
        // horizonal pass
        //----------------------------------------------------------
        fboBlurOnePass.begin();
        shaderBlurX.begin();
        shaderBlurX.setUniform1f("blurAmnt", blur);
        image.draw(0, 0);
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
        fboBlurTwoPass.draw(vidPos);
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
        video.load(filepath);
        
        videoAspectRatio = video.getWidth()/video.getHeight();
        video.play();
        vidDropped = true;

        
    }

   
}
