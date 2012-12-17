#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);

	display_gui_ = true;

	draw_island_button_.setup("Island", 5, ofVec2f(20, 20), ofVec2f(30, 20));
	drawing_islands_ = false;

	put_refinery_button_.setup("Refinery", 5, ofVec2f(20, 60), ofVec2f(30, 20));
	putting_refineries_ = false;

	put_city_button_.setup("City", 5, ofVec2f(20, 100), ofVec2f(30, 20));
	putting_cities_ = false;

	put_starting_point_button_.setup("Start", 5, ofVec2f(20, 140), ofVec2f(30, 20));
	putting_starting_points_ = false;

	save_button_.setup("Save", 5, ofVec2f(20, 180), ofVec2f(30, 20));

	if(scenario_xml_.loadFile("scenario.xml")){
		cout << "mySettings.xml loaded!" << endl;
	}else{
		cout << "unable to load scenario.xml check data/ folder" << endl;
	}

	if(scenario_xml_.getNumTags("ISLANDS") > 0){
		cout << "Islands processing..." << endl;
		scenario_xml_.pushTag("ISLANDS");
		int numIslands = scenario_xml_.getNumTags("ISLAND");
		if(numIslands > 0){
			int totalIslands = numIslands;
			for(int i = 0; i < totalIslands; i++){
				scenario_xml_.pushTag("ISLAND", i);
				int numPoints = scenario_xml_.getNumTags("PT");
				if(numPoints > 0){
					Island temp_island;// = new Island();
					int totalPoints = numPoints;
					for(int i = 0; i < totalPoints; i++){
						int x = scenario_xml_.getValue("PT:X", 0, i);
						int y = scenario_xml_.getValue("PT:Y", 0, i);
						temp_island.island_shape_points_.push_back(ofVec2f(x, y));
					}
					islands_.push_back(temp_island);
				}
				scenario_xml_.popTag();
			}
		}
		scenario_xml_.popTag();
	}

	if(scenario_xml_.getNumTags("REFINERIES") > 0){
		cout << "Refineries processing..." << endl;
		scenario_xml_.pushTag("REFINERIES");
		int numPoints = scenario_xml_.getNumTags("REFINERY");
		cout << " got " << numPoints << " refineries" << endl;
		if(numPoints > 0){
			int totalPoints = numPoints;
			for(int i = 0; i < totalPoints; i++){
				int x = scenario_xml_.getValue("REFINERY:X", 0, i);
				int y = scenario_xml_.getValue("REFINERY:Y", 0, i);
				refineries_.push_back(ofVec2f(x, y));
			}
		}
		scenario_xml_.popTag();
	}

	if(scenario_xml_.getNumTags("CITIES") > 0){
		cout << "Cities processing..." << endl;
		scenario_xml_.pushTag("CITIES");
		int numPoints = scenario_xml_.getNumTags("CITY");
		cout << " got " << numPoints << " cities" << endl;
		if(numPoints > 0){
			int totalPoints = numPoints;
			for(int i = 0; i < totalPoints; i++){
				int x = scenario_xml_.getValue("CITY:X", 0, i);
				int y = scenario_xml_.getValue("CITY:Y", 0, i);
				cities_.push_back(ofVec2f(x, y));
			}
		}
		scenario_xml_.popTag();
	}

}

//--------------------------------------------------------------
void testApp::update(){
	


}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0, 0, 0);

	ofSetColor(192, 192, 192);
	for(int i = 0; i < 62; i++){
		ofLine(i*ofGetWidth()/60, 0, i*ofGetWidth()/60, ofGetHeight());
	}
	for(int i = 0; i < 42; i++){
		ofLine(0, i*ofGetHeight()/40, ofGetWidth(), i*ofGetHeight()/40);
	}

	if(drawing_islands_)
		ofDrawBitmapString("Islands", 505, 20);

	if(putting_refineries_)
		ofDrawBitmapString("Refineries", 505, 20);

	if(putting_cities_)
		ofDrawBitmapString("Cities", 505, 20);

	if(putting_starting_points_)
		ofDrawBitmapString("Starting points", 495, 20);

	if(islands_.size() > 0){
		for(int i = 0; i < islands_.size(); i++)
			islands_[i].draw();
	}

	ofSetColor(0, 0, 0);
	if(refineries_.size() > 0){
		for(int i = 0; i < refineries_.size(); i++)
			ofRect(refineries_[i].x, refineries_[i].y, 5, 5);
	}

	ofSetColor(0, 0, 255);
	if(cities_.size() > 0){
		for(int i = 0; i < cities_.size(); i++)
			ofRect(cities_[i].x, cities_[i].y, 5, 5);
	}

	ofSetColor(0, 255, 0);
	if(starting_points_.size() > 0){
		for(int i = 0; i < starting_points_.size(); i++)
			ofRect(starting_points_[i].x, starting_points_[i].y, 5, 5);
	}

	ofPushStyle();
		ofSetColor(128, 128, 0);
		glBegin(GL_POLYGON);
		for(int i = 0; i < island_points_.size(); i++)
			glVertex2d(island_points_[i].x, island_points_[i].y);
		glEnd();
	ofPopStyle();

	ofSetColor(64, 64, 64);
	if(island_points_.size() > 0){
		for(int i = 0; i < island_points_.size()-1; i++)
			ofLine(island_points_[i].x, island_points_[i].y, island_points_[i+1].x, island_points_[i+1].y);
		ofLine(island_points_.at(island_points_.size()-1).x, island_points_.at(island_points_.size()-1).y, island_points_.at(0).x, island_points_.at(0).y);
	}

	if(display_gui_){
		draw_island_button_.draw();
	
		put_refinery_button_.draw();
	
		put_city_button_.draw();
	
		put_starting_point_button_.draw();

		save_button_.draw();
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	if(key == 8){
		if(drawing_islands_)
			if(island_points_.size() > 0)
				island_points_.pop_back();
		if(putting_refineries_)
			if(refineries_.size() > 0)
				refineries_.pop_back();
		if(putting_cities_)
			if(cities_.size() > 0)
				cities_.pop_back();
		if(putting_starting_points_)
			if(starting_points_.size() > 0)
				starting_points_.pop_back();
	}

	if(key == 257){
		display_gui_ = !display_gui_;
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

	if(display_gui_){
		if(draw_island_button_.isUnderPoint(ofVec2f(x, y)) && !putting_refineries_ && !putting_cities_ && !putting_starting_points_){
			if(drawing_islands_ && island_points_.size() > 3){
				Island temp_island;
				for(int i = 0; i < island_points_.size(); i++)
					temp_island.island_shape_points_.push_back(island_points_[i]);
				islands_.push_back(temp_island);
				island_points_.clear();
			}
			drawing_islands_ = !drawing_islands_;
			return;
		}

		if(put_refinery_button_.isUnderPoint(ofVec2f(x, y)) && !drawing_islands_ && !putting_cities_ && !putting_starting_points_){
			putting_refineries_ = !putting_refineries_;
			return;
		}

		if(put_city_button_.isUnderPoint(ofVec2f(x, y)) && !putting_refineries_ && !drawing_islands_ && !putting_starting_points_){
			putting_cities_ = !putting_cities_;
			return;
		}

		if(put_starting_point_button_.isUnderPoint(ofVec2f(x, y)) && !putting_refineries_ && !putting_cities_ && !drawing_islands_){
			putting_starting_points_ = !putting_starting_points_;
			return;
		}

		if(save_button_.isUnderPoint(ofVec2f(x, y)) && !putting_refineries_ && !putting_cities_ && !drawing_islands_ && !putting_starting_points_){
			
			ofxXmlSettings scenario;
			scenario.loadFile("scenario.xml");
			scenario.clear();

			int lastTagNumber = 0;

			lastTagNumber = scenario.addTag("ISLANDS");
			if(scenario.pushTag("ISLANDS", lastTagNumber) ){
				for(int i = 0; i < islands_.size(); i++){
					int lastTag = scenario.addTag("ISLAND");
					if(scenario.pushTag("ISLAND", lastTag) ){

						for(int j = 0; j < islands_[i].island_shape_points_.size(); j++){
							int tagNum = scenario.addTag("PT");
							scenario.setValue("PT:X", (double)islands_[i].island_shape_points_[j].x, tagNum);
							scenario.setValue("PT:Y", (double)islands_[i].island_shape_points_[j].y, tagNum);
						}

						scenario.popTag();
					}
				}
				scenario.popTag();
			}

			lastTagNumber = scenario.addTag("REFINERIES");
			if(scenario.pushTag("REFINERIES", lastTagNumber) ){

				for(int i = 0; i < refineries_.size(); i++){
					int tagNum = scenario.addTag("REFINERY");
					scenario.setValue("REFINERY:X", (double)refineries_[i].x, tagNum);
					scenario.setValue("REFINERY:Y", (double)refineries_[i].y, tagNum);
				}

				scenario.popTag();
			}
			scenario.popTag();

			lastTagNumber = scenario.addTag("CITIES");
			if(scenario.pushTag("CITIES", lastTagNumber) ){

				for(int i = 0; i < cities_.size(); i++){
					int tagNum = scenario.addTag("CITY");
					scenario.setValue("CITY:X", (double)cities_[i].x, tagNum);
					scenario.setValue("CITY:Y", (double)cities_[i].y, tagNum);
				}

				scenario.popTag();
			}
			scenario.popTag();

			lastTagNumber = scenario.addTag("STARTING_POINTS");
			if(scenario.pushTag("STARTING_POINTS", lastTagNumber) ){

				for(int i = 0; i < starting_points_.size(); i++){
					int tagNum = scenario.addTag("START_POINT");
					scenario.setValue("START_POINT:X", (double)starting_points_[i].x, tagNum);
					scenario.setValue("START_POINT:Y", (double)starting_points_[i].y, tagNum);
				}

				scenario.popTag();
			}
			scenario.popTag();

			scenario.saveFile("scenario.xml");

			return;
		}
	}

	float xf = 0;
	float yf = 0;

	float dist = 1000000;
	for(int i = 0; i < 62; i++){
		if(abs((i*ofGetWidth()/60) - x) < dist){
			xf = i*ofGetWidth()/60;
			dist = abs((i*ofGetWidth()/60) - x);
		}
	}

	dist = 1000000;
	for(int i = 0; i < 42; i++){
		if(abs((i*ofGetHeight()/40) - y) < dist){
			yf = i*ofGetHeight()/40;
			dist = abs((i*ofGetHeight()/40) - y);
		}
	}

	if(drawing_islands_)
		island_points_.push_back(ofVec2f(xf, yf));
	if(putting_refineries_)
		refineries_.push_back(ofVec2f(xf, yf));
	if(putting_cities_)
		cities_.push_back(ofVec2f(xf, yf));
	if(putting_starting_points_)
		starting_points_.push_back(ofVec2f(xf, yf));

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

