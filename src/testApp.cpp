#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth = 960;
	camHeight = 720;
	
	ps3eye.listDevices();
	
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight);
	
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(0.5);
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.5);
	ps3eye.setBrightness(0.6);
	ps3eye.setContrast(1.0);
	ps3eye.setHue(0.0);
	
	ps3eye.setFlicker(1);
    ps3eye.setLed(false);
    
    gui = new ofxUICanvas();
    
    gui->addLabel("microscope", OFX_UI_FONT_LARGE);
    gui->addSpacer();
    gui->addSlider("Gain", 0.0, 1.0, 0.05);
    gui->addSlider("Shutter", 0.0, 1.0, 0.05);
    gui->addSlider("Gamma", 0.0, 1.0, 0.05);
    gui->addSlider("Brightness", 0.0, 1.0, 0.05);
    gui->addSlider("Contrast", 0.0, 1.0, 0.05);
    gui->addSlider("Hue", 0.0, 1.0, 0.05);
    
    gui->addSpacer();
    gui->addLabel("capturing", OFX_UI_FONT_LARGE);
    gui->addToggle("Video", false);
    
    gui->addSpacer();
    gui->addLabel("options", OFX_UI_FONT_LARGE);
    gui->addToggle("Fullscreen", false);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
    
    bShowGUI = false;
    
    fileName = "microscope";
    fileExt = ".mp4";
    
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("1200k");
    
    bRecording = false;
}


//--------------------------------------------------------------
void testApp::update(){
	
	ps3eye.update();    
    gui->setVisible(bShowGUI);
    
    if(ps3eye.isFrameNew() && bRecording){
        vidRecorder.addFrame(ps3eye.getPixelsRef());
    }
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetHexColor(0xffffff);
	ps3eye.draw(0, 0, ofGetWidth(), ofGetWidth() / 4 * 3);
	
}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
	if(name == "Gain") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setGain(slider->getScaledValue());
	}
	if(name == "Shutter") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setShutter(slider->getScaledValue());
	}
	if(name == "Gamma") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setGamma(slider->getScaledValue());
	}
	if(name == "Brightness") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setBrightness(slider->getScaledValue());
	}
	if(name == "Contrast") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setContrast(slider->getScaledValue());
	}
	if(name == "Hue") {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        ps3eye.setHue(slider->getScaledValue());
	}
    else if(e.widget->getName() == "Fullscreen")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());
    }
    else if(e.widget->getName() == "Video")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bRecording = toggle->getValue();
        
        if(bRecording){
            if(!vidRecorder.isInitialized()) {
                vidRecorder.setup(fileName+ofGetTimestampString()+fileExt,
                                  640, 480, 30, sampleRate, channels);
            }
        } else {
            bRecording = false;
            vidRecorder.close();
        }

    }
    
}

//--------------------------------------------------------------
void testApp::exit(){
    
	gui->saveSettings("GUI/guiSettings.xml");
    vidRecorder.close();
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 	

	if(key == 'g'){
        bShowGUI = !bShowGUI;
    }
    
    if(key == 'f'){
        ofSaveFrame();
    }
    
    if(key=='v'){
        bRecording = !bRecording;
        
        if(bRecording){
            if(!vidRecorder.isInitialized()) {
                vidRecorder.setup(fileName+ofGetTimestampString()+fileExt,
                    640, 480, 30, sampleRate, channels);
            }
        } else {
            bRecording = false;
            vidRecorder.close();
        }
        
    }
		
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
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
