#include "Frames.h"

using namespace std;
using namespace m1;

Frames::Frames()
{
}

Frames::~Frames()
{
}

// getters
glm::vec2 Frames::getPosition()
{
	return this->position;
}

glm::vec3 Frames::getColor()
{
	return this->color;
}

float Frames::getLength()
{
	return this->length;
}

int Frames::getPoints()
{
	return this->points;
}

std::string Frames::getMeshRect()
{
	return this->meshRect;
}

std::string Frames::getMeshRhomb()
{
	return this->meshRhomb;
}



// setters
void Frames::setPosition(glm::vec2 position)
{
	this->position = position;
}

void Frames::setColor(glm::vec3 color)
{
	this->color = color;
}

void Frames::setLength(float length)
{
	this->length = length;
}

void Frames::setPoints(int points)
{
	this->points = points;
}

void Frames::setMeshRect(std::string meshRect)
{
	this->meshRect = meshRect;
}

void Frames::setMeshRhomb(std::string meshRhomb)
{
	this->meshRhomb = meshRhomb;
}

Frames* Frames::detectFrame(glm::vec2 mousePos) {
	if (mousePos.x >= this->position.x - this->length / 2 &&
		mousePos.x <= this->position.x + this->length / 2 &&
		mousePos.y >= this->position.y - this->length / 2 &&
		mousePos.y <= this->position.y + this->length / 2) {
		return this;
	}
	return NULL;
}
