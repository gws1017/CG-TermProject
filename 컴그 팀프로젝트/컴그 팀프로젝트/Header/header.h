#pragma once
#pragma warning(disable:4996)
//�⺻���
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

using namespace std;
//�ܺ����


//opengl ���
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//����

#define WIDTH 1000  //������ ����
#define HEIGHT 1000  //������ ����
#define STB_IMAGE_IMPLEMENTATION
#define FRUIT_MAX 5
#define SYSTEM_FRUIT_MAX 9

enum class CType //���� Ÿ��
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
	bool bDraw = false; // �׷ȴ��� �ȱ׷ȴ��� üũ
	CType color;
};
