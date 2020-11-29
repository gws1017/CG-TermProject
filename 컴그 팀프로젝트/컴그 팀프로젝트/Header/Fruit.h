#pragma once
#define SYSTEM_FRUIT_MAX 9
#include"Header/Init.h"
enum class CType //���� Ÿ��
{
	NONE,
	RED,
	GREEN,
	BLUE
};



class Fruit
{
public:
	float x, y, z;
	float r, g, b;
	bool bDraw = false; // �׷ȴ��� �ȱ׷ȴ��� üũ
	CType color;
	
public:
	glm::mat4 T = glm::mat4(1.0f);

	void Draw(unsigned int modellocation,GLUquadricObj* qobj);
	void Create(bool draw, float Red, float Green, float Blue, CType Color);
	void Remove(bool draw);


};

