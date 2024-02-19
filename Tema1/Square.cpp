#include "Square.h"

using namespace std;
using namespace m1;

Square::Square()
{
	this->empty = true;
	this->shoot = false;
	contorTime = 0;
}

Square::~Square()
{
}

// getters
glm::vec2 Square::getPosition()
{
	return this->position;
}

float Square::getLength()
{
	return this->length;
}

bool Square::getEmpty()
{
	return this->empty;
}

RhombusRect* Square::getRhombusRect()
{
	return this->rhombusRect;
}

bool Square::getShoot()
{
	return this->shoot;
}

float Square::getRadiusRhombus()
{
	return this->radiusRhombus;
}

std::string Square::getStarMeshName()
{
	return this->starMeshName;
}


// setters

void Square::setPosition(glm::vec2 position)
{
	this->position = position;
}

void Square::setLength(float length)
{
	this->length = length;
}

void Square::setEmpty(bool empty)
{
	this->empty = empty;
}

void Square::setRhombusRect(RhombusRect* rhombusRect)
{
	this->rhombusRect = rhombusRect;
}

Square* Square::detectSquare(glm::vec2 mousePos)
{
	if (mousePos.x > this->position.x - this->length / 2 && 
		mousePos.x < this->position.x + this->length / 2 &&
		mousePos.y > this->position.y - this->length / 2  &&
		mousePos.y < this->position.y + this->length / 2) {
		return this;
	}
	return NULL;
}

void Square::setShoot(bool shoot)
{
	this->shoot = shoot;
}

void Square::setStarMeshName(std::string starMeshName)
{
	this->starMeshName = starMeshName;
}

void Square::setRadiusRhombus(float radiusRhombus)
{
	this->radiusRhombus = radiusRhombus;
}
