#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	float rave = rand() % 256;
	float rave1 = rand() % 256;
	float rave2 = rand() % 256;
		float Bit = 1;
		float Z = 10;
		float I = 10; 
	//	while (Z <= 500)
	//{		
	//	ofDrawBitmapString(Bit, Z, I);
	//		Z = Z + 40;
	//		Bit = Bit + 1;
	//		I = 20;
		
			/*while (I <= 1000)
			{

				Z = 10;
				while (Z <= 1000)
				{
					
						ofDrawBitmapString(Bit, Z, I);
					Z = Z + 30;
					Bit = Bit + 1; 
					//Bit = (Bit + 32) + 1; 
				}
				I = I + 30;
			
			}
			//I = I + 3;
			
			//std:: cout << Bit;
	//}*/
	float X = 200;
	float Y = 200;
	float size = 100;
		float windowx = X + size / 2;
		float windowY1 = Y+size*1/10;
		float windowY2 = Y+size * 1/10;
		float DoorX = X + size / 10;
		float DoorY = Y + size / 2;
		float doorsizeY = size / 2;
		float doorsizeX = size / 4;
		float windowsize = size * 90/300;
		ofSetColor(255, 0, 0);
	ofDrawTriangle(X , Y, X + size/2, Y - size / 2, X+size, Y);
	ofSetColor(rave, rave1, rave2);
	ofDrawCircle(X+size/2, Y - size/4, size/8);
	ofSetColor(20, 50, 10);
	ofDrawRectangle(X, Y, size, size);
	ofSetColor(100, 100, 100);
	ofDrawRectangle(DoorX, DoorY, doorsizeX, doorsizeY);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(windowx, windowY1, windowsize, windowsize);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(windowx, DoorY, windowsize, windowsize);
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
