
#include "Tree.h"

void Tree::Init(const GLuint s_program)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/tree.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/tree.png");
}

void Tree::Draw()
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(World * R * S1));
	glDrawArrays(GL_TRIANGLES, 0, indexCount);
}
