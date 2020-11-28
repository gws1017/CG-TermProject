#pragma once
#pragma warning(disable:4996)
//기본헤더
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;
//외부헤더


//opengl 헤더
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//정의

#define WIDTH 1000  //윈도우 가로
#define HEIGHT 1000  //윈도우 세로
#define STB_IMAGE_IMPLEMENTATION
#define FRUIT_MAX 5
#define SYSTEM_FRUIT_MAX 9

enum class CType //색깔 타입
{
	NONE,
	RED,
	GREEN,
	BLUE
};

struct Fruit
{
	float x, y, z;
	float r, g, b;
	bool bDraw = false; // 그렸는지 안그렸는지 체크
	CType color;
};
