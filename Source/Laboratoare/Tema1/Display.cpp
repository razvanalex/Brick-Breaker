#include "Display.h"

/*
	This function computes the logic space to viewport space transformation.
	This is uniformly done, so resizing the window, will not stretch to fit 
	the window. We want that the image be the same on every display, as movies 
	are. This function is from Laborator 3.
*/
glm::mat3 Display::LogicToViewportTransformation(LogicSpace *lSpace, 
	ViewportSpace *vSpace) 
{
	float sx, sy, tx, ty, smin;
	sx = vSpace->width / (float)lSpace->width;
	sy = vSpace->height / (float)lSpace->height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;

	tx = vSpace->x - smin * lSpace->x + 
		(vSpace->width - smin * lSpace->width) / 2;
	ty = vSpace->y - smin * lSpace->y + 
		(vSpace->height - smin * lSpace->height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

/*
	This function sets the viewport area. This function is from Laborator 3
	and adapted for my camera.
*/
void Display::SetViewportArea(Camera &camera, 
	ViewportSpace &vSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(vSpace.x, vSpace.y, vSpace.width, vSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(vSpace.x, vSpace.y, vSpace.width, vSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	camera.SetOrthographic(
		(float)vSpace.x,
		(float)(vSpace.x + vSpace.width),
		(float)vSpace.y,
		(float)(vSpace.y + vSpace.height),
		0.1f, 400);
}

/*
	This function renders the model onto the screen. It's taken from Laborator 5
	and adapted for my camera.
*/
void Display::RenderMesh(Mesh * mesh, Shader * shader, 
	const glm::mat4 & modelMatrix, Camera * camera)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE,
		glm::value_ptr(camera->GetViewMatrix()));

	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, 
		glm::value_ptr(camera->GetProjectionMatrix()));

	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE,
		glm::value_ptr(modelMatrix));

	mesh->Render();
}