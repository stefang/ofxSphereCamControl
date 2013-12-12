/*
 *  ofxSphereCam.h
 *
 *  Created by Stefan Goodchild on 13-08-12.
 *  Copyright 2012/13 Triple Geek Ltd. All rights reserved.
 *
 */

#include "ofxSphereCamControl.h"

void ofxSphereCamControl::setCamRef(ofxSphereCam* camPtr) {
    sCam = camPtr;
}

void ofxSphereCamControl::setOSC(string host, int inport, int outport ) {
    sender.setup(host, outport);
    receiver.setup(inport);
}

void ofxSphereCamControl::setScale(float s) {
    scale = s;
}

void ofxSphereCamControl::update() {
    
    // Check for incoming from TouchOSC
    
    if (!receiver.hasWaitingMessages()) {
        // Send any changes if there's no incoming changes
        // This should stop the in/out conflict of changing settings during tween updates
        
        ofxOscMessage mCam;
        mCam.setAddress("/position/cam");
        mCam.addFloatArg(sCam->movedTo.x/scale);
        mCam.addFloatArg(sCam->movedTo.y/scale);
        mCam.addFloatArg(sCam->movedTo.z/scale);
        sender.sendMessage(mCam);
        
        ofxOscMessage mTar;
        mTar.setAddress("/position/tar");
        mTar.addFloatArg(sCam->lookedAt.x/scale);
        mTar.addFloatArg(sCam->lookedAt.y/scale);
        mTar.addFloatArg(sCam->lookedAt.z/scale);
        sender.sendMessage(mTar);
        
        if (handheldMonitor!=sCam->handheld) {
            handheldMonitor = sCam->handheld;
            ofxOscMessage mHan;
            mHan.setAddress("/position/handheld");
            mHan.addIntArg(sCam->handheld);
            sender.sendMessage(mHan);
        }
    }
    
    while(receiver.hasWaitingMessages()){
        
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
        ofVec3f currentPos = sCam->movedTo;
        
		if(m.getAddress() == "/position/cam/1"){
            currentPos.x = m.getArgAsFloat(0)*scale;
		}
		if(m.getAddress() == "/position/cam/2"){
            currentPos.y = m.getArgAsFloat(0)*scale;
		}
		if(m.getAddress() == "/position/cam/3"){
            currentPos.z = m.getArgAsFloat(0)*scale;
		}
        
        if (currentPos != sCam->movedTo) {
            sCam->moveTo(currentPos, 0);
            cout << "ofVec3f mt = ofVec3f(" << currentPos.x << ", " << currentPos.y << ", " << currentPos.z << ");" << endl;
            cout << "ofVec3f la = ofVec3f(" << sCam->lookedAt.x << ", " << sCam->lookedAt.y << ", " << sCam->lookedAt.z << ");" << endl;
            cout << "--" << endl;
        }
        
        ofVec3f currentLook = sCam->lookedAt;
        
		if(m.getAddress() == "/position/tar/1"){
            currentLook.x = m.getArgAsFloat(0)*scale;
		}
		if(m.getAddress() == "/position/tar/2"){
            currentLook.y = m.getArgAsFloat(0)*scale;
		}
		if(m.getAddress() == "/position/tar/3"){
            currentLook.z = m.getArgAsFloat(0)*scale;
		}
        
        if (currentLook != sCam->lookedAt) {
            sCam->lookAtTo(currentLook, 0);
            cout << "ofVec3f mt = ofVec3f(" << sCam->movedTo.x << ", " << sCam->movedTo.y << ", " << sCam->movedTo.z << ");" << endl;
            cout << "ofVec3f la = ofVec3f(" << currentLook.x << ", " << currentLook.y << ", " << currentLook.z << ");" << endl;
            cout << "--" << endl;
        }
        
        if(m.getAddress() == "/position/handheld"){
            sCam->handheld = m.getArgAsInt32(0);
        }
        
        if(m.getAddress() == "/position/moveto"){
            sCam->randomPosM();
        }
        if(m.getAddress() == "/position/sphereto"){
            sCam->randomPosS();
        }

	
    }
    
}