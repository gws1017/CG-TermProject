#pragma once
#define SYSTEM_FRUIT_MAX 9
#include"Header/Init.h"
enum class CType //색깔 타입
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
	bool bDraw = false; // 그렸는지 안그렸는지 체크
	CType color;
	GLUquadricObj* qobj; //안에 넣어주면됩니다
public:
	glm::mat4 T = glm::mat4(1.0f);

	void Draw(unsigned int modellocation, unsigned int vColorLocation);
	void Create(bool draw, float Red, float Green, float Blue, CType Color);
	void Remove(bool draw);


};

