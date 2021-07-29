#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "THANKS!";
	int sample_count = 60;

	for (int k = 0; k < 12; k++) {

		auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int i = 0; i < word.size(); i++) {

			ofPath chara_path = this->font.getCharacterAsPoints(word[i], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(-80  + i * -100, this->font_size * -0.5, 0);
					auto rotation = glm::rotate(glm::mat4(), (k * 30.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation;

					auto len = glm::length(location);
					auto noise_value = ofNoise(len * 0.0005 + ofGetFrameNum() * 0.005);
					auto angle_y = ofMap(noise_value, 0, 1, -PI * 3, PI * 3);
					auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

					location = glm::vec4(location, 0) * rotation_y;
					ofVertex(location);
				}
			}
			ofEndShape();

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
				for (auto& vertex : vertices) {

					auto location = vertex - glm::vec3(-80 + i * -100, this->font_size * -0.5, 0);
					auto rotation = glm::rotate(glm::mat4(), (k * 30.f) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation;

					auto len = glm::length(location);
					auto noise_value = ofNoise(len * 0.0005 + ofGetFrameNum() * 0.005);
					auto angle_y = ofMap(noise_value, 0, 1, -PI * 3, PI * 3);
					auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

					location = glm::vec4(location, 0) * rotation_y;
					ofVertex(location);
				}
			}
			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}