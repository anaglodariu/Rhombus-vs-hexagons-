#include "RhombusRect.h"

using namespace std;
using namespace m1;

RhombusRect::RhombusRect()
{
	this->scaleXRhombus = 0.3f;
	this->scaleYRhombus = 2 * this->scaleXRhombus;
	this->scaleXRect = this->scaleXRhombus * sqrt(2);
	this->scaleYRect = 0.2f;
	this->radius = this->scaleYRhombus * sqrt(2) / 2;
	this->moving = true;
	this->rendered = true;
	this->shrinked = false;
}

RhombusRect::~RhombusRect()
{
}


// getters
glm::vec3 RhombusRect::getColor()
{
	return this->color;
}

glm::vec2 RhombusRect::getRhombusCenter()
{
	return this->rhombusCenter;
}

glm::vec2 RhombusRect::getRectCenter()
{
	return this->rectCenter;

}

bool RhombusRect::getRendered()
{
	return this->rendered;
}

bool RhombusRect::getMoving()
{
	return this->moving;
}

bool RhombusRect::getShrinked()
{
	return this->shrinked;
}

float RhombusRect::getRadius()
{
	return this->radius;
}

float RhombusRect::getScaleXRhombus()
{
	return this->scaleXRhombus;
}

float RhombusRect::getScaleYRhombus()
{
	return this->scaleYRhombus;
}

float RhombusRect::getScaleXRect()
{
	return this->scaleXRect;
}

float RhombusRect::getScaleYRect()
{
	return this->scaleYRect;
}

std::string RhombusRect::getRectMesh()
{
	return this->rectMesh;
}

std::string RhombusRect::getRhombMesh()
{
	return this->rhombMesh;
}


// setters

void RhombusRect::setColor(glm::vec3 color)
{
	this->color = color;
}

void RhombusRect::setRhombusCenter(glm::vec2 center)
{
	this->rhombusCenter = center;
}

void RhombusRect::setRectCenter(glm::vec2 center)
{
	this->rectCenter = center;
}

void RhombusRect::setRendered(bool rendered)
{
	this->rendered = rendered;
}

void RhombusRect::setMoving(bool moving)
{
	this->moving = moving;
}

void RhombusRect::setShrinked(bool shrinked)
{
	this->shrinked = shrinked;
}

void RhombusRect::setRadius(float radius)
{
	this->radius = radius;
}

void RhombusRect::setScaleXRhombus(float scaleXRhombus)
{
	this->scaleXRhombus = scaleXRhombus;
}

void RhombusRect::setScaleYRhombus(float scaleYRhombus)
{
	this->scaleYRhombus = scaleYRhombus;
}

void RhombusRect::setScaleXRect(float scaleXRect)
{
	this->scaleXRect = scaleXRect;
}

void RhombusRect::setScaleYRect(float scaleYRect)
{
	this->scaleYRect = scaleYRect;
}

void RhombusRect::setRectMesh(std::string rectMesh)
{
	this->rectMesh = rectMesh;
}

void RhombusRect::setRhombMesh(std::string rhombMesh)
{
	this->rhombMesh = rhombMesh;
}