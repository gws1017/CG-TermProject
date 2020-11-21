#include "Header/Init.h"
#include "Header/ReadObj.h"
#include "Header/stb_image.h"

void InitBuffer(GLuint&vao, GLuint vbo[], GLuint& ebo, const GLuint s_program, const char* Filename, float*& vPosData, float*& vNormalData, float*& vTextureCoordinateData, int*& indexData, int& vertexCount, int& indexCount)
{
	ReadObj(Filename, vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);//OBJ파일 읽기

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //정점데이터 바인드
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vPosData, GL_STATIC_DRAW);
	int posLocation = glGetAttribLocation(s_program, "in_Position");
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
	glEnableVertexAttribArray(posLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); //노멀데이터 바인드
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vNormalData, GL_STATIC_DRAW);
	int normalLocation = glGetAttribLocation(s_program, "in_Normal");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]); //텍스처데이터 바인드
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 2, vTextureCoordinateData, GL_STATIC_DRAW);
	int uvLocation = glGetAttribLocation(s_program, "in_uv");
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(uvLocation);



	glGenBuffers(1, &ebo); //EBO인덱스 바인드
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(int), indexData, GL_STATIC_DRAW);
}

void InitTexture(unsigned int& texture, int& width, int& height, int& nrChannels, const GLuint s_program, const char* Filename)
{
	glGenTextures(1, &texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(Filename, &width, &height, &nrChannels, 0); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	if (nrChannels == 3) glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의
	else if (nrChannels == 4) glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의
	glUseProgram(s_program);
	int tLocation = glGetUniformLocation(s_program, "outTexture"); //--- outTexture 유니폼 샘플러의 위치를 가져옴
	glUniform1i(tLocation, 0); //--- 샘플러를 0번 유닛으로 설정
}