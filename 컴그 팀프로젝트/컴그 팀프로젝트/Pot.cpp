#include "Header/Pot.h"
#include "Header/Function.h"

void Pot::Init(const GLuint s_program) //각종 초기화는 여기서 합시다(변하지 않는 변수만)
{
	InitBuffer(vao, vbo, ebo, s_program, "Resource/potB.obj", vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, "Resource/pot.png");

	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.0, 2.0));
	S = scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));

	SWT = glm::translate(SWT, glm::vec3(PHEIGHT, 0.0f, 0.0f));
	SWT2 = glm::translate(SWT2, glm::vec3(-PHEIGHT, 0.0f, 0.0f));
	
}

void Pot::Swing() //스윙 애니메이션 함수
{
	if (SWRa >= 20.0f || SWRa <= -20.0f) delta_SW *= -1;
	
	if (SWRa == 0.0f)
	{
		SWT = glm::mat4(1.0f);
		SWT2 = glm::mat4(1.0f);
		
		SWT = glm::translate(SWT, glm::vec3(delta_SW * PHEIGHT, 0.0f, 0.0f));
		SWT2 = glm::translate(SWT2, glm::vec3(-delta_SW * PHEIGHT, 0.0f, 0.0f));
	}

	SWRa += delta_SW * SPEED;

	SWR = glm::mat4(1.0f);

	SWR = glm::rotate(SWR, glm::radians(SWRa), glm::vec3(0.0f, 0.0f, 1.0f));
	
	
}

void Pot::Draw(const unsigned int modelLocation, const unsigned int vColorLocation)
{
	SW = SWT2 * SWR * SWT;

	POT = T * SW * S;
	
	//glUniform3f(vColorLocation, NCV(50), NCV(50), NCV(50));
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(POT));
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
