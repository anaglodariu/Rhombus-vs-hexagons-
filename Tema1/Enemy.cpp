#include "Enemy.h"

using namespace std;
using namespace m1;

Enemy::Enemy()
{
	this->radiusEnemy = 50;
	this->scaleEnemy = this->radiusEnemy;	
	this->scaleInt = 35;
	this->rendered = true;
	this->hits = 0;
	killed = false;
}

Enemy::~Enemy()
{
}

bool Enemy::detectCollision(glm::vec2 point, float radius)
{
	float distance = glm::distance(this->enemyCenter, point);
	if (distance < this->radiusEnemy + radius)
		return true; // detected collision
	return false;
}

// getters
glm::vec2 Enemy::getEnemyCenter()
{
	return this->enemyCenter;
}

bool Enemy::getRendered()
{
	return this->rendered;
}

float Enemy::getRadiusEnemy()
{
	return this->radiusEnemy;
}

float Enemy::getScaleEnemy()
{
	return this->scaleEnemy;
}

float Enemy::getScaleInt()
{
	return this->scaleInt;
}

std::string Enemy::getEnemyMesh()
{
	return this->enemyMesh;
}

float Enemy::getLine()
{
	return this->line;
}

int Enemy::getHits()
{
	return this->hits;
}

// setters
void Enemy::setEnemyMesh(string mesh)
{
	this->enemyMesh = mesh;
}

void Enemy::setEnemyCenter(glm::vec2 center)
{
	this->enemyCenter = center;
}

void Enemy::setRendered(bool rendered)
{
	this->rendered = rendered;
}

void Enemy::setRadiusEnemy(float radius)
{
	this->radiusEnemy = radius;
}

void Enemy::setScaleEnemy(float scaleEnemy)
{
	this->scaleEnemy = scaleEnemy;
}

void Enemy::setScaleInt(float scaleInt)
{
	this->scaleInt = scaleInt;
}


void Enemy::setLine(float line)
{
	this->line = line;
}

void Enemy::setHits(int hits)
{
	this->hits = hits;
}