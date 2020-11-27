#pragma once
#include "header.h"


class Pokemon {

	GLuint vao, vbo[3], ebo;

	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	int width, height, nrChannels;
	unsigned int texture;

	
	char* Filename, *Texturename; //파일이름, 텍스처파일이름
	char* name; //포켓몬 이름
	int nsize; //포켓몬 이름 길이

	//모델 변환행렬
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 PKM = glm::mat4(1.0f); //냄비의 이동 신축 회전을 포함하는 행렬
public:

	// 생성자 포켓몬 생성시 이름을 적어주세요
	Pokemon(const char* n); 
	//소멸자
	~Pokemon();
	void Init(const GLuint s_program);
	//포켓몬 이름에따라 모델 변환을 다르게 초기화 해주는 함수
	void Has_PokemonTRS();
	void Draw(const unsigned int modelLocation);


};

