/*
 *  ofxSphereCamControl.h
 *
 *  Created by Stefan Goodchild on 08-09-13.
 *  Copyright 2013 Triple Geek Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxSphereCam.h"

class ofxSphereCamControl {

public:
    
	ofxSphereCamControl() :
        sCam(NULL),
        scale(600),
        handheldMonitor(NULL)
    {};
    void setCamRef(ofxSphereCam* camPtr);
    void setOSC(string host, int inport, int outport);
    void setScale(float scale);
    void update();

protected:
    ofxSphereCam* sCam;
    ofxOscSender sender;
    ofxOscReceiver receiver;
    float scale;
    bool handheldMonitor;
};
