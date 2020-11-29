#include "Header/Tree1.h"

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

void Tree1::DrawBackTree(unsigned int modelocation, int i)
{
	int chp;
	if (i % 2 == 0)
		chp = -1;
	else
		chp = 1;
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 - i, 2.0, -9.0 + (chp)));
	S = scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01 * ((2 + chp)), 0.01));
	STR = T * S;
	glUniformMatrix4fv(modelocation, 1, GL_FALSE, glm::value_ptr(STR));

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Tree1::DrawBigTree(unsigned int modelocation)
{
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 6.0, -10.0));
	S = scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));
	Rz = glm::rotate(glm::mat4(1.0f), glm::radians(treeAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	STR = T * Rz * S;
	glUniformMatrix4fv(modelocation, 1, GL_FALSE, glm::value_ptr(STR));
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Tree1::DrawSideTree(unsigned int modelocation, float chp, int i, float side)
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

void Tree1::Swing()
{
	
	if (treeAngle > 5.0)
		treeVec *= -1;
	if (treeAngle < -5.0)
		treeVec *= -1;
	treeAngle += treeVec;
	Rz = glm::mat4(1.0f);

	Rz = glm::rotate(Rz, glm::radians(treeAngle), glm::vec3(0.0f, 0.0f, 1.0f));
}
