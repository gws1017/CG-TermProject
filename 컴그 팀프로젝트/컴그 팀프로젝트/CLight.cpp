#include "Header/CLight.h"



void CLight::Update(unsigned int lightPosLocation, unsigned int lightColorLocation)
{
	
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLocation, LightX, LightY, LightZ);
	
}

void CLight::movelight(float count)
{
	LightX = (float)cos(count * deinged) * radius + 0.5f;
	LightY = (float)sin(count * deinged) * radius;
	LightZ = 0.5f;
}


