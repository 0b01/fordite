#include "ofApp.h"






//--------------------------------------------------------------
void ofApp::setup(){
	l = Layers();
	l.generate();
}

//--------------------------------------------------------------
void ofApp::update(){
	l.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	l.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case OF_KEY_UP:
			l.changeAcc(true);
			break;
		case OF_KEY_DOWN:
			l.changeAcc(false);
			break;
		case OF_KEY_LEFT:
			l.changeVar(false);
			break;
		case OF_KEY_RIGHT:
			l.changeVar(true);
			break;
		default:
			break;
	}

	stringstream stream;
	stream << "var: "<< l.variance << ", acc: "<< l.a;
	std::cout << stream.str() << std::endl;
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
