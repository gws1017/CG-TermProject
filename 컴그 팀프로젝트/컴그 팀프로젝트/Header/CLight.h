#pragma once
#include"Header/header.h"
class CLight
{
public:
	glm::vec3 lightscale=glm::vec3(1.0f, 1.0f, 1.0f);
	float LightX = 0.0f;
	float LightY = 0.0f;
	float LightZ = 0.0f;
	glm::vec3 LightPos = glm::vec3(LightX, LightY, LightZ);
	float radius = 1000.0f;
	float deinged = 3.141592 / 180;
	 
public:

	void Update(unsigned int lightPosLocation, unsigned int lightColorLocation);
	void movelight(float count);
};

