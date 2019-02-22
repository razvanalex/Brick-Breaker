#include "Square.h"

/*
	Constructor for square. It sets the vertices and indices to create a square
	using triangles (if it's filled) or loop line (if it's not filled).
*/
Square::Square(std::string name, glm::vec3 color, glm::mat3 modelMatrix, 
	bool fill) : Object2D(name, modelMatrix)
{
	this->color = color;

	// Set vertices
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, -0.5,  1), color),
		VertexFormat(glm::vec3( 0.5, -0.5,  1), color),
		VertexFormat(glm::vec3( 0.5,  0.5,  1), color),
		VertexFormat(glm::vec3(-0.5,  0.5,  1), color),
	};
	
	// Set indices
	std::vector<unsigned short> indices;

	if (!fill) {
		indices = { 0, 1, 2, 3 };
		this->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices = { 0, 1, 2, 0, 2, 3 };
		this->SetDrawMode(GL_TRIANGLES);
	}

	this->SetVertices(vertices);
	this->SetIndices(indices);
}

/*
	Destructor for square
*/
Square::~Square()
{
}

/*
	Getter for fill
*/
bool Square::IsFill()
{
	return this->fill;
}

/*
	Setter for color. Use before adding to meshes
*/
void Square::SetColor(glm::vec3 color)
{
	this->color = color;

	std::vector<VertexFormat> vertices = this->GetVertices();
	for (VertexFormat v : vertices) {
		v.color = color;
	}
}

/*
	Getter for color
*/
glm::vec3 Square::GetColor()
{
	return this->color;
}

