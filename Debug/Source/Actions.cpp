#include "Actions.h"
#include "Game_Model.h"
#include "Application.h"


Actions* Actions::m_pointer = new Actions();

void Actions::Update(float dt)
{
	Clear_Action();

	if (Application::IsKeyPressed('L'))
	{
		Game_Model::pointer()->Light_Check = true;
	}
	if (Application::IsKeyPressed('K'))
	{
		Game_Model::pointer()->Light_Check = false;
	}
	if (Application::IsKeyPressed(VK_SPACE))
	{
		actions[jump] = true;
	}
	Game_Model::pointer()->System_Update(dt);
};