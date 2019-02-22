#pragma once
#include <include/glm.h>
#include <include/math.h>

/*
	This is a simple implementation of a camera 2D. It's inspired from Laborator 
	5. It has only the necessary things to capture a 2D image.
*/
class Camera
{
	public:
		Camera(const glm::vec3 &position, const glm::vec3 &center, 
			const glm::vec3 &up);
		~Camera();

		void Set(const glm::vec3 &position, const glm::vec3 &center, 
			const glm::vec3 &up);
		glm::mat4 GetViewMatrix();
		glm::vec3 GetTargetPosition();
		void SetOrthographic(float left, float right, float bottom, float top, 
			float zNear, float zFar);
		glm::mat4 GetProjectionMatrix();

	private:
		float distanceToTarget;
		glm::vec3 position;
		glm::vec3 forward;
		glm::vec3 right;
		glm::vec3 up;
		
		glm::mat4 projectionMatrix;

};