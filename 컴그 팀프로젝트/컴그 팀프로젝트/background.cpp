#include "Header/background.h"
#include "Header/Init.h"

void Background::Init(const GLuint s_program) //각종 초기화는 여기서 합시다(변하지 않는 변수만)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/sphere.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/sky.png");
	float bg_size = 0.5f;
	S = glm::scale(S, glm::vec3(bg_size, bg_size, bg_size));
	T = glm::translate(T, glm::vec3(0.0f, -1.0f, 0.0f));
}

void Background::Draw(const unsigned int modelLocation)
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T*S));
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}