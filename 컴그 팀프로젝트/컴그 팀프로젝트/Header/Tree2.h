#pragma once
#include"Init.h"
class Tree2
{

	
		GLuint vao, vbo[3], ebo;

		float* vPosData;
		float* vNormalData;
		float* vTextureCoordinateData;
		int* indexData;
		int vertexCount;
		int indexCount;

		int width, height, nrChannels;
		unsigned int texture;
		//변환행렬
		glm::mat4 S = glm::mat4(1.0f);
		glm::mat4 T = glm::mat4(1.0f);
		glm::mat4 STR = glm::mat4(1.0f);

public:

		void Init(const GLuint s_program);
		void Draw();
		void DrawSideTree(unsigned int modelocation,float chp,int i, float side);

};

