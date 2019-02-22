#pragma once
#include "Square.h"
#include "Transform2D.h"

#include <string>

/*
	Paddle is a square that is scaled, resulting in a rectangle. The paddle is 
	used to deploy the ball and to bounce it when the ball hits the paddle.
*/
class Paddle : public Square {
	public: 
		Paddle(std::string name, unsigned int width, 
			unsigned int height, float x, float y,
			glm::vec3 color);
		~Paddle();

	private: 
		unsigned int width;
		unsigned int height;
		glm::vec2 position;

		void updateModelMatrix();

	public:
		unsigned int GetWidth();
		unsigned int GetHeight();
		glm::vec2 GetSize();
		glm::vec2 GetPosition();

		void Update(glm::vec2 mousePosition);
};