#pragma once
#include"Init.h"

#define PHEIGHT 1.3f
#define SPEED 5.0f

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

	float SWRa = 0.0f; // 스윙각도 변수
	int delta_SWT = 1, delta_SW = 1; // 스윙변화량 제어 변수
	int PotCount = 0;
	

	//변환행렬
	glm::mat4 SW = glm::mat4(1.0f);   //냄비 흔들림 행렬
	glm::mat4 SWT = glm::mat4(1.0f);  //냄비 회전축을 왼쪽으로 이동행렬
	glm::mat4 SWT2 = glm::mat4(1.0f); //냄비 회전축을 원위치시키는 이동행렬
	glm::mat4 SWR = glm::mat4(1.0f);  //냄비 흔들림 회전 행렬Rz

	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 POT = glm::mat4(1.0f); //냄비의 이동 신축 회전을 포함하는 행렬

public:

	bool potswingTimer = false;

	int Get_potcount();

	void Init(const GLuint s_program);
	void Swing(int r, int g, int b, GLuint s_program); // 솥이 흔들리는 애니메이션
	void Draw(const unsigned int modelLocation, const unsigned int vColorLocation);
};

