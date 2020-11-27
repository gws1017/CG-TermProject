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

public:

		void Init(const GLuint s_program);
		void Draw();

};

