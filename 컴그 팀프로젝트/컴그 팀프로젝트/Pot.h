#pragma once
#include"Header/Init.h"
class Pot
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
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 POT = glm::mat4(1.0f); //냄비의 이동 신축 회전을 포함하는 행렬
public:

	void Init(const GLuint s_program);
	void Draw(const unsigned int modelLocation, const unsigned int vColorLocation);
};

