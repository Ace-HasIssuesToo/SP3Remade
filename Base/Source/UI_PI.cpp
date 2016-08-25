#include "UI_PI.h"
#include "Render_PI.h"
#include "Player.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Sensor.h"

void UI::Render()
{
	Enemy_Poison::pointer()->render_Poison();
	Sensor::pointer()->Render();
	float Runtime = PlayerClass::pointer()->return_Runtime();
	Render_PI::pointer()->modelStack_Set(true);
	Vector3 Pos = (Vector3(5, 5, 0) + Vector3(Runtime * 10, 10, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Wall"), false, Pos, Vector3(Runtime * 10, 5, 5));
	Render_PI::pointer()->modelStack_Set(false);

	float LightPower = PlayerClass::pointer()->return_LightPower();
	Render_PI::pointer()->modelStack_Set(true);
	Vector3 Pos2 = (Vector3(5, 5, 0) + Vector3(LightPower * 10, 180, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Wall"), false, Pos2, Vector3(LightPower * 10, 5, 5));
	Render_PI::pointer()->modelStack_Set(false);

	/*if (state == FLOOR1 || state == FLOOR2 || state == FLOOR3 || state == FLOOR4 || state == FLOOR5)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Vector3 Pos = Vector3(levelTimer* 0.05, 40, 0)*0.5f;
		Render_PI::pointer()->RenderMeshIn2D(timer, false, Pos, Vector3(levelTimer * 0.7, 5, 5));
		Render_PI::pointer()->modelStack_Set(false);

	}*/
}