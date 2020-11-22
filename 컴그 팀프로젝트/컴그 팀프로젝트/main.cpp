#include "Header/ShaderManager.h"
#include "Header/Bottom.h"
#include"Tree.h"
//opengl 쉐이더및 콜백함수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);

//opengl 기본변수
GLuint s_program;
GLuint shaderID;
GLchar* vertexsource, *fragmentsource;
GLuint vertexshader, fragmentshader;

//로케이션 변수
unsigned int vColorLocation;
unsigned int projectionLocation;
unsigned int modelLocation;
unsigned int viewLocation;
unsigned int viewposLocation;
unsigned int lightPosLocation;
unsigned int lightColorLocation;

float CamPosX = 0.0f;
float CamPosY = 1.0f;
float CamPosZ = 5.0f;

float CamXAt = 0.0f;
float CamYAt = 0.0f;
float CamZAt = 0.0f;

float cam_rotate = 0.0;
float cam_revolve = 0.0;
//행렬 선언


//객체 선언
Bottom b;
Tree t;
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
	b.Init(s_program);
	t.Init(s_program);
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

	glutMainLoop();

}

//콜백함수

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(s_program);
	

	glm::vec3 cameraPos = glm::vec3(CamPosX, CamPosY, CamPosZ);
	glm::vec3 cameraDirection = glm::vec3(CamXAt, CamYAt, CamZAt);
	glm::mat4 cameraRotate(1.0f);

	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 cameraRevolve(1.0f);

	cameraRotate = glm::rotate(cameraRotate, (float)glm::radians(cam_rotate), glm::vec3(0.0f, 1.0f, 0.0f));
	cameraRevolve = glm::rotate(cameraRevolve, (float)glm::radians(cam_revolve), glm::vec3(0.0f, 1.0f, 0.0f));
	view = cameraRotate*glm::lookAt(cameraPos, cameraDirection, cameraUp)* cameraRevolve;
	projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 50.0f);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	glm::mat4 S = glm::mat4(1.0f);

	glm::mat4 T = glm::mat4(1.0f);

	glm::mat4 Rx = glm::mat4(1.0f);
	glm::mat4 Ry = glm::mat4(1.0f);
	glm::mat4 Rz = glm::mat4(1.0f);

	glm::mat4 STR = glm::mat4(1.0f);
	S = scale(S, glm::vec3(0.1, 0.1, 0.1));
	modelLocation = glGetUniformLocation(s_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(STR));
	t.Draw();

	STR = STR * S;
	unsigned int modelLocation2 = glGetUniformLocation(s_program, "modelTransform");
	glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(STR));
	b.Draw();
	
	
	
	glEnable(GL_DEPTH_TEST);


	glutPostRedisplay();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

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
	
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}


