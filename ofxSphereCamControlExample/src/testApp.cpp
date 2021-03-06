#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    // Setup Camera and Control
    
    sCamControl.setCamRef(&sCam); // This tells the control add on which camera to control if you have more than one
    sCamControl.setOSC("192.168.0.104", 7000, 7001); // Adjust this to match the iPad ip address and ports in TouchOSC
    
    sCam.handheld = true;
    
    // Test Geometry filler code. Loving the new IcoSphere primative.
    
    ofSetVerticalSync(true);
    
    for (int i = 0; i < 200; i++) {
        icoSpheres.push_back(ofIcoSpherePrimitive());
    }
    
    vector<ofIcoSpherePrimitive>::iterator iS;
    for ( iS = icoSpheres.begin(); iS != icoSpheres.end(); iS++ ) {
        iS->setPosition(ofRandom(-800,800), ofRandom(-800,800), ofRandom(-800,800));
        iS->setResolution(1);
        iS->setRadius( 35 );
        
        // Flat shading is much nicer, don't you think?
        
        iS->setMode( OF_PRIMITIVE_TRIANGLES );
        vector<ofMeshFace> triangles = iS->getMesh().getUniqueFaces();
        iS->getMesh().setFromTriangles( triangles, true );
        
    }

    pointLight.setDiffuseColor( ofFloatColor(.15, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 35.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,194.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );

}

//--------------------------------------------------------------
void testApp::update(){
    
    // Update camera tweens and send position updates to TouchOSC
    
    sCamControl.update(); // This grabs sCam tween data and send over OSC every frame
    sCam.update(); // Need to update the camera tweens otherwise it stays still!
    
    // Update light position and geometry rotation
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    vector<ofIcoSpherePrimitive>::iterator iS;
    for ( iS = icoSpheres.begin(); iS != icoSpheres.end(); iS++ ) {
        iS->rotate(spinX, 1.0, 0.0, 0.0);
        iS->rotate(spinY, 0, 1.0, 0.0);
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    sCam.begin();
    
    ofEnableDepthTest();
    
    ofEnableLighting();
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
    vector<ofIcoSpherePrimitive>::iterator iS;
    for ( iS = icoSpheres.begin(); iS != icoSpheres.end(); iS++ ) {
        iS->draw();
    }
    
    sCam.drawTarget();
    sCam.drawAxis();

    sCam.end();
    
    ofDisableDepthTest();
    ofDisableLighting();
    ofFill();
    ofSetColor(255);
    
    stringstream ss;
    ss << "(s): Spherical rotate around static look vector"<<endl;
    ss << "(m): Tween cam and look vector along straight line"<<endl;
    ss << "(h): Handheld toggle"<<endl;
    
    ofDrawBitmapString(ss.str().c_str(), 20, 20);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case 's':
            sCam.randomPosS();
            break;
        case 'm':
            sCam.randomPosM();
            break;
        case 'h':
            sCam.handheld = !sCam.handheld;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}