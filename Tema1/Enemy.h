#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Enemy
	{
	public:
		Enemy();
		~Enemy();

		bool killed;
		bool detectCollision(glm::vec2 point, float radius);

		// getters
		glm::vec2 getEnemyCenter();
		bool getRendered();
		float getRadiusEnemy();
		float getScaleEnemy();
		float getScaleInt();
		std::string getEnemyMesh();
		float getLine();
		int getHits();

		// setters
		void setEnemyCenter(glm::vec2 center);
		void setRendered(bool rendered);
		void setRadiusEnemy(float radius);
		void setScaleEnemy(float scaleEnemy);
		void setScaleInt(float scaleInt);
		void setEnemyMesh(std::string enemyMesh);
		void setLine(float line);
		void setHits(int hits);
		
	private:
		glm::vec2 enemyCenter;

		float radiusEnemy;
		float scaleEnemy;
		float scaleInt;

		bool rendered;
		std::string enemyMesh;
		float line;
		int hits;
	};
}