#pragma once
#include "header.h"



class Pokemon_Manager {
 
	vector<class Pokemon> vpm;

public:

	bool Position_timer = false;
	int Position_Count = 0;
	Pokemon_Manager();
	~Pokemon_Manager();

	void Create(int r, int g, int b, GLuint s_program);

	void Draw(const unsigned int modelLocation);

	void Act();

	void Position();
};
