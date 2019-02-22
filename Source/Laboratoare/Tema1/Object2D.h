#pragma once

#include <vector>
#include <string>

#include <Core/Engine.h>

/*
	This is a primitive used to draw any object on the screen. It contains
	the indices, the vertices, the name of the object and the model matrix.
*/
class Object2D 
{
	public:
		Object2D(std::string name, std::vector<VertexFormat> vertices,
				std::vector<unsigned short> indices,
				glm::mat3 modelMatrix);
		Object2D(std::string name, glm::mat3 modelMatrix);
		~Object2D();

	private:
		std::string name;
		std::vector<VertexFormat> vertices;
		std::vector<unsigned short> indices;
		unsigned int drawMode;
		glm::mat3 modelMatrix;

	protected:
		void SetVertices(std::vector<VertexFormat> vertices);
		void SetIndices(std::vector<unsigned short> indices);
		std::vector<VertexFormat> GetVertices();
		std::vector<unsigned short> SetIndices();

	public:
		Mesh* CreateMesh();
		Mesh* CreateMeshEngine();
		void SetDrawMode(unsigned int primitive);
		std::string GetName();
		glm::mat3 GetModelMatrix();
		void SetModelMatrix(glm::mat3 modelMatrix);
		void ApplyTranformation(glm::mat3 modelMatrix);
};