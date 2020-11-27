#include "Tree1.h"

void Tree1::Init(const GLuint s_program)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/tree.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/tree.png");
}

void Tree1::Draw()
{

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
