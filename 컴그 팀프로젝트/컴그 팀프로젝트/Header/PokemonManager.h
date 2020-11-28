#pragma once
#include "header.h"


class Pokemon_Manager {
 
	vector<class Pokemon> vpm;

public:

	Pokemon_Manager();
	~Pokemon_Manager();

	void Create(const char* name, GLuint s_program);

	void Draw(const unsigned int modelLocation);

	void Act();

	void Position(Pokemon* p);
};
