#include "Header/Pokemon.h"
#include "Header/Function.h"
#include "Header/Init.h"

 Pokemon::Pokemon(const char* n) 
	 :nsize(strlen(n))
{
	 name = new char[nsize];
	 strcpy(name, n);
}
 Pokemon::~Pokemon()
 {
	 Filename = NULL;
	 Texturename = NULL;
	 name = NULL;

	 delete[] Filename;
	 delete[] Texturename;
	 delete[] name;
 }

void Pokemon::Init(const GLuint s_program)
{
	MakeFileName(Filename, nsize, name, "Resource/", ".obj");
	MakeFileName(Texturename, nsize, name, "Resource/", ".png");

	InitBuffer(vao, vbo, ebo, s_program, Filename, vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, Texturename);

	Has_PokemonTRS();
}

void Pokemon::Draw(const unsigned int modelLocation)
{
	PKM = T * R * S;

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(PKM));
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Pokemon::Has_PokemonTRS()
{
	if (strcmp(name, "balchang") == 0)
	{
		S = glm::scale(S, glm::vec3(0.01f, 0.01f, 0.01f));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -8.0f));
	}
	else if (strcmp(name, "picachu") == 0)
	{
		S = glm::scale(S, glm::vec3(0.01f, 0.01f, 0.01f));
		R = glm::rotate(R, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -7.0f));
	}
	else if (strcmp(name, "gong") == 0)
	{
		S = glm::scale(S, glm::vec3(0.01f, 0.01f, 0.01f));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -7.0f));
	}
	else if (strcmp(name, "pang") == 0)
	{
		S = glm::scale(S, glm::vec3(0.02f, 0.02f, 0.02f));
		R = glm::rotate(R, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -7.0f));
	}
	else if (strcmp(name, "coil") == 0)
	{
		S = glm::scale(S, glm::vec3(0.005f, 0.005f, 0.005f));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.3f, -7.0f));
	}
}