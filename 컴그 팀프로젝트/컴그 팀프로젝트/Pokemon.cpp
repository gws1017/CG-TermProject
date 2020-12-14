#include "Header/Pokemon.h"
#include "Header/Function.h"
#include "Header/Init.h"

 Pokemon::Pokemon(const char* n) 
	 :nsize(strlen(n))
{
	 name = new char[nsize];
	 strcpy(name, n);
}
 Pokemon::~Pokemon()
 {
	 Filename = NULL;
	 Texturename = NULL;
	 name = NULL;

	 delete[] Filename;
	 delete[] Texturename;
	 delete[] name;
 }

 //get, set ÇÔ¼ö

 int Pokemon::Get_Act_Type()
 {
	 return Act_Type;
 }

 int Pokemon::Get_PosX()
 {
	 return pos.x;
 }
 int Pokemon::Get_PosZ()
 {
	 return pos.z;
 }

 float Pokemon::Get_p_height() {
	 return p_height;
 }


 void Pokemon::Set_Pos(float x, float y, float z)
 {
	 pos.x = x;
	 pos.y = y;
	 pos.z = z;
 }


void Pokemon::Init(const GLuint s_program)
{

	MakeFileName(Filename, nsize, name, "Resource/", ".obj");
	MakeFileName(Texturename, nsize, name, "Resource/", ".png");

	InitBuffer(vao, vbo, ebo, s_program, Filename, vPosData, vNormalData, vTextureCoordinateData, indexData, vertexCount, indexCount);
	InitTexture(texture, width, height, nrChannels, s_program, Texturename);

	Has_Pokemon();

	SWT = glm::translate(SWT, glm::vec3(p_height, 0.0f, 0.0f));
	SWT2 = glm::translate(SWT2, glm::vec3(-p_height, 0.0f, 0.0f));
	
}

void Pokemon::Jump()
{
	JMP = glm::mat4(1.0f);

	if (jmpy >= 0.1f) delta_jy *= -1;
	else if(jmpy < 0.0f) delta_jy *= -1;
	
	jmpy += delta_jy*0.01f;

	JMP = glm::translate(JMP, glm::vec3(0.0f, jmpy, 0.0f));
}

void Pokemon::Jump2()
{
	JMP = glm::mat4(1.0f);

	if (jmpy >= 0.1f) delta_jy *= -1;
	else if (jmpy < 0.0f) delta_jy = 0;

	if (delta_jy == 0) jumptimer += 1;
	if (jumptimer >= 50)
	{
		delta_jy = 1;
		jumptimer = 0;
	}

	jmpy += delta_jy * 0.01f;

	JMP = glm::translate(JMP, glm::vec3(0.0f, jmpy, 0.0f));
}

void Pokemon::Swing()
{
	if (SWRa >= 10.0f || SWRa <= -10.0f) delta_SW *= -1;

	if (SWRa == 0.0f)
	{
		SWT = glm::mat4(1.0f);
		SWT2 = glm::mat4(1.0f);

		SWT = glm::translate(SWT, glm::vec3(delta_SW * p_height, 0.0f, 0.0f));
		SWT2 = glm::translate(SWT2, glm::vec3(-delta_SW * p_height, 0.0f, 0.0f));
	}

	SWRa += delta_SW * sw_speed;

	SWR = glm::mat4(1.0f);

	SWR = glm::rotate(SWR, glm::radians(SWRa), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Pokemon::Rotate() {

	ROT = glm::rotate(ROT, glm::radians(10.0f),glm::vec3(0.0f,1.0f,0.0f));
}

void Pokemon::Float(float _h)
{
	float h = 0.1f;
	if (_h != 0) h = _h;
	FLO = glm::mat4(1.0f);

	if (floy >= h || floy < -h) delta_fy *= -1;
	floy += delta_fy * 0.015f;

	FLO = glm::translate(FLO,glm::vec3(0.0f,floy , 0.0f));
	
}

void Pokemon::Tornado()
{
	Float(0.3f);
	Rotate();
}

void Pokemon::Draw(const unsigned int modelLocation)
{
	SW = SWT2 * SWR * SWT;
	PKM = FLO * JMP * T * PT * SW * ROT * R * S;

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(PKM));
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Pokemon::Has_Pokemon()
{
	uniform_int_distribution<int> uid(0,2),uid2(3,5);
	random_device rd;
	mt19937 mt(rd());

	float size = 2.0f;

	// Á¡ÇÁ Á¡ÇÁ2 ½ºÀ®
	if (strcmp(name, "balchang") == 0)
	{
		S = glm::scale(S, glm::vec3(0.015f*size, 0.015f*size, 0.015f*size));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -8.0f));
		p_height = 0.05f;
		Act_Type = uid(mt);
	}
	// Á¡ÇÁ Á¡ÇÁ2 ½ºÀ®
	else if (strcmp(name, "picachu") == 0)
	{
		S = glm::scale(S, glm::vec3(0.01f*size, 0.01f*size, 0.01f*size));
		R = glm::rotate(R, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -7.0f));
		p_height = 0.06f;
		Act_Type = uid(mt);
	}

	// µÕµÕ
	else if (strcmp(name, "gong") == 0)
	{
		S = glm::scale(S, glm::vec3(0.01f*size, 0.01f*size, 0.01f*size));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.15f, -7.0f));
		p_height = 0.05f;
		Act_Type = 3;
	}
	// Á¡ÇÁ Á¡ÇÁ2 ½ºÀ®
	else if (strcmp(name, "pang") == 0)
	{
		S = glm::scale(S, glm::vec3(0.013f*size, 0.013f*size, 0.013f*size));
		R = glm::rotate(R, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.05f, -7.0f));
		p_height = 0.1f;
		Act_Type = uid(mt);
	}

	//µÕµÕ Åä³×ÀÌµµ È¸Àü
	else if (strcmp(name, "coil") == 0)
	{
		S = glm::scale(S, glm::vec3(0.005f*size, 0.005f*size, 0.005f*size));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.3f, -7.0f));
		p_height = 0.03f;
		Act_Type = uid2(mt);
	}
	else if (strcmp(name, "phantom") == 0)
	{
		S = glm::scale(S, glm::vec3(0.005f*size, 0.005f*size, 0.005f*size));
		R = glm::rotate(R, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		T = glm::translate(T, glm::vec3(0.0f, 1.3f, -7.0f));
		p_height = 0.03f;
		Act_Type = 3;
	}
}

void Pokemon::Update_Pos() {

	PT = glm::translate(PT,pos);
}
