#include "Camera.h"

/*
	Construct a camera, and set posstion, center and vector up.
*/
Camera::Camera(const glm::vec3 &position, const glm::vec3 &center,
	const glm::vec3 &up)
{
	Set(position, center, up);
}

/*
	Destructor for camera
*/
Camera::~Camera()
{ 
}

/*
	Update the properties of camera
*/
void Camera::Set(const glm::vec3 &position, const glm::vec3 &center, 
	const glm::vec3 &up)
{
	this->position = position;
	forward = glm::normalize(center - position);
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward);
}

/*
	Returns the View Matrix
*/
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + forward, up);
}

/*
	Getter for targetPosition
*/
glm::vec3 Camera::GetTargetPosition()
{
	return position + forward * distanceToTarget;
}

/*
	Set an orthographic projection
*/
void Camera::SetOrthographic(float left, float right, float bottom, float top, 
	float zNear, float zFar)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
}

/*
	Getter for projection matrix
*/
glm::mat4 Camera::GetProjectionMatrix()
{
	return this->projectionMatrix;
}
