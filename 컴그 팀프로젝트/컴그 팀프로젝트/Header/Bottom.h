#pragma once
#include "Init.h"

class Bottom {

	GLuint vao, vbo[3],ebo;

	//정점 정보
	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	//텍스처 정보
	int width, height, nrChannels;
	unsigned int texture;

	//변환 행렬
	glm::mat4 S = glm::mat4(1.0f); 
	glm::mat4 BOT = glm::mat4(1.0f); // 바닥의 신축 이동 회전을 포함하는 행렬
public:

	void Init(const GLuint s_program);
	void Draw(const unsigned int modelLocation);
};
