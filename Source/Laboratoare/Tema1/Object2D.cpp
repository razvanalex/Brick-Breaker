#include "Object2D.h"

/*
	Constructor for an onject 2d.
*/
Object2D::Object2D(std::string name, std::vector<VertexFormat> vertices,
					std::vector<unsigned short> indices,
					glm::mat3 modelMatrix)
{
	this->name = name;
	this->drawMode = GL_TRIANGLES;
	this->vertices = vertices;
	this->indices = indices;
	this->modelMatrix = modelMatrix;
}

/*
	Constructor for an object 2d.
*/
Object2D::Object2D(std::string name, glm::mat3 modelMatrix)
{
	this->name = name;
	this->modelMatrix = modelMatrix;
	this->drawMode = GL_TRIANGLES;
}

/*
	Destructor for an object 2d
*/
Object2D::~Object2D()
{
}

/*
	Setter for vertices
*/
void Object2D::SetVertices(std::vector<VertexFormat> vertices)
{
	this->vertices = vertices;
}

/*
	Setter for indices
*/
void Object2D::SetIndices(std::vector<unsigned short> indices)
{
	this->indices = indices;
}

/*
	Getter for vertices
*/
std::vector<VertexFormat> Object2D::GetVertices()
{
	return this->vertices;
}

/*
	Setter for indices
*/
std::vector<unsigned short> Object2D::SetIndices()
{
	return this->indices;
}

/*
	Create a mesh from indices and vertices. In the code, it is used only this
	function made at Laborator 2. 
*/
Mesh* Object2D::CreateMesh()
{
	// Create the VAO and bind it
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	Mesh* obj = new Mesh(this->name);

	obj->SetDrawMode(this->drawMode);
	obj->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return obj;
}

/*
	This function uses the Engine to initialize the VBOs and VAOs. It is NOT 
	used in current implementation of the game.
*/
Mesh* Object2D::CreateMeshEngine()
{
	Mesh* obj = new Mesh(this->name);

	obj->SetDrawMode(this->drawMode);
	obj->InitFromData(this->vertices, this->indices);

	return obj;
}

/*
	Set draw mode.
*/
void Object2D::SetDrawMode(unsigned int primitive)
{
	this->drawMode = primitive;
}

/*
	Getter for name
*/
std::string Object2D::GetName()
{
	return this->name;
}

/*
	Getter for model matrix
*/
glm::mat3 Object2D::GetModelMatrix()
{
	return this->modelMatrix;
}

/*
	Setter for model matrix
*/
void Object2D::SetModelMatrix(glm::mat3 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

/*
	Apply transformation to model matrix.
*/
void Object2D::ApplyTranformation(glm::mat3 transformation)
{
	this->modelMatrix *= transformation;
}

