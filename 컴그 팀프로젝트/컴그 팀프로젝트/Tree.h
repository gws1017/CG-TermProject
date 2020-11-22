#include "Header/Init.h"
class Tree
{
	GLuint vao, vbo[3], ebo;

	float* vPosData;
	float* vNormalData;
	float* vTextureCoordinateData;
	int* indexData;
	int vertexCount;
	int indexCount;

	int width, height, nrChannels;
	unsigned int texture;
	//glm::mat4 R

public:

	void Init(const GLuint s_program);
	void Draw();
};
