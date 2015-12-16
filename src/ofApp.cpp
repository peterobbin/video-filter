#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    gui.setup();
    gui.add(useWebCam.set("use WebCam", false));
    gui.add(enableBlur.set("enable Blur",false));
    gui.add(bluramt.set("blur amount", 0.0, 0.0, 5.0));
    gui.add(enableBW.set("enable B/W",false));
    gui.add(bwShift.set("B/W shift", 0.0, -1.0, 1.0));
    gui.add(enableDistort.set("enable distortion",false));
    gui.add(enableWarp.set("enable warp", false));
    gui.add(enableMix.set("enable mix", false));
    gui.add(swapVid.set("swap video", false));
    gui.add(mixMode.set("mix mode", 0, 0, 2));
    gui.add(mixOpacity.set("mix opacity", 1.0, 0 ,1.0));
    
    ofBackground(50);
    videoPos = ofVec2f(gui.getWidth() + 20, 0);
    greeting = "Drag & drop video to start";
    altGreeting = "or press s to use webcam";
    
    
    ofSetWindowShape(8 * greeting.length() + 40, 13.6 + 40);
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight());

    
    effects.setup();
    
    cam.setup(640, 480);

}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (video.getHeight() == 0 && useWebCam){
        useWebCam = true;
    }
    if (twoVideos) video2.update();
    
    effects.update();
    
    if(useWebCam) {
        cam.init();
        cam.update();
    }else{
        cam.close();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    

    
    
    if (!vidDropped) {
        ofDrawBitmapString(greeting, 20, 20);
        ofDrawBitmapString(altGreeting, 20, 35);
    }else{
        
        if (useWebCam) {
            video.stop();
            output.allocate(cam.camWidth, cam.camHeight);
            effects.rawOutput(cam.vidGrabber, output);
        }else{
            if (video.getHeight() == 0) {
                useWebCam = true;
                cam.init();
                cam.update();
            }else{
                video.play();
                output.allocate(video.getWidth(), video.getHeight());
                effects.rawOutput(video, output);
            }
        }
        

        if (twoVideos && enableMix){
            effects.mixVid(video2, output, output2, mixMode, mixOpacity, swapVid);
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
        
        if (enableWarp) {
            effects.faceWarp(output, useWebCam, cam.nosePos, videoPos);
        }

        
        output.draw(videoPos);
        // if (useWebCam)cam.draw(videoPos);
        
        gui.draw();
        
        if (!useWebCam) {
            ofSetWindowShape(gui.getWidth() + video.getWidth() + 20, video.getHeight());
            ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
            if (twoVideos)ofDrawBitmapString("File Path 2: " + filepath2, gui.getWidth() + 30, ofGetHeight() - 20);
        }else{
            ofSetWindowShape(gui.getWidth() + cam.camWidth + 20, cam.camHeight);
            
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 's':
            if (!useWebCam){
                useWebCam = true;
                vidDropped = true;
            }
            break;
       
        default:
            break;
    }
    


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
            useWebCam = false;
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
            useWebCam = false;
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
