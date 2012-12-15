#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);

	display_gui_ = true;

	draw_island_button_.setup("Island", 5, ofVec2f(20, 20), ofVec2f(30, 20));;
	drawing_islands_ = false;

	put_refinery_button_.setup("Refinery", 5, ofVec2f(20, 60), ofVec2f(30, 20));;
	putting_refineries_ = false;

	put_city_button_.setup("City", 5, ofVec2f(20, 100), ofVec2f(30, 20));;
	putting_cities_ = false;

	put_starting_point_button_.setup("Start", 5, ofVec2f(20, 140), ofVec2f(30, 20));;
	putting_starting_points_ = false;

}

//--------------------------------------------------------------
void testApp::update(){
	


}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0, 0, 0);

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

	ofSetColor(128, 128, 128);
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
	}

	if(drawing_islands_)
		island_points_.push_back(ofVec2f(x, y));
	if(putting_refineries_)
		refineries_.push_back(ofVec2f(x, y));
	if(putting_cities_)
		cities_.push_back(ofVec2f(x, y));
	if(putting_starting_points_)
		starting_points_.push_back(ofVec2f(x, y));

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

