#include "Header/header.h"


//opengl 쉐이더및 콜백함수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


//opengl 기본변수
GLuint s_program;
GLuint shaderID;
GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example1");

	glewExperimental = GL_TRUE;
	glewInit();

	InitShader();


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	

	glutMainLoop();

}

//콜백함수

GLvoid drawScene()
{
	glUseProgram(s_program);
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}


