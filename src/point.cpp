#include "point.h"


Point::Point(float x, float y) {
    this->m_pos = {x, y};
    this->timeOfCreation = ofGetElapsedTimef();
}

Point::Point(glm::vec2 pos) {
    this->m_pos = pos;
    this->timeOfCreation = ofGetElapsedTimef();
}

Point::~Point() {
    this->neighbors.clear();
    this->neighbors.shrink_to_fit();
}

glm::vec2 Point::getPos() {
    return this->m_pos;
}

vector<unsigned int> Point::getNeighbors() {
    return this->neighbors;
}

ofColor Point::getCol() {
    return this->col;
}

float Point::getRadius() {
    return this->radius;
}

float Point::getTimeOfCreation() {
    return this->timeOfCreation;
}

float Point::getTimeSinceCreation() {
    return ofGetElapsedTimef() - this->timeOfCreation;
}

void Point::setPos(glm::vec2& pos) {
    this->m_pos = pos;
}

void Point::setPos(float x, float y) {
    this->m_pos.x = x;
    this->m_pos.y = y;
}

void Point::addNeighbor(unsigned int newNeighborIndex) {
    this->neighbors.push_back(newNeighborIndex);
}

void Point::popNeighbor(unsigned int index) {
    auto it = this->neighbors.begin() + index;
    this->neighbors.erase(it);
}

void Point::setBackNeighbors(unsigned int amount) {
    for (unsigned int & neighborIndex : this->neighbors) {
        if (amount > neighborIndex) {
            return;
        }
        neighborIndex -= amount;
    }
}

void Point::setColor(ofColor& col) {
    this->col = col;
}

void Point::setColor(int red, int green, int blue) {
    ofColor col(red, green, blue);
    this->col = col;
}

void Point::setColor(int red, int green, int blue, int alpha) {
    ofColor col(red, green, blue, alpha);
    this->col = col;
}

void Point::setRadius(float radius) {
    this->radius = radius;
}

void Point::update(float speed) {
    if (this->getTimeSinceCreation() > 0.14) {
        this->m_pos.x = ofLerp(this->m_pos.x, ofGetWidth() / 2, 0.005 * speed);
        this->m_pos.y = ofLerp(this->m_pos.y, ofGetHeight() / 2, 0.005 * speed);
        this->radius = ofLerp(this->radius, 0, 0.005 * speed);
        this->col.a = ofLerp(this->col.a, 0, 0.005 * speed);
    } else {
        this->col.a = ofLerp(this->col.a, 255, 0.05);
    }

}

void Point::draw(vector<Point*>& points) {
    ofSetColor(this->col);
    ofDrawCircle(this->m_pos, this->radius);

    for (unsigned int neighborIndex : neighbors) {
        auto it = points.begin() + neighborIndex;
        Point* neighborPtr = *it;
        const glm::vec2& neighborPos = neighborPtr->getPos();
        ofDrawLine(this->m_pos, neighborPos);
    }
}
