#include"Header/Fruit.h"


void Fruit::Draw(unsigned int modellocation, unsigned int vColorLocation)
{
	T = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	glUniformMatrix4fv(modellocation, 1, GL_FALSE, glm::value_ptr(T));
	glUniform3f(vColorLocation,r,g,b);
	if (bDraw)//객체내의 불변수가 참이면 그린다
		gluSphere(qobj, 0.2, 20, 20);
}

void Fruit::Create(bool draw, float Red, float Green, float Blue, CType Color)
{
	qobj = gluNewQuadric();
	bDraw = draw;
	r = Red;
	g = Green;
	b = Blue;
	color = Color;
}

void Fruit::Remove(bool draw)
{
	bDraw = draw;
	r =0.0f;
	g = 0.0f;
	b = 0.0f;
	color = CType::NONE;
}


