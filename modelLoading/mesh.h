#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/glm/matrix_transform.hpp>

#include "shader_m.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	string type;
	string path; // store path of texture to compare with other textures
};
class Mesh {
	public: 
		// Mesh Data 
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;
		// Functions 
		// Constructor for giving mesh all necessary data
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures; 
			
			setupMesh();
		}
		// Drawing mesh 
		void Draw(Shader shader)
		{
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for(unsigned int i = 0; i < textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding 
				// retrieve number of textures
				string number;
				string name = textures[i].type;
				if(name == "texture_diffuse") 
					number = std::to_string(diffuseNr++);
				else if(name == "texture_specular")
					number = std::to_string(specularNr++);
				shader.setFloat(("material." + name + number).c_str(), i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
			glActivateTexture(GL_TEXTURE0);
			// draw mesh 
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0); 	
		}
	private: 
		// Render data 
		unsigned int VAO, VBO, EBO;
		// Functions 
		// Initialize buffers 
		void setupMesh() 
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
			
			glBindVertexArray(VAO);
			glBindBufer(GL_ARRAY_BUFFER, VBO);
			
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),	&vertices[0], GL_STATIC_DRAW);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); 

			// vertex positions 
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			// vertex normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
			// vertex texture coords
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

			glBindVertexArray(0);
		}
}
