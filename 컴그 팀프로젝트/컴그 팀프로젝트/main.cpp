#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include "Tree1.h"
#include "Tree2.h"
#include "Pot.h"

//opengl 쉐이더및 콜백함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Timerfunction(int value);
void MouseInput(int button, int state, int x, int y);

//opengl 기본변수
GLuint s_program;
GLuint shaderID;
GLchar* vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;

//로케이션 변수
unsigned int flagLocation;
unsigned int vColorLocation;
unsigned int projectionLocation;
unsigned int modelLocation;
unsigned int viewLocation;
unsigned int viewposLocation;
unsigned int lightPosLocation;
unsigned int lightColorLocation;

//카메라 변수
float CamPosX = 0.0f;
float CamPosY = 5.0f;
float CamPosZ = 40.0f;

float CamXAt = 0.0f;
float CamYAt = 0.0f;
float CamZAt = 0.0f;

float cam_rotate = 0.0;
float cam_revolve = 0.0;

//열매
void make_fruitpos();

GLUquadricObj* qobj;
int fruit_xpos[20] = { 0, };
float fruit_ypos[20] = { 0.0f, };
int fruit_zpos[20] = { 0, };
bool fruitTimer = false;
bool treeTimer = false;
float treeVec = 0.5f;

float treeAngle = 0.0f;

//행렬 선언
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);


//객체 선언
Bottom b;
Tree1 t1;
Tree2 t2;
Pot p;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example1");

	glewExperimental = GL_TRUE;
	glewInit();

	glUseProgram(s_program);

	InitShader();
	//클래스 초기화------------------
	b.Init(s_program);
	t1.Init(s_program);
	t2.Init(s_program);
	p.Init(s_program);
	//-------------------

	//-----사용자 함수--------
	make_fruitpos();
	//--------------------

	//로케이션 정보
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

//콜백함수

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
	//--------------------바닥
	b.Draw(modelLocation);
	//----------------------



	//---------------------뒤에 나무들
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
		int chp;//앞뒤 간격 및 높낮이 조정
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


	//-------------------제일 큰나무
	T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0 , 6.0, -10.0 ));
	S = scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05 , 0.05));
	Rz = glm::rotate(glm::mat4(1.0f), glm::radians(treeAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	STR2 = T*Rz * S;
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR2));
	t1.Draw();
	
	//------------열매
	for (int i = 0; i < 20; ++i)
	{
		
		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)fruit_xpos[i], fruit_ypos[i], (float)fruit_zpos[i]));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
		
		gluSphere(qobj, 0.2, 20, 20);
	}
	//-------------------------------옆에 나무들

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



	//------------------------------------------------솥
	glUniform1i(flagLocation, 1);
	p.Draw(modelLocation,vColorLocation);


	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
	case'm' :
		treeTimer = !treeTimer;
		fruitTimer = !fruitTimer;
		treeAngle = 0.0f;
		break;
	case 'c':
		CamYAt += 0.5;
		CamPosY += 0.5;
		break;
	case 'C':
		CamYAt -= 0.5;
		CamPosY -= 0.5;
		break;
    case 'z':
        CamZAt += 0.5;
        CamPosZ += 0.5;
        break;
    case 'Z':
        CamZAt -= 0.5;
        CamPosZ -= 0.5;
        break;
    case 'y':
        cam_rotate += 10.0;
        break;
    case 'Y':
        cam_rotate -= 10.0;
        break;
    case 'r':
        cam_revolve += 10.0;
        break;
    case 'R':
        cam_revolve -= 10.0;
        break;
    }
	glutPostRedisplay();
}

void Timerfunction(int value)
{
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

	
	glutTimerFunc(100, Timerfunction, 1);
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
		fruit_xpos[i] =fch+i/10;
		fruit_ypos[i] = 9.0f;
	}
}
