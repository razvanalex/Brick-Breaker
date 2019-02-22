#pragma once

#include "Object2D.h"

#include <vector>
#include <string>

#include <Core/Engine.h>

/*
	Square is an Object2D used to draw a square. It has properties like color, 
	or is filled.
*/
class Square : public Object2D {
	public: 
		Square(std::string name, glm::vec3 color, glm::mat3 modelMatrix, bool fill);
		~Square();

	private:
		bool fill;
		glm::vec3 color;

	public:
		bool IsFill();
		void SetColor(glm::vec3 color);
		glm::vec3 GetColor();
};