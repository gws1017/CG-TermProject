#pragma once
#pragma warning(disable:4996)
#include "header.h"

//opengl 쉐이더함수
void make_vertexShader();
void make_fragmentShader();
char* filetobuf(char* file);
void InitShader();
