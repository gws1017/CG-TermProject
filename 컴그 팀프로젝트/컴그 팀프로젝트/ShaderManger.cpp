#include "Header/ShaderManager.h"

//opengl 기본변수
extern GLuint s_program;
extern GLuint shaderID;
extern GLchar* vertexsource, * fragmentsource;
extern GLuint vertexshader, fragmentshader;

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;

} 

void make_vertexShader()
{
	vertexsource = filetobuf("Shader/vertex.glsl");
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	glCompileShader(vertexshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR:vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_fragmentShader()
{
	fragmentsource = filetobuf("Shader/fragment.glsl");
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, NULL);
	glCompileShader(fragmentshader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR:vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void InitShader()
{
	make_vertexShader();
	make_fragmentShader();

	s_program = glCreateProgram();
	glAttachShader(s_program, vertexshader);
	glAttachShader(s_program, fragmentshader);
	glLinkProgram(s_program);
	//CheckCompileErrors(s_program, "PROGRAM");
	//--- 세이더 삭제하기 
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
	//--- Shader Program 사용하기 
	glUseProgram(s_program);
}
