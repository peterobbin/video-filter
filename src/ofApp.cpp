#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    
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

    
    effects.setup();

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
        
        effects.rawOutput(video, output);
        
        if (enableBlur) {
            effects.blur(bluramt, output);
        }
        if (enableBW){
            effects.bw(bwShift, output);
        }
        
       output.draw(videoPos);
        gui.draw();
        ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
        ofSetWindowShape(gui.getWidth() + video.getWidth() + 20, video.getHeight());
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
