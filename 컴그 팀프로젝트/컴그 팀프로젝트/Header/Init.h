#pragma once
#include "header.h"


//OBJ를 읽고 바인딩해주는 함수
void InitBuffer(GLuint& vao, GLuint vbo[], GLuint& ebo, const GLuint s_program, const char* Filename, float*& vPosData, float*& vNormalData, float*& vTextureCoordinateData, int*& indexData, int& vertexCount, int& indexCount);

//텍스쳐를 바인딩 해주는 함수
void InitTexture(unsigned int& texture, int& width, int& height, int& nrChannels, const GLuint s_program, const char* Filename);
