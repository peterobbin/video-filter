//
//  WebCam.cpp
//  video-filter
//
//  Created by peterobbin on 12/16/15.
//
//

#include "WebCam.hpp"


void WebCam::setup(int _width, int _height){
    camWidth = _width;
    camHeight = _height;
    
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    initComplete = false;
    

}

void WebCam::init(){
    if (!initComplete)vidGrabber.initGrabber(camWidth, camHeight);
    initComplete = true;
}

void WebCam::update(){
    vidGrabber.update();



}

void WebCam::close(){
    vidGrabber.close();
    initComplete = false;
}


void WebCam::draw(ofVec2f _pos){

    vidGrabber.draw(_pos);
}