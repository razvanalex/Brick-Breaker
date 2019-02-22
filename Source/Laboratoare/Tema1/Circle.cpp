#include "Circle.h"

/*
	Creates a circle. This method uses Gl_LINE_LOOP for non-filled objects
	and GL_TRIANGLE_FAN for a filled object. This creates vertices in 
	circle and then joins each vertex to create the desired object.
	An unit circle is described as: x(t) = cos(t) and y(t) = sin(t), for any 
	t between 0 and 2 * PI.
*/
Circle::Circle(std::string name, glm::vec3 color, glm::mat3 modelMatrix,
	bool fill) : Object2D(name, modelMatrix)
{
	const float twoPI = 2.0f * glm::pi<float>();
	float step = twoPI / (float)this->numSides;

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	// Set vertices
	for (float i = 0; i < 2 * glm::pi<float>(); i += step)
		vertices.push_back(VertexFormat(glm::vec3(cos(i), sin(i), 1), color));

	// Set indices
	for (int i = 0; i < numSides; i++)
		indices.push_back((unsigned int)i);

	// Set draw mode 
	if (!fill)
		this->SetDrawMode(GL_LINE_LOOP);
	else
		this->SetDrawMode(GL_TRIANGLE_FAN);

	// Set attributes
	this->color = color;
	this->SetVertices(vertices);
	this->SetIndices(indices);
}

/*
	Destructor for circle
*/
Circle::~Circle()
{
}

/*
	Getter for isFill.
*/
bool Circle::IsFill()
{
	return this->fill;
}

/*
	Setter for color. May by used before adding it to meshes.
*/
void Circle::SetColor(glm::vec3 color)
{
	this->color = color;

	std::vector<VertexFormat> vertices = this->GetVertices();
	for (VertexFormat v : vertices) {
		v.color = color;
	}
}

/*
	Getter for color.
*/
glm::vec3 Circle::GetColor()
{
	return this->color;
}

