#include "Header/Bottom.h"

void Bottom::Init(const GLuint s_program)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/Bottom.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/Bottom.png");
	S = glm::scale(S, glm::vec3(0.5, 0.5, 0.5));
}

void Bottom::Draw(const unsigned int modelLocation)
{
	
	BOT = S;
	
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(BOT));
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}



