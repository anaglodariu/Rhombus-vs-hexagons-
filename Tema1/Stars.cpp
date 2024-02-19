#include "Stars.h"

using namespace std;
using namespace m1;

Star::Star()
{
	this->angularStep = 0;
	this->starRadius = 50;
}

Star::~Star()
{
	
}

bool Star::pickStar(glm::vec2 mousePos)
{
	// if you click inside the circle, return true
	float circle = sqrt(pow(mousePos.x - starCenter.x, 2) + pow(mousePos.y - starCenter.y, 2));
	if (circle <= starRadius)
		return true;
	return false;
}


// getters
float Star::getStarRadius()
{
	return this->starRadius;
}

float Star::getAngularStep()
{
	return this->angularStep;
}

string Star::getMeshStarName()
{
	return this->meshStarName;
}

glm::vec2 Star::getStarCenter()
{
	return this->starCenter;
}


// setters
void Star::setStarRadius(float radius)
{
	this->starRadius = radius;
}

void Star::setAngularStep(float step)
{
	this->angularStep = step;
}

void Star::setMeshStarName(string name)
{
	this->meshStarName = name;
}

void Star::setStarCenter(glm::vec2 center)
{
	this->starCenter = center;
}

