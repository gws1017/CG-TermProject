#pragma once
#pragma warning(disable:4996)
//기본헤더
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <windows.h>

//외부헤더
#include"ReadObj.h"
#include"stb_image.h"

//opengl 헤더
//양원석용
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//-------------------------

//정의

#define WIDTH 1000  //윈도우 가로
#define HEIGHT 1000  //윈도우 세로
#define STB_IMAGE_IMPLEMENTATION