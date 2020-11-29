#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include "Header/Tree1.h"
#include "Header/Tree2.h"
#include "Header/Pot.h"
#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
#include "Header/Sound.h"
#include "Header/background.h"

//opengl ���̴��� �ݹ��Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);

//-------���콺�Լ�---------
void MouseInput(int button, int state, int x, int y);
void Convert_ScreenToClipSpace(int* pInX, int* pInY,
	float* pOutX, float* pOutY);
//--------------------------

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
float CamPosY = 5.5f;
float CamPosZ =21.0f;

float CamXAt = 0.0f;
float CamYAt = 0.0f;
float CamZAt = 0.0f;

float cam_rotate = 0.0;
float cam_revolve = 0.0;
float cam_tvec = 0.05;
void make_pot_cam(); //ī�޶� ��� �ֵ� ����ֵ� ������ ���� ���� 



//Ÿ�̸� ����
bool fruitTimer = false;
bool treeTimer = false;
bool potswingTimer = false;
bool bMakePoketmon = false;// �� ���� �ý��� üũ
bool bCheckColor = false;//�÷�üũ ������ ���߱� ���� ����
//���� ��������

void Init_fruit();// ���� ���� ��ġ����� �Լ�

GLUquadricObj* qobj;
float fruit_xpos[FRUIT_MAX] = { -1.5f,-1.0f, 0.5f,1.3f,1.6 };
float fruit_ypos[FRUIT_MAX] = { 0.0f, };
float fruit_zpos[FRUIT_MAX] = { -9.0f,-8.5f,-8.3f,-8.7f,-8.0f };
float treeVec = 0.05f;
float treeAngle = 0.0f;
//------------------------------

//----���� ����------------------

CType color; // ������ Ŭ���� �������� 0:���� ,1:���� ,2:�ʷ� , 3:�Ķ�
float Red = 0.0f;
float Green = 0.0f;
float Blue = 0.0f;
bool RDraw=false; //�������� ������ �������ִ� ����
int CheckCount = 0; //�����ϴ� �� �ε��� ī��Ʈ
int RedCount = 0;   //�÷��ǰ����� �޾��ֱ����� ����
int GreenCount = 0;	//�÷��ǰ����� �޾��ֱ����� ����
int BlueCount = 0;	//�÷��ǰ����� �޾��ֱ����� ����
void check_color();//�÷� ī��Ʈ�� üũ���ִ� �Լ��� �迭�� �ѹ� ���Ƽ� ��� �÷��� ������ üũ 
//------------------------------


//��� ����
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);


//��ü ����
Bottom b;
Tree1 t1;
Tree2 t2;
Pot p;
Fruit SysFruit[9]; //���տ� ���� ��ü

Pokemon_Manager pm;
Sound sound;
Background bg;
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
	sound.Init_Sound();
	bg.Init(s_program);
	//-------------------

	//-----����� �Լ�--------
	Init_fruit();
	
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

	//��������
	FMOD_System_PlaySound(sound.soundSystem, sound.bgmSound[0], NULL, 0, &sound.Channel[0]);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseInput);
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

	

	glm::vec3 cameraPos = glm::vec3(CamPosX, CamPosY, CamPosZ);
	glm::vec3 cameraDirection = glm::vec3(CamXAt, CamYAt, CamZAt);

	glm::mat4 cameraRotate(1.0f);
	cameraRotate = glm::rotate(cameraRotate, (float)glm::radians(cam_rotate), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 cameraRevolve(1.0f);
	cameraRevolve = glm::rotate(cameraRevolve, (float)glm::radians(cam_revolve), glm::vec3(0.0f, 1.0f, 0.0f));
	view = cameraRotate*lookAt(cameraPos, cameraDirection, cameraUp)*cameraRevolve;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	
	glUseProgram(s_program);
	glEnable(GL_DEPTH_TEST);
	glUniform1i(flagLocation, 0);

	//--------------------���
	bg.Draw(modelLocation);

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
	for (int i = 0; i < FRUIT_MAX; ++i)
	{
		
		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)fruit_xpos[i], fruit_ypos[i], (float)fruit_zpos[i]));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
		glColor3f(1.0f, 0.0f, 0.0f);
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
	
	//--------------------���� ����

	if (bMakePoketmon)
	{
		if (RDraw)
		{
			//Ű���� �������� �޾ƿ� ���� �־���
			SysFruit[CheckCount-1].bDraw = true;
			SysFruit[CheckCount-1].r = Red;
			SysFruit[CheckCount-1].g = Green;
			SysFruit[CheckCount-1].b = Blue;
			SysFruit[CheckCount - 1].color = color;
		}
		else
		{
			//������ RDraw�� false�� ����� rkqtdmf sjgdjwna
			SysFruit[CheckCount].bDraw = false;
			SysFruit[CheckCount].r = Red;
			SysFruit[CheckCount].g = Green;
			SysFruit[CheckCount].b = Blue;
			SysFruit[CheckCount].color = color;
		}
		for (int i = 0; i < 9; ++i)
		{

			T = glm::translate(glm::mat4(1.0f), glm::vec3(SysFruit[i].x, SysFruit[i].y, SysFruit[i].z));
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
			glColor3f(SysFruit[i].r, SysFruit[i].g, SysFruit[i].b);
			if (SysFruit[i].bDraw)//��ü���� �Һ����� ���̸� �׸���
				gluSphere(qobj, 0.2, 20, 20);

		}
		
	}
	//--------------------------------------
	glutSwapBuffers();
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
		
		for (int i = 0; i < FRUIT_MAX; ++i)
		{
			fruit_ypos[i] -= (rand() % 10 + 1) * 0.01;
			if (fruit_ypos[i] <= 1.5f)
			{
				fruit_ypos[i] = 1.5f;
			}
		}
		
		
	}

	if (bMakePoketmon)
	{
		make_pot_cam();
		
	}
	else
	{
		if (bCheckColor)
			check_color();
		if(potswingTimer)
			p.Swing();
	}
	pm.Act();
	glutTimerFunc(10, Timerfunction, 1);
	glutPostRedisplay();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Init_fruit()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < FRUIT_MAX; ++i)
	{
		float fch = (rand() % 10 + 1) / 100+1;//��ġ ����ȭ ����(�յ� �翷)
		if (i % 2 == 0)
		{
			fch *= -1;
		}
		//fruit_zpos[i] = -10.0 + fch;
		//fruit_xpos[i] =fch+i/10;
		fruit_ypos[i] = 9.0f;
	}
	
	for (int i = 0; i < 3; ++i)
	{
		SysFruit[i].x = -0.65f + (i * 0.65);
		SysFruit[i].y = 3.4f;
		SysFruit[i].z = 1.3f;

		SysFruit[i+3].x = -0.65f + (i * 0.65);
		SysFruit[i+3].y = 3.4f;
		SysFruit[i+3].z = 1.95f ;

		SysFruit[i + 6].x = -0.65f + (i * 0.65);
		SysFruit[i + 6].y = 3.4f;
		SysFruit[i + 6].z =  2.6;
	}

	
}

// ���� �������� ���� �� ���� �ݱ�
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	
		float fOutX;
		float fOutY;
		Convert_ScreenToClipSpace(&x, &y, &fOutX, &fOutY);
		cout << fOutX << "|" << fOutY << endl;
		
			for (int i = 0; i < FRUIT_MAX; ++i)
			{
				fruit_ypos[i] = 9.0f;

			}
		//������ �ö󰡰Ը���
		//��ǥ �浹�� ������ �����Ƿ� Ű����� ��ȯ�ϰų� ���д�.
	}
}

void Convert_ScreenToClipSpace(int* pInX, int* pInY, //��ũ����ǥ->�������� ��ǥ
	float* pOutX, float* pOutY)//��ũ�� ���� ���콺 ��ǥ�� �������� ��ǥ��� �ٲ��ִ� �Լ�
{
	*pOutX = (*pInX - WIDTH / 2) * 2.f / WIDTH;
	*pOutY = (HEIGHT / 2 - *pInY) * 2.f / HEIGHT;
}

//ī�޶� ��� �ֵ� ����ֵ� ������ ���� ���� 
void make_pot_cam()  
{
	if (CamYAt < 0)
	{
		CamYAt += cam_tvec;
		if (CamYAt >= -3.0f)
		{
			CamYAt = -3.0f;
		}
	}
	if (CamYAt >= 0)
	{
		CamYAt -= cam_tvec;
		if (CamYAt <= -3.0f)
		{
			CamYAt = -3.0f;
		}
	}

	if (CamZAt < 0)
	{
		CamZAt += cam_tvec;
		if (CamZAt >= -3.0f)
		{
			CamZAt = -3.0f;
		}
	}
	if (CamZAt >= 0)
	{
		CamZAt -= cam_tvec;
		if (CamZAt <= -3.0f)
		{
			CamZAt = -3.0f;
		}
	}

	if (CamPosY < 0)
	{
		CamPosY += cam_tvec;
		if (CamPosY >= 9.0f)
		{
			CamPosY = 9.0f;
		}
	}
	if (CamPosY >= 0)
	{
		CamPosY -= cam_tvec;
		if (CamPosY <= 9.0f)
		{
			CamPosY = 9.0f;
		}
	}
	if (CamPosZ < 0)
	{
		CamPosZ += cam_tvec;
		if (CamPosZ >= 6.0f)
		{
			CamPosZ = 6.0f;
		}
	}
	if (CamPosZ >= 0)
	{
		CamPosZ -= cam_tvec;
		if (CamPosZ <= 6.0f)
		{
			CamPosZ = 6.0f;
		}
	}
}

void check_color()
{
	//��ü�� ������ �ִ� �������� ���� ī��Ʈ�� ���ش�.
	for (int i = 0; i < SYSTEM_FRUIT_MAX; ++i)
	{
		if (SysFruit[i].color == CType::RED)
			++RedCount;
		else if (SysFruit[i].color == CType::GREEN)
			++GreenCount;
		else if (SysFruit[i].color == CType::BLUE)
			++BlueCount;
	}
	cout << RedCount<<"|" << GreenCount<<"|" << BlueCount << endl; //üũ��
	bCheckColor = false;//ī��Ʈ ������� �����ش�.
}