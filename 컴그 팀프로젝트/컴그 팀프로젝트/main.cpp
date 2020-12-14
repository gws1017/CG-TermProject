#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include "Header/Tree1.h"
#include "Header/Tree2.h"
#include "Header/Pot.h"
#include "Header/KeyBoard.h"
#include "Header/PokemonManager.h"
#include "Header/Sound.h"
#include "Header/Fruit.h"
#include "Header//background.h"
#include "Header/Camera.h"
#include "Header/Function.h"
#include "Header/CLight.h"
//opengl 쉐이더및 콜백함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);

//-------마우스함수---------
void MouseInput(int button, int state, int x, int y);
void Convert_ScreenToClipSpace(int* pInX, int* pInY,
	float* pOutX, float* pOutY);
//--------------------------

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

//카메라가 어디에 있든 어디있든 솥으로 가게 해줌 


float cam_dist;//원점과 카메라의 거리
//타이머 변수
bool fruitTimer = false;
bool treeTimer = false;
//bool potswingTimer = false;
bool bMakePoketmon = false;// 솥 조합 시스템 체크
bool bCheckColor = false;//컬러체크 끝내고 멈추기 위한 변수
bool bReset = false;
bool all_timer = false;//전체뷰로 바귀기 전까지 움직이지 않기 위해 체크
void make_dist(float x, float y,float z);//거리계산함수

//열매 떨어질때--------------------------------------------
void Init_fruit();// 열매 랜덤 위치만드는 함수
GLUquadric* qobj;
float fruit_xpos[FRUIT_MAX] = { -1.5f,-1.0f, 0.5f,1.3f,1.6 };
float fruit_ypos[FRUIT_MAX] = { 0.0f, };
float fruit_zpos[FRUIT_MAX] = { -9.0f,-8.5f,-8.3f,-8.7f,-8.0f };

//----열매 조합------------------
CType color; // 열거형 클래스 색깔지정 0:없음 ,1:빨깡 ,2:초록 , 3:파랑
float Red = 0.0f;
float Green = 0.0f;
float Blue = 0.0f;
bool RDraw=false; //넣을때와 뺄때를 구분해주는 변수
int CheckCount = 0; //생성하는 구 인덱스 카운트
int RedCount = 0;   //컬러의개수를 받아주기위한 변수
int GreenCount = 0;	//컬러의개수를 받아주기위한 변수
float LightCount = 0;
int BlueCount = 0;	//컬러의개수를 받아주기위한 변수
//int PotCount = 0;
void check_color();//컬러 카운트를 체크해주는 함수로 배열을 한번 돌아서 몇개의 컬러가 들어갔는지 체크
void reset();//요리만들고 초기화하기 위한함수
//------------------------------


//행렬 선언

glm::mat4 projection = glm::mat4(1.0f);



//객체 선언
Bottom b;
Tree1 t1;
Tree2 t2;
Pot p;
Fruit SysFruit[SYSTEM_FRUIT_MAX]; //조합용 열매 객체
CLight light;
Pokemon_Manager pm;
Sound sound;
Background bg;
Camera cm;

void main(int argc, char** argv)
{
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("PokeMonSimulator");

	glewExperimental = GL_TRUE;
	glewInit();

	glUseProgram(s_program);

	InitShader();

	//클래스 초기화------------------
	b.Init(s_program);
	t1.Init(s_program);
	t2.Init(s_program);
	p.Init(s_program);

	//사운드
	sound.Init_Sound();
	//배경
	bg.Init(s_program);
	cm.Init();
	
	//-------------------
	qobj = gluNewQuadric();
	//-----사용자 함수--------
	Init_fruit();
	
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
	
	//배경음재생
	FMOD_System_PlaySound(sound.soundSystem, sound.bgmSound[0], NULL, 0, &sound.Channel[0]);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseInput);
	glutTimerFunc(10, Timerfunction, 1);

	glutMainLoop();

}

//콜백함수

GLvoid drawScene()
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glm::mat4 T = glm::mat4(1.0f);
	
	cm.Update(viewLocation);
	light.Update(lightPosLocation, lightColorLocation);
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	glUseProgram(s_program);
	glEnable(GL_DEPTH_TEST);
	glUniform1i(flagLocation, 0);

	// 배경그려줌

	bg.Draw(modelLocation);

	//--------------------바닥
	b.Draw(modelLocation);
	//----------------------

	//---------------------뒤에 나무들
	for (int i = 2; i < 12; ++i)
	{
	
		t1.DrawBackTree(modelLocation,i);
		t1.DrawBackTree(modelLocation, -i);
		
	}
	//----------------------------------------


	//-------------------제일 큰나무
	
	t1.DrawBigTree(modelLocation);
	
	//------------열매
	glUniform1i(flagLocation, 1);
	for (int i = 0; i < FRUIT_MAX; ++i)
	{
		

		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)fruit_xpos[i], fruit_ypos[i], (float)fruit_zpos[i]));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(T));
		if(i==1)
		glUniform3f(vColorLocation,1.0f, 0.0f, 0.0f);
		if(i>1&&i<=3)
			glUniform3f(vColorLocation, 0.0f, 1.0f, 0.0f);
		if(i>3)
			glUniform3f(vColorLocation, 0.0f, 0.0f, 1.0f);
		gluSphere(qobj, 0.2, 20, 20);
	}
	
	glUniform1i(flagLocation, 0);
	//-------------------------------옆에 나무들

	for (int i = 1; i < 23; ++i)
	{
		float chp;
		if (i % 2 == 0)
			chp = -0.7;
		else
			chp = 0.7;
		
		if (i % 2 == 0)
		{
			t1.DrawSideTree(modelLocation, chp, i, -11.0);
			t1.DrawSideTree(modelLocation, -chp, i, 11.0);
		}
		else
		{
			t2.DrawSideTree(modelLocation,chp,i,-11.0);
			t2.DrawSideTree(modelLocation, -chp, i, 11.0);
		}
	}

	//--------------------------------------------------
	pm.Draw(modelLocation);

	//------------------------------------------------솥
	glUniform1i(flagLocation, 0);
	p.Draw(modelLocation,vColorLocation);
	//--------------------열매 조합

	if (bMakePoketmon)
	{
		if (RDraw)
		{
			//키보드 변수에서 받아온 값을 넣어줌
			SysFruit[CheckCount-1].Create(RDraw,Red,Green, Blue, color);
		}
		else
		{
			//뺄때는 RDraw를 false로 만들고 rkqtdmf sjgdjwna
			SysFruit[CheckCount].Remove(false);
		}
		for (int i = 0; i < 9; ++i)
		{
			glUniform1i(flagLocation, 1);
			SysFruit[i].Draw(modelLocation,vColorLocation);
		}
		
	}
	
	glutSwapBuffers();
}



void Timerfunction(int value)
{
	make_dist(cm.CamPosX, cm.CamPosY, cm.CamPosZ);
	LightCount += 0.05;
	light.movelight(LightCount);
	if (treeTimer)
		t1.Swing();
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
	if (all_timer)
	{
		if (bMakePoketmon)
		{
			if (bReset)
			{
				reset();
				bReset = false;
			}
			cm.make_pot_cam();
		}
		else
		{
			if (bCheckColor)
			{
				check_color();
				bCheckColor = false;
				CheckCount = 0;
			}
			else
				p.Swing(RedCount, GreenCount, BlueCount, s_program);


		}

		pm.Act();

		if (pm.Position_timer) pm.Position_Count += 1;

		if (pm.Position_Count >= 100)
		{
			pm.Position();
			pm.Position_Count = 0;
			pm.Position_timer = false;
			cm.make_Overview();
			all_timer = false;
		}
	}
	else
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
		float fch = (rand() % 10 + 1) / 100+1;//위치 랜덤화 변수(앞뒤 양옆)
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

// 일정 범위에서 누를 시 열매 줍기
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
		//누르면 올라가게만듬
		//좌표 충돌은 무리가 있으므로 키보드로 전환하거나 냅둔다.
	}
}



//카메라가 어디에 있든 어디있든 솥으로 가게 해줌 


void check_color()
{
	//객체가 가지고 있는 열거형에 따라서 카운트를 세준다.
	for (int i = 0; i < SYSTEM_FRUIT_MAX; ++i)
	{
		if (SysFruit[i].color == CType::RED)
			++RedCount;
		else if (SysFruit[i].color == CType::GREEN)
			++GreenCount;
		else if (SysFruit[i].color == CType::BLUE)
			++BlueCount;
	}
	cout << RedCount<<"|" << GreenCount<<"|" << BlueCount << endl; //체크용
	
}

void reset()
{
	for (int i = 0; i < 9; ++i)
	{
		bool r = false;
		SysFruit[i].Remove(r);
	}
	RedCount = 0;
	GreenCount = 0;
	BlueCount = 0;
	CheckCount = 0;
	color = CType::NONE;
	Red = 0.0f;
	Green = 0.0f;
	Blue = 0.0f;
	
}

void make_dist(float x, float y, float z)
{
	cam_dist = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}