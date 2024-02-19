#pragma once

#include "components/simple_scene.h"
#include "RhombusRect.h"
#include "Stars.h"

namespace m1
{
	class Square
	{

	private:
		glm::vec2 position;
		float length;
		bool empty;
		RhombusRect* rhombusRect;
		bool shoot;
		std::string starMeshName;
		float radiusRhombus;
		
	public:
		Square();
		~Square();

		Square* detectSquare(glm::vec2 mousePos);

		// getters
		glm::vec2 getPosition();
		float getLength();
		bool getEmpty();
		RhombusRect* getRhombusRect();
		bool getShoot();
		std::string getStarMeshName();
		float getRadiusRhombus();
		

		// setters
		void setPosition(glm::vec2 position);
		void setLength(float length);
		void setEmpty(bool empty);
		void setRhombusRect(RhombusRect* rhombusRect);
		void setShoot(bool shoot);
		void setStarMeshName(std::string starMeshName);
		void setRadiusRhombus(float radiusRhombus);

		std::list<Star> stars;
		float contorTime;
	};
}