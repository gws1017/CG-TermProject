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

	
	char* Filename, *Texturename; //�����̸�, �ؽ�ó�����̸�
	char* name; //���ϸ� �̸�
	int nsize; //���ϸ� �̸� ����

	//�� ��ȯ���
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 PKM = glm::mat4(1.0f); //������ �̵� ���� ȸ���� �����ϴ� ���
public:

	// ������ ���ϸ� ������ �̸��� �����ּ���
	Pokemon(const char* n); 
	//�Ҹ���
	~Pokemon();
	void Init(const GLuint s_program);
	//���ϸ� �̸������� �� ��ȯ�� �ٸ��� �ʱ�ȭ ���ִ� �Լ�
	void Has_PokemonTRS();
	void Draw(const unsigned int modelLocation);


};

