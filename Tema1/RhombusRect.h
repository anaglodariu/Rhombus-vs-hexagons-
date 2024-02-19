#pragma once

#include "components/simple_scene.h"
#include "Stars.h"

namespace m1
{
	class RhombusRect
	{
	public:
		RhombusRect();
		~RhombusRect();

		// getters
		glm::vec3 getColor();
		glm::vec2 getRhombusCenter();
		glm::vec2 getRectCenter();
		bool getRendered();
		bool getMoving();
		bool getShrinked();
		float getRadius();
		float getScaleXRhombus();
		float getScaleYRhombus();
		float getScaleXRect();
		float getScaleYRect();
		std::string getRectMesh();
		std::string getRhombMesh();
		
		// setters
		void setColor(glm::vec3 color);
		void setRhombusCenter(glm::vec2 center);
		void setRectCenter(glm::vec2 center);
		void setRendered(bool rendered);
		void setMoving(bool moving);
		void setRadius(float radius);
		void setShrinked(bool shrinked);
		void setScaleXRhombus(float scaleXRhombus);
		void setScaleYRhombus(float scaleYRhombus);
		void setScaleXRect(float scaleXRect);
		void setScaleYRect(float scaleYRect);
		void setRectMesh(std::string rectMesh);
		void setRhombMesh(std::string rhombMesh);




		// we have to keep the center, color
	private:
		glm::vec3 color;
		glm::vec2 rhombusCenter;

		float radius;
		float scaleXRhombus;
		float scaleYRhombus;
		float scaleXRect;
		float scaleYRect;

		glm::vec2 rectCenter;
		bool rendered;
		bool moving;
		bool shrinked;
		std::string rectMesh;
		std::string rhombMesh;

		
	};
}