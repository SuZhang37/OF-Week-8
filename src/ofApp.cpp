#include "ofApp.h"

ofFbo fbo,spFbo;
float x,y, angle = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    song.load("I Really Like You.mp3");
    while(!song.isLoaded());
    song.play();
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    //ofBackground(250,182,196);
    ofBackground(250,206,196);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    spFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F);
    
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    spFbo.begin();
    ofClear(255,255,255, 0);
    spFbo.end();
    
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    nBandsToGet = 112;

}
float *val;

//--------------------------------------------------------------
void ofApp::update(){

    ofSoundUpdate();
    val = ofSoundGetSpectrum(nBandsToGet);
    
    
    for (int i = 0;i < nBandsToGet; i++){
        

        fftSmoothed[i] *= 0.96f;

        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
}



//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofSetColor(250,206,196, 5);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    
    
    
    
    float width = (float)(5*112) / nBandsToGet;
    for(int i =0; i<nBandsToGet;i++){


        
        if(fftSmoothed[i]*200>10){
        ofRotate(val[i]*90);

        }
        
        if(val[i]>val[90] && val[i]<val[100]){
        
        ofSetColor(255, 255, 255,ofRandom(100,255));
        ofNoFill();
        ofDrawCircle(0,0, 70+fftSmoothed[i/50]*100);
        }
        cout<< val[i] << endl;
        
        for(int j = 0; j<fftSmoothed[i]*200; j+=ofRandom(15,40)){
            ofFill();
            ofSetColor(ofRandom(176,251),235,ofRandom(170,228),255);
            ofDrawCircle(i*width, -j, ofRandom(5));
            
        }
        
        
    }
    
    ofPopMatrix();
    
    fbo.end();
    ofSetColor(255,255,255);
    fbo.draw(0,0);
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

}
