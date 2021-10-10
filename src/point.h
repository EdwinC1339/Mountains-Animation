#pragma once

#include "ofMain.h"

class Point {

private:
    glm::vec2 m_pos;
    vector<unsigned int> neighbors;
    ofColor col;
    float radius;
    float timeOfCreation;
public:
    Point(float x, float y);
    Point(glm::vec2 pos);
    ~Point();
    
    glm::vec2 getPos();
    vector<unsigned int> getNeighbors();
    ofColor getCol();
    float getRadius();
    float getTimeOfCreation();
    float getTimeSinceCreation();
    
    void setPos(glm::vec2& pos);
    void setPos(float x, float y);

    void addNeighbor(unsigned int newNeighborIndex);

    void popNeighbor(unsigned int index);

    void setBackNeighbors(unsigned int amount);

    void setColor(ofColor& col);
    void setColor(int red, int green, int blue);
    void setColor(int red, int green, int blue, int alpha);

    void setRadius(float radius);

    void update(float speed);
    void draw(vector<Point*>& points);
};