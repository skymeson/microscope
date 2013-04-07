#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"
#include "ofxUI.h"
#include "ofxVideoRecorder.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofxMacamPs3Eye ps3eye;
	
		int camWidth;
		int camHeight;
    
        ofxUICanvas *gui_camera;
        ofxUICanvas *gui_information;
    
        ofxUITextInput *author;
        ofxUITextInput *date;
        ofxUITextInput *specimen;
        ofxUITextInput *sample_name;
    
        ofxUITextInput *scale_units_textinput;
    
        ofTrueTypeFont newmediafett;
    
        float scale_width;
        float scale_units;
    
        void exit();
        void guiEvent(ofxUIEventArgs &e);
    
        bool bShowGUI;
        bool bShowFooter;
    
        ofxVideoRecorder vidRecorder;
        bool bRecording;
        int sampleRate;
        int channels;
        string fileName;
        string fileExt;
    
        bool bControl;
};
