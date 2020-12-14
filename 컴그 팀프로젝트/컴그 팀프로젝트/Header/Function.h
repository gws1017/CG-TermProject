#pragma once
#include "header.h"
//종종 쓰이는 기타함수 모아놓기

//정규화된 컬러 값 변환 함수
float NCV(float value);
/*{
	return value / 255.0f;
}*/

//이름길이, 이름, 폴더위치, 확장자를 대입하면 Filename에 파일이름을 만들어서 넣어준다.
void MakeFileName(char*& Filename, const int& Namelen, char*& name, const char* Folder, const char* extension);
/*{
	Filename = new char[Namelen + strlen(Folder) + strlen(extension)];
	Filename = strcpy(Filename, Folder);
	Filename = strcat(Filename,name);
	Filename = strcat(Filename, extension);
}*/

bool Check_Combination(int r, int g, int b);