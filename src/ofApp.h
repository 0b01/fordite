#pragma once

#include "ofMain.h"


class Layers
{
public:
	std::vector<ofPolyline> lvls;
	std::vector<ofColor> colors;
	int levels = 200;
	int w = ofGetWidth();
	int h = ofGetHeight();
	
	float height = 15;

	float smoothness = 550;
	float increment = 1/(float)smoothness;
	
	float variance = 10;
	float v = 0;
	float a = 0.001;

	uint64_t lasttime = ofGetElapsedTimeMillis();

	Layers(){
		updateColor();
	};
	void generate(){
		lvls.clear();
		for (int lvl = 0; lvl < levels; lvl++)
		{

			float normalized_lvl = (float)lvl / (float)levels * variance + v;
			ofPolyline noise;

			if ( lvls.empty() ){
				ofPolyline init;
				for (float x = 0; x < 1; x += increment)
				{
					init.addVertex(ofVec2f( x*w, h ));
					float randomNoise = ofNoise(normalized_lvl, x)*height + h - height;
					noise.addVertex(
						ofVec2f( x*w, randomNoise )
					);
				}
				lvls.push_back(init);
			}
			else 
			{
				for (float x = 0; x < 1; x += increment)
				{
					float randomNoise = 
						lvls.back().getVertices()[x*smoothness].y - ofNoise(normalized_lvl, x)* height;
					noise.addVertex(
						ofVec2f( x*w, randomNoise )
					);
				}
			}
			lvls.push_back(noise);
		}
		// if( colors.empty() || ofGetElapsedTimeMillis() - lasttime > 1000) {
		// 		updateColor();
		// }
	}
	void changeAcc(bool faster){
		if(faster) a+= 0.01;
		else a-= 0.01;
	}
	void changeVar(bool smoother) {
		if(smoother)variance *= 2;
		else variance /= 2;
	}
	void update(){
		v += a;
		generate();
	}
	void updateColor(){
		colors.clear();


		//The Great Wave off Kanagawa
		// std::vector<ofColor> palette = {ofColor(162,250,163),ofColor(146,201,177),ofColor(79,117,155),ofColor(93,81,121),ofColor(87,31,78)};
		//

		//Shades of Red
		// std::vector<ofColor> palette = {ofColor(221,48,68),ofColor(229,78,88),ofColor(238,109,110),ofColor(246,140,131),ofColor(255,172,153)};

		//Shades of Green
		// std::vector<ofColor> palette = {ofColor(123,255,212),ofColor(48,242,159),ofColor(105,156,129),ofColor(0,120,93),ofColor(2,51,0)};
		
		//Shades of Blue
		// std::vector<ofColor> palette = {ofColor(117,127,202),ofColor(61,102,156),ofColor(20,174,228),ofColor(119,202,242),ofColor(192,252,252)};

		//RGB
		// std::vector<ofColor> palette = {ofColor::red, ofColor::green, ofColor::blue};

		// random
		// std::vector<ofColor> palette = {ofColor(7,174,161),ofColor(28,180,146),ofColor(4,182,115),ofColor(213,225,16),ofColor(238,195,15)};

		// brown - yellow - red
		std::vector<ofColor> palette = {ofColor(0,82,165),ofColor(224,22,43),ofColor(255,255,255),ofColor(169,169,169),ofColor(21,21,21)};

		// /*
		//  *
		//  * Method 1
		//  *
		//  */
		// for (int lvl = 0; lvl < levels; lvl++){
		//   	double cindex_abs, fractpart, intpart;
		// 	cindex_abs = ((float)lvl/(float)levels*(float)palette.size());
		// 	fractpart = modf (cindex_abs , &intpart);
		// 	colors.push_back(
		// 		palette.at(ofClamp(intpart,0,palette.size()-1)).getLerped(
		// 			palette.at(ofClamp(intpart+1,0,palette.size()-1)), fractpart)
		// 		);
		// }


		/*
		 *
		 * Method 2
		 *
		 */
		for (int lvl = 0; lvl < levels; lvl++){
			colors.push_back(
				palette.at(lvl%palette.size())
				);
		}

		lasttime = ofGetElapsedTimeMillis();
	}
	void draw(){
		for (std::vector<ofPolyline>::iterator poly = lvls.begin(); poly != std::prev(lvls.end(),1); poly++)
		{
			int index = poly-lvls.begin();
		    ofSetColor(colors.at(index));
    		ofFill();
			ofBeginShape();
			    for( int i = 0; i < poly->getVertices().size(); i++) {  
			        ofVertex(
			        	poly->getVertices().at(i).x,
			        	poly->getVertices().at(i).y + ofNoise(i) * 100
			        	);  
			    }
			    for( int i = std::next(poly,1)->getVertices().size()-1; i>0 ;i--) {
			        ofVertex(
			        	std::next(poly,1)->getVertices().at(i).x, 
			        	std::next(poly,1)->getVertices().at(i).y + ofNoise(i) * 100
			        	);
			    }

			ofEndShape();

			// poly->draw();
		}

	}
	~Layers(){};
};




class ofApp : public ofBaseApp{
	private:
		Layers l;
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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
