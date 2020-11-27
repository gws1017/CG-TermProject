#include "Pot.h"
#include "Function.h"
void Pot::Init(const GLuint s_program)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/pot.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 2.0));
	S = scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));
}

void Pot::Draw(const unsigned int modelLocation, const unsigned int vColorLocation)
{
	
	POT = T * S;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(POT));
	glUniform3f(vColorLocation, NCV(50), NCV(50), NCV(50));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
