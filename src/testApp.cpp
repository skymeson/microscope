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
    
    gui_camera = new ofxUICanvas(0, 0, 255, ofGetHeight());
    
    gui_camera->addLabel("microscope", OFX_UI_FONT_LARGE);
    gui_camera->addSpacer();
    gui_camera->addSlider("Gain", 0.0, 1.0, 0.05);
    gui_camera->addSlider("Shutter", 0.0, 1.0, 0.05);
    gui_camera->addSlider("Gamma", 0.0, 1.0, 0.05);
    gui_camera->addSlider("Brightness", 0.0, 1.0, 0.05);
    gui_camera->addSlider("Contrast", 0.0, 1.0, 0.05);
    gui_camera->addSlider("Hue", 0.0, 1.0, 0.05);
    
    gui_camera->addLabel("scale", OFX_UI_FONT_LARGE);
    gui_camera->addSpacer();
    gui_camera->addSlider("Scale Width", 0.0, 1.0, 0.05);
    scale_units_textinput = (ofxUITextInput *) gui_camera->addWidgetDown(new ofxUITextInput("Scale Units", "100", 250, 30));
    
//    gui_camera->addSpacer();
//    gui_camera->addLabel("capturing", OFX_UI_FONT_LARGE);
//    gui_camera->addToggle("Video", false);
    
    gui_camera->addSpacer();
    gui_camera->addLabel("options", OFX_UI_FONT_LARGE);
    gui_camera->addToggle("Fullscreen", false);
    
    gui_camera->addSpacer();
    gui_camera->addLabel("shortcuts", OFX_UI_FONT_LARGE);
    gui_camera->addLabel("down + g: show/hide gui", OFX_UI_FONT_SMALL);
    gui_camera->addLabel("down + i: show/hide infobox", OFX_UI_FONT_SMALL);
    gui_camera->addLabel("down + f: capture frame", OFX_UI_FONT_SMALL);
    gui_camera->addLabel("down + v: capture video", OFX_UI_FONT_SMALL);
    gui_camera->addSpacer();
    gui_camera->addLabel("frame is captured with infobox or gui", OFX_UI_FONT_SMALL);
    gui_camera->addLabel("video is named after info in infobox", OFX_UI_FONT_SMALL);
    
    gui_camera->autoSizeToFitWidgets();
    ofAddListener(gui_camera->newGUIEvent, this, &testApp::guiEvent);
    gui_camera->loadSettings("GUI/camera.xml");
    
    gui_information = new ofxUICanvas(ofGetWidth() - 255, 0, 255, 180);

    gui_information->addLabel("information", OFX_UI_FONT_LARGE);
    gui_information->addSpacer();
    gui_information->addLabel("author", OFX_UI_FONT_SMALL);
    author = (ofxUITextInput *) gui_information->addWidgetDown(new ofxUITextInput("Author", "", 250, 30));
    gui_information->addLabel("date", OFX_UI_FONT_SMALL);
    date = (ofxUITextInput *) gui_information->addWidgetDown(new ofxUITextInput("Date", "", 250, 30));
    gui_information->addLabel("specimen", OFX_UI_FONT_SMALL);
    specimen = (ofxUITextInput *) gui_information->addWidgetDown(new ofxUITextInput("Specimen", "", 250, 30));
    gui_information->addLabel("sample_name", OFX_UI_FONT_SMALL);
    sample_name = (ofxUITextInput *) gui_information->addWidgetDown(new ofxUITextInput("Sample Name", "", 250, 30));
    
    gui_information->autoSizeToFitWidgets();
    ofAddListener(gui_information->newGUIEvent, this, &testApp::guiEvent);
	gui_information->loadSettings("GUI/information.xml");
    
    scale_width = 200.0;
    scale_units = 10.0;
    
    bShowGUI = true;
    bShowFooter = true;
    
    fileName = "microscope";
    fileExt = ".mp4";
    
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("1200k");
    
    bRecording = false;
    bControl = false;
    
    newmediafett.loadFont("GUI/NewMedia Fett.ttf", 14, true, true);
}


//--------------------------------------------------------------
void testApp::update(){
	
	ps3eye.update();
    gui_camera->setVisible(bShowGUI);
    gui_information->setVisible(bShowFooter);
    
    if(ps3eye.isFrameNew() && bRecording){
        vidRecorder.addFrame(ps3eye.getPixelsRef());
    }
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetHexColor(0xffffff);
	ps3eye.draw(0, 0, ofGetWidth(), ofGetWidth() / 4 * 3);
    
    gui_camera->setHeight(ofGetHeight());
    gui_information->setPosition(ofGetWidth() - 255, 0);
    
//    ofSetColor(255, 255, 255);
//    ofLine(ofGetWidth() / 2 - ofGetWidth() * scale_width / 2, ofGetHeight() - 50, ofGetWidth() / 2 + ofGetWidth() * scale_width / 2, ofGetHeight() - 50);
//    
//    ostringstream units_label;
//    units_label << scale_units;
//    
//    newmediafett.drawString(units_label.str(), ofGetWidth() / 2, ofGetHeight() - 65);
	
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
    if(e.widget->getName() == "Fullscreen")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());
    }
    if(e.widget->getName() == "Scale Width")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        scale_width = slider->getScaledValue();
    }
    if(e.widget->getName() == "Scale Units")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        istringstream(textinput->getTextString()) >> scale_units;
//        ofxText *slider = (ofxUISlider *) e.widget;
//        scale_units = slider->getScaledValue();
    }
    if(e.widget->getName() == "Video")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        bRecording = toggle->getValue();
        
        if(bRecording){
            if(!vidRecorder.isInitialized()) {
                fileName = specimen->getTextString()
                            + "-" + sample_name->getTextString()
                            + ": " + date->getTextString()
                            + " - " + author->getTextString();
                vidRecorder.setup(fileName+fileExt,
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
    
	gui_camera->saveSettings("GUI/camera.xml");
	gui_information->saveSettings("GUI/information.xml");
    vidRecorder.close();
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 	
    
	if(key == OF_KEY_DOWN){
        bControl = true;
    }
    
    if(bControl){
        if(key == 'g'){
            bShowGUI = !bShowGUI;
        }
    
        if(key == 'i'){
            bShowFooter = !bShowFooter;
        }
    
        if(key == 'f'){
            ofSaveFrame();
        }
    
        if(key=='v'){
            bRecording = !bRecording;
        
            if(bRecording){
                if(!vidRecorder.isInitialized()) {
                    fileName = specimen->getTextString()
                    + "-" + sample_name->getTextString()
                    + ":" + date->getTextString()
                    + "-" + author->getTextString();
                    vidRecorder.setup(fileName+fileExt,
                                      640, 480, 30, sampleRate, channels);
                }
            } else {
                bRecording = false;
                vidRecorder.close();
            }
        
        }
        
    }
		
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
    
	if(key == OF_KEY_DOWN){
        bControl = false;
    }
    
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
