#pragma once

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "Player.h"

class PokeballInfo
{
public:
	static PokeballInfo* pointer()
	{
		return m_pointer;
	}
private:
	PokeballInfo();
	~PokeballInfo();
	static PokeballInfo* m_pointer;
};