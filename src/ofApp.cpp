#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    ofBackground(50);
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
    video.draw(gui.getWidth() + 20, 0);
    
    if (!vidDropped) {
        ofDrawBitmapString(greeting, 20, 20);
    }else{
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
        video.load(filepath);
        
        videoAspectRatio = video.getWidth()/video.getHeight();
        video.play();
        vidDropped = true;

        
    }

   
}
