#include "Header/PokemonManager.h"
#include "Header/Pokemon.h"

Pokemon_Manager::Pokemon_Manager()
{

}
Pokemon_Manager::~Pokemon_Manager()
{

}

void Pokemon_Manager::Create(const char* name ,GLuint s_program)
{
	Pokemon p(name);
	p.Init(s_program);
	vpm.push_back(p);
}


void Pokemon_Manager::Draw(const unsigned int modelLocation)
{
	if (!vpm.empty())
	{
		for (int i = 0; i < vpm.size(); i++)
		{
			vpm.at(i).Draw(modelLocation);
		}

	}
	
}