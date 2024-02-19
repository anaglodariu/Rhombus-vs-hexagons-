#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Frames
	{
	private:
		glm::vec2 position;
		glm::vec3 color;
		float length;
		int points;
		std::string meshRect;
		std::string meshRhomb;

	public:
		Frames();
		~Frames();

		Frames* detectFrame(glm::vec2 mousePos);

		// getters
		glm::vec2 getPosition();
		glm::vec3 getColor();
		float getLength();
		int getPoints();
		std::string getMeshRect();
		std::string getMeshRhomb();

		// setters
		void setPosition(glm::vec2 position);
		void setColor(glm::vec3 color);
		void setLength(float length);
		void setPoints(int points);
		void setMeshRect(std::string meshRect);
		void setMeshRhomb(std::string meshRhomb);

	
	
	};
}