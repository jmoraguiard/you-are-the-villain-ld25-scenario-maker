#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "island.h"
#include "button.h"

#define NUM_PTS 800

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

		vector<Island> islands_;
		vector<ofVec2f> island_points_;

		vector<ofVec2f> refineries_;
		vector<ofVec2f> cities_;
		vector<ofVec2f> starting_points_;

		int pointCount;
		int lineCount;
		int lastTagNumber;

		bool display_gui_;
		ButtonClass draw_island_button_;
		bool drawing_islands_;
		ButtonClass put_refinery_button_;
		bool putting_refineries_;
		ButtonClass put_city_button_;
		bool putting_cities_;
		ButtonClass put_starting_point_button_;
		bool putting_starting_points_;

		ButtonClass save_button_;
		ofxXmlSettings scenario_xml_;
};

