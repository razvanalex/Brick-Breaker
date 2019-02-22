#pragma once
#include "Object2D.h"

#include <vector>
#include <string>

#include <Core/Engine.h>

/*
	Circle class is used to draw circular objects. This class my be drived to 
	obtain the desired behaviour. 60 vertices are enought to draw a cicle even 
	on a HD screen.
*/
class Circle : public Object2D {
public:
	Circle(std::string name, glm::vec3 color, glm::mat3 modelMatrix, bool fill);
	~Circle();

private:
	bool fill;
	glm::vec3 color;
	const int numSides = 60;

public:
	bool IsFill();
	void SetColor(glm::vec3 color);
	glm::vec3 GetColor();
};