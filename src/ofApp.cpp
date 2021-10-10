#include "ofApp.h"

#define RANGESIZE 100
#define MAXSIZE 10000
#define TICKSBETWEENRANGES 2
#define BANDS 512

//--------------------------------------------------------------
void ofApp::setup(){
    speed = 1;
    points.reserve(MAXSIZE + RANGESIZE);
    spectrumSmoothed.reserve(BANDS);
    ticksUntilNextRange = TICKSBETWEENRANGES;


}

void ofApp::makeRange(unsigned int pointsToGenerate) {
    for (unsigned int i = 0; i < pointsToGenerate; i++) {
        float x = i * (ofGetWidth() - 50 ) / pointsToGenerate + 25;
        float idontknowwhattocallthis = i * BANDS / pointsToGenerate / 16;
        unsigned int spectrumIndex = idontknowwhattocallthis;

        float y = ofGetHeight() - spectrumSmoothed[spectrumIndex] * ofGetHeight();

        float noiseFactor = ofNoise(x / 80, ofGetElapsedTimef() * 5) * 30;
        y += noiseFactor;

        Point* newPoint = new Point(x, y);
        points.push_back(newPoint);

        newPoint->setColor(0, 255, 255, 0);
        newPoint->setRadius(2.5f);
        if (i) {
            unsigned int last = points.size() - 2;
            newPoint->addNeighbor(last);
        }

        if (points.size() > pointsToGenerate) {
            unsigned int upNeighborIndex = points.size() - pointsToGenerate - 1;
            newPoint->addNeighbor(upNeighborIndex);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ticksUntilNextRange--;
    if (!ticksUntilNextRange) {
        makeRange(RANGESIZE);
        ticksUntilNextRange = TICKSBETWEENRANGES;
        if (points.size() > MAXSIZE) {
            points.erase(points.begin(), points.begin() + RANGESIZE);
            for (Point* point : points) {
                point->setBackNeighbors(RANGESIZE);
            }
        }
    }

    for (Point* point : points) {
         point->update(speed);
    }

    float total = 0;
    constexpr size_t bandsToGet = BANDS;
    if (ofSoundGetSpectrum(bandsToGet) != nullptr) {
        spectrum = ofSoundGetSpectrum(BANDS);
        for (unsigned int i = 0; i < BANDS; i ++) {
            total += spectrum[i];
            if (spectrumSmoothed[i] < spectrum[i]) {
                spectrumSmoothed[i] = spectrum[i];
            } else {
                spectrumSmoothed[i] *= 0.8;
            }
        }
    }

    speed += total * total * 0.5;
    speed = ofLerp(speed, 1, 0.5);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString("Press space to load a song!", 30, 30);
    for (Point* point : points) {
        point->draw(points);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        mySound.setPaused(true);
        loadSong();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

void ofApp::loadSong() {

    ofFileDialogResult path = ofSystemLoadDialog("Select a sound file");

    int attempts = 3;
	
	while (!path.bSuccess && attempts--){
		ofFileDialogResult path = ofSystemLoadDialog("Select a sound file");
	}

	if (path.bSuccess) {
		mySound.load(path.getPath());
		mySound.setVolume(0.4f);
        mySound.setPaused(false);
        mySound.play();
	}
}