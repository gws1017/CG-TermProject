#include "Header/Function.h"



float NCV(float value)
{
	return value / 255.0f;
}


void MakeFileName(char*& Filename, const int& Namelen,char*& name, const char* Folder, const char* extension)
{
	Filename = new char[Namelen + strlen(Folder) + strlen(extension)];
	strcpy(Filename, Folder);
	strcat(Filename, name);
	strcat(Filename, extension);
}

