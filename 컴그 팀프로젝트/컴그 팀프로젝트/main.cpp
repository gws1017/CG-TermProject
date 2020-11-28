#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include "Header/Tree1.h"
#include "Header/Tree2.h"
#include "Header/Pot.h"
#include "Header/KeyBoard.h"
#include "Header/Pokemon.h"
#include "Header/PokemonManager.h"

//opengl ���̴��� �ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void MouseInput(int button, int state, int x, int y);



//opengl �⺻����
GLuint s_program;
GLuint shaderID;
GLchar* vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;

//�����̼� ����
unsigned int flagLocation;
unsigned int vColorLocation;
unsigned int projectionLocation;
unsigned int modelLocation;
unsigned int viewLocation;
unsigned int viewposLocation;
unsigned int lightPosLocation;
unsigned int lightColorLocation;

//ī�޶� ����
float CamPosX = 0.0f;
float CamPosY = 1.5f;
float CamPosZ = 5.0f;

float CamXAt = 0.0f;
float CamYAt = 0.0f;
float CamZAt = 0.0f;

float cam_rotate = 0.0;
float cam_revolve = 0.0;

//Ÿ�̸� ����
bool fruitTimer = false;
bool treeTimer = false;
bool potswingTimer = false;

//����
void make_fruitpos();

GLUquadricObj* qobj;
int fruit_xpos[20] = { 0, };
float fruit_ypos[20] = { 0.0f, };
int fruit_zpos[20] = { 0, };

float treeVec = 0.5f;

float treeAngle = 0.0f;

//��� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);


//��ü ����
Bottom b;
Tree1 t1;
Tree2 t2;
Pot p;

Pokemon_Manager pm;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("PokeMonSimulator");

	glewExperimental = GL_TRUE;
	glewInit();

	glUseProgram(s_program);

	InitShader();

	//Ŭ���� �ʱ�ȭ------------------
	b.Init(s_program);
	t1.Init(s_program);
	t2.Init(s_program);
	p.Init(s_program);
	//-------------------

	//-----����� �Լ�--------
	make_fruitpos();
	//--------------------

	//�����̼� ����
	flagLocation = glGetUniformLocation(s_program, "flag");
	vColorLocation = glGetUniformLocation(s_program, "in_Color");
	projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
	modelLocation = glGetUniformLocation(s_program, "modelTransform");
	viewLocation = glGetUniformLocation(s_program, "viewTransform");
	viewposLocation = glGetUniformLocation(s_program, "viewPos");
	lightPosLocation = glGetUniformLocation(s_program, "lightPos");
	lightColorLocation = glGetUniformLocation(s_program, "lightColor");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	
	glutTimerFunc(100, Timerfunction, 1);

	glutMainLoop();

}

//�ݹ��Լ�

GLvoid drawScene()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	qobj = gluNewQuadric();
	glm::mat4 S = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);
	glm::mat4 STR = glm::mat4(1.0f);
	glm::mat4 STR1 = glm::mat4(1.0f);
	glm::mat4 STR2 = glm::mat4(1.0f);
	glm::mat4 STR3 = glm::mat4(1.0f);
	glm::mat4 STR4 = glm::mat4(1.0f);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::vec3 cameraPos = glm::vec3(CamPosX, CamPosY, CamPosZ);
	glm::vec3 cameraDirection = glm::vec3(CamXAt, CamYAt, CamZAt);

	glm::mat4 cameraRotate(1.0f);
	cameraRotate = glm::rotate(cameraRotate, (float)glm::radians(cam_rotate), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 cameraRevolve(1.0f);
	cameraRevolve = glm::rotate(cameraRevolve, (float)glm::radians(cam_revolve), glm::vec3(0.0f, 1.0f, 0.0f));
	view = cameraRotate*lookAt(cameraPos, cameraDirection, cameraUp)*cameraRevolve;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 80.0f);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	
	glUseProgram(s_program);
	glEnable(GL_DEPTH_TEST);
	glUniform1i(flagLocation, 0);
	//--------------------�ٴ�
	b.Draw(modelLocation);
	//----------------------



	//---------------------�ڿ� ������
	for (int i = 2; i < 12; ++i)
	{
		int chp ;
		if (i % 2 == 0)
			chp = -1;
		else
			chp =1;
		T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 - i, 2.0, -9.0+(chp)));
		S = scale(glm::mat4(1.0f), glm::vec3(0.01 , 0.01*((2+chp)),  0.01));
		STR1 = T*S;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR1));
		
			t1.Draw();
		
	}
	for (int i = 2; i < 12; ++i)
	{
		int chp;//�յ� ���� �� ������ ����
		if (i % 2 == 0)
			chp = -1;
		else
			chp = 1;
		T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 + i, 2.0, -9.0 + (chp)));
		S = scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01 * ((2 + chp)), 0.01));
		STR1 = T * S;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR1));

		t1.Draw();

	}
	//----------------------------------------


	//-------------------���� ū����
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 , 6.0, -10.0 ));
	S = scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05 , 0.05));
	Rz = glm::rotate(glm::mat4(1.0f), glm::radians(treeAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	STR2 = T*Rz * S;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR2));
	t1.Draw();
	
	//------------����
	for (int i = 0; i < 20; ++i)
	{
		
		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)fruit_xpos[i], fruit_ypos[i], (float)fruit_zpos[i]));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
		
		gluSphere(qobj, 0.2, 20, 20);
	}
	//-------------------------------���� ������

	for (int i = 1; i < 23; ++i)
	{
		float chp;
		if (i % 2 == 0)
			chp = -0.7;
		else
			chp = 0.7;
		T = glm::translate(glm::mat4(1.0f), glm::vec3(-11.0+(chp), 1.3, -10.0+i));
		S = scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
		STR3 = T * S;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR3));
		if (i % 2 == 0)
			t1.Draw();
		else
			t2.Draw();

	}

	for (int i = 1; i < 23; ++i)
	{
		float chp;
		if (i % 2 == 0)
			chp = -0.7;
		else
			chp = 0.7;
		T = glm::translate(glm::mat4(1.0f), glm::vec3(11.0 - (chp), 1.3, -10.0 + i));
		S = scale(glm::mat4(1.0f), glm::vec3(0.01, 0.01, 0.01));
		
		STR3 = T * S;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR3));
		if (i % 2 == 0)
			t1.Draw();
		else
			t2.Draw();

	}
	//--------------------------------------------------
	
	pm.Draw(modelLocation);

	//------------------------------------------------��
	glUniform1i(flagLocation, 0);
	p.Draw(modelLocation,vColorLocation);
	
	
	glutSwapBuffers();
}



void Timerfunction(int value)
{
	if (potswingTimer) p.Swing();

	if (treeTimer)
	{
		treeAngle += treeVec;
		if (treeAngle > 5.0)
			treeVec *= -1;
		if (treeAngle < -5.0)
			treeVec *= -1;
	}

	if (fruitTimer)
	{
		for (int i = 0; i < 20; ++i)
		{
			fruit_ypos[i] -= (rand() % 10 + 1) * 0.1;
			if (fruit_ypos[i] <= 1.0f)
			{
				fruit_ypos[i] = 9.0f;
			}
		}
	}

	pm.Act();
	
	glutTimerFunc(10, Timerfunction, 1);
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void make_fruitpos()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		float fch = (rand() % 10 + 1) / 10+1;
		if (i % 2 == 0)
		{
			fch *= -1;
		}
		fruit_zpos[i] = -10.0 + fch;
		fruit_xpos[i] = fch+i/10;
		fruit_ypos[i] = 9.0f;
	}
}
