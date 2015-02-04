#include "ofMain.h"

#include "ofxGPC.h"


class ofApp : public ofBaseApp{
private:
    
    ofPath path;
    ofPath path2;
    
    vector<ofPolyline> unioned;
    vector<ofPolyline> diffed;
    
public:
    void setup(){
        ofBackground(0);
        
        path.moveTo(0,0);
        path.lineTo(120, 150);
        path.lineTo(180, 100);
        path.lineTo(300, 300);
        path.lineTo(300, 400);
        path.close();
        path.setFilled(false);
        path.setStrokeWidth(1);
        
        path2.moveTo(100,50);
        path2.lineTo(200, 250);
        path2.lineTo(150, 500);
        path2.close();
        path2.setFilled(false);
        path2.setStrokeWidth(1);
        
        unioned = ofxGPC::getPolygonClip(ofxGPC::UNION, path, path2);
        diffed = ofxGPC::getPolygonClip(ofxGPC::DIFF, path, path2);
        
    }
    void update(){
        
    }
    void draw(){
        
        path.draw();
        path2.draw();
        
        ofPushMatrix();
        ofTranslate(300, 0);
        for ( auto p : unioned ) {
            p.draw();
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(600, 0);
        for ( auto p : diffed ) {
            p.draw();
        }
        ofPopMatrix();
    }
    
};

int main( ){
	ofSetupOpenGL(900, 500,OF_WINDOW);
	ofRunApp(new ofApp());
}
