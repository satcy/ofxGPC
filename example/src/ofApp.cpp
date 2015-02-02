#include "ofApp.h"

#include "ofxGPC.h"

ofPath path;
ofPath path2;

vector<ofPolyline> lines;

//--------------------------------------------------------------
void ofApp::setup(){
    path.moveTo(0,0);
    path.lineTo(300, 300);
    path.lineTo(300, 400);
    path.close();
    
    path2.moveTo(100,50);
    path2.lineTo(200, 250);
    path2.lineTo(150, 500);
    path2.close();
    
    lines = ofxGPC::getPolygonClip(GPC_UNION, path, path2);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    path.draw();
    path2.draw();
    
    ofPushMatrix();
    ofTranslate(400, 0);
    for ( auto p : lines ) {
        p.draw();
    }
    ofPopMatrix();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
