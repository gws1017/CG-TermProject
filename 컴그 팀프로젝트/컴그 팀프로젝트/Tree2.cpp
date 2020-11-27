#include "Header/Tree2.h"

void Tree2::Init(const GLuint s_program)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/tree2.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/tree2.png");
}

void Tree2::Draw()
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
