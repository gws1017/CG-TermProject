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

void Tree2::DrawSideTree(unsigned int modelocation, float chp, int i, float side)
{
	T = glm::translate(glm::mat4(1.0f), glm::vec3(side + (chp), 1.3, -10.0 + i));
	S = scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
	STR = T * S;
	glUniformMatrix4fv(modelocation, 1, GL_FALSE, glm::value_ptr(STR));
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
