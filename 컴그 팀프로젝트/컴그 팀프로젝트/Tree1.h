#pragma once
#include"Header/Init.h"
class Tree1
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

	//��ȯ ���
public:

	void Init(const GLuint s_program);
	void Draw();
};

