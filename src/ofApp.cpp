#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    sampleRate = 44100;
    channels = 2;
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    fileName = "testMovie";
    fileExt = ".mov"; // ffmpeg uses the extension to determine the container type. run 'ffmpeg -formats' to see supported formats
    
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("800k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    
    //    soundStream.listDevices();
    //    soundStream.setDeviceID(11);
    soundStream.setup(this, 0, channels, sampleRate, 256, 4);
    bRecording = false;
    ofEnableAlphaBlending();

    
    
    gui.setup();
    gui.add(useWebCam.set("use WebCam", false));
    gui.add(enableBlur.set("enable Blur",false));
    gui.add(bluramt.set("blur amount", 0.0, 0.0, 5.0));
    gui.add(enableBW.set("enable B/W",false));
    gui.add(bwShift.set("B/W shift", 0.0, -1.0, 1.0));
    gui.add(enableDistort.set("enable distortion",false));
    gui.add(enableWarp.set("enable warp", false));
    gui.add(warpAmt.set("warp intensity", 1.0, 0.0, 6.0));
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
    
    if(bRecording){
        ofImage image;
        image.grabScreen(gui.getWidth() + 20, 0, video.getWidth(), video.getHeight());
        bool success = vidRecorder.addFrame(image.getPixels());
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }
    
    
    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (vidRecorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }
    
    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    

    
    
    if (!vidDropped) {
        ofDrawBitmapString(greeting, 20, 20);
        ofDrawBitmapString(altGreeting, 20, 35);
    }else{
        
//        if (useWebCam) {
//            video.stop();
//            output.allocate(cam.camWidth, cam.camHeight);
//            effects.rawOutput(cam.vidGrabber, output);
//        }else{
//            video.play();
//            output.allocate(video.getWidth(), video.getHeight());
//            effects.rawOutput(video, output);
//        }
        
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
            effects.faceWarp(output, useWebCam, cam.nosePos, videoPos, warpAmt);
        }

        
        output.draw(videoPos);
        // if (useWebCam)cam.draw(videoPos);
        
        gui.draw();
        ofDrawBitmapString("press r to record", 10, ofGetHeight() - 20);
        ofDrawBitmapString("press s to stop", 10, ofGetHeight() - 10);
        if (!useWebCam) {
            ofSetWindowShape(gui.getWidth() + video.getWidth() + 20, video.getHeight());
            ofDrawBitmapString("File Path: " + filepath, gui.getWidth() + 30, ofGetHeight() - 10);
            if (twoVideos)ofDrawBitmapString("File Path 2: " + filepath2, gui.getWidth() + 30, ofGetHeight() - 20);
        }else{
            ofSetWindowShape(gui.getWidth() + cam.camWidth + 20, cam.camHeight);
            
        }
    }
    
    if(bRecording){
        ofSetColor(255, 0, 0);
        ofDrawCircle(ofGetWidth() - 20, 20, 5);
        ofSetColor(255, 255, 255);
    }
}
//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    if(bRecording)
        vidRecorder.addAudioSamples(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
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
            
        case 'r':
            bRecording = !bRecording;
            if(bRecording) {
                vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, video.getWidth(), video.getHeight(), 30, sampleRate, channels);
                
                // Start recording
                vidRecorder.start();
            }
            else if(!bRecording && vidRecorder.isInitialized()) {
                vidRecorder.setPaused(true);
            }
            else if(bRecording && vidRecorder.isInitialized()) {
                vidRecorder.setPaused(false);
            }
            break;
            
        case 'c':
            bRecording = false;
            vidRecorder.close();
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

//--------------------------------------------------------------
void ofApp::exit(){
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    vidRecorder.close();
}
