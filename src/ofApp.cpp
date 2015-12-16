#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    
    gui.setup();
    gui.add(enableBlur.set("enable Blur",false));
    gui.add(bluramt.set("blur amount", 0.0, 0.0, 5.0));
    gui.add(enableBW.set("enable B/W",false));
    gui.add(bwShift.set("B/W shift", 0.0, -1.0, 1.0));
    gui.add(enableDistort.set("enable distortion",false));
    gui.add(enableMix.set("enable mix", false));
    
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
    if (twoVideos) video2.update();
    
    effects.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    if (!vidDropped) {
        ofDrawBitmapString(greeting, 20, 20);
    }else{
        
        effects.rawOutput(video, output);
        if (twoVideos && enableMix){
            effects.mixVid(video2, output, output2);
        }
        
        if (enableBlur) {
            effects.blur(bluramt, output);
        }
        if (enableBW){
            effects.bw(bwShift, output);
        }
        if (enableDistort){
            effects.distortion(output);
        }

        output.draw(videoPos);
        
        gui.draw();
        ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
        if (twoVideos)ofDrawBitmapString("File Path 2: " + filepath2, gui.getWidth() + 30, ofGetHeight() - 20);
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
  //  dragInfo.files.clear();
    cout<<dragInfo.files.size()<<endl;
    if (dragInfo.files.size() > 0  &&  dragInfo.files.size() < 2) {
        filepath = dragInfo.files[0];
        try {
            video.load(filepath);
            videoAspectRatio = video.getWidth()/video.getHeight();
            video.play();
            video2.stop();
            video2.close();
            vidDropped = true;
            twoVideos = false;
            output.allocate(video.getWidth(), video.getHeight());
            
        } catch (exception e) {
            cout<<e.what()<<endl;
        }
        
    }
    
    if (dragInfo.files.size() > 1  &&  dragInfo.files.size() < 3) {
        filepath = dragInfo.files[0];
        filepath2 = dragInfo.files[1];
        try {
            video.load(filepath);
            video2.load(filepath2);
            videoAspectRatio = video.getWidth()/video.getHeight();
            video.play();
            video2.play();
            vidDropped = true;
            twoVideos = true;
            output.allocate(video.getWidth(), video.getHeight());
            output2.allocate(video.getWidth(), video.getHeight());
            
        } catch (exception e) {
            cout<<e.what()<<endl;
        }
        
    }
}
