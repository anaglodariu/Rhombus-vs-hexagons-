#pragma once

#include "components/simple_scene.h"

namespace m1
{
	class Star
	{
	public:
		Star();
		~Star();

		bool pickStar(glm::vec2 mousePosition);

		// getters
		std::string getMeshStarName();
		glm::vec2 getStarCenter();
		float getStarRadius();
		float getAngularStep();

		// setters
		void setMeshStarName(std::string meshStarName);
		void setStarCenter(glm::vec2 starCenter);
		void setStarRadius(float starRadius);
		void setAngularStep(float angularStep);

	private:
		std::string meshStarName;
		glm::vec2 starCenter;
		float starRadius;
		float angularStep;

	};
}