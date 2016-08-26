#include "UI_PI.h"
#include "Render_PI.h"
#include "Player.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Sensor.h"
#include "GameState.h"

void UI::Render()
{
	Enemy_Poison::pointer()->render_Poison();
	Sensor::pointer()->Render();
	float Runtime = PlayerClass::pointer()->return_Runtime();
	Render_PI::pointer()->modelStack_Set(true);
	//Vector3 Pos = (Vector3(184, 5, 0) + Vector3(Runtime * 10, 48, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Stamina"), false, Vector3(110, 27, 0) + Vector3(Runtime * 1.75, 0, 0), Vector3(Runtime * 3.5, 5, 1));
	Render_PI::pointer()->modelStack_Set(false);

	float LightPower = PlayerClass::pointer()->return_LightPower();
	Render_PI::pointer()->modelStack_Set(true);/*
	Vector3 Pos2 = (Vector3(10, 5, 0) + Vector3(LightPower * 11, 55, 0))*0.5f;*/
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Battery"), false, Vector3(110, 31, 0) + Vector3(LightPower * 1.0, 0, 0), Vector3(LightPower * 2, 3, 1));
	Render_PI::pointer()->modelStack_Set(false);

	bool GetBattery = PlayerClass::pointer()->return_BatteryIcon();
	if (GetBattery == true)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryIcon"), false, Vector3(5, 10, 0), Vector3(5, 10, 1));
		Render_PI::pointer()->RenderTextOnScreen(GameState::pointer()->GetText(), "1", Color(1, 1, 0), Vector3(5, 17, 0), Vector3(5, 5, 1));
		//cout << batteryTimer << endl;
	}

	bool GetDrink = PlayerClass::pointer()->return_DrinkIcon();
	if (GetDrink == true)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("DrinkIcon"), false, Vector3(15, 10, 0), Vector3(5, 10, 1));
		Render_PI::pointer()->RenderTextOnScreen(GameState::pointer()->GetText(), "2", Color(1, 1, 0), Vector3(15, 17, 0), Vector3(5, 5, 1));
		//cout << drinkTimer << endl;
	}

	Render_PI::pointer()->modelStack_Set(true);
	if (LightPower > 8.f && LightPower <= 10.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryFull"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	else if (LightPower > 6.f && LightPower <= 8.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryFour"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	else if (LightPower > 4.f && LightPower <= 6.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryThree"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	else if (LightPower > 2.f && LightPower <= 4.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryTwo"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	else if (LightPower > 0.f && LightPower <= 2.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryOne"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	else
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryZero"), false, Vector3(107, 31, 0), Vector3(4, 4, 1));
	}
	Render_PI::pointer()->modelStack_Set(false);

	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("StaminaIcon"), false, Vector3(107, 26, 0), Vector3(4, 5, 1));
	Render_PI::pointer()->modelStack_Set(false);
	
}