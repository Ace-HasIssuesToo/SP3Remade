#include "UI_PI.h"
#include "Render_PI.h"
#include "Player.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Sensor.h"
<<<<<<< HEAD
=======
#include "GameState.h"
<<<<<<< dda089ad6b72dd5b6f8e8d0ad7abb116fc753095
=======


Mesh* UI::clock = nullptr;
Mesh* UI::minute_hand = nullptr;
Mesh* UI::hour_hand = nullptr;

void UI::Init()
{
	clock = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\Clock_Face.obj");
	clock->textureArray[0] = LoadTGA("Data\\UI\\Clock.tga");
	minute_hand = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\minute_hand.obj");
	minute_hand->textureArray[0] = LoadTGA("Data\\UI\\hand.tga");
	hour_hand = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\hour_hand.obj");
	hour_hand->textureArray[0] = LoadTGA("Data\\UI\\hand.tga");
}
>>>>>>> Clock Done!
>>>>>>> 44426e81d4351c103c7110d8e3b8bd85597ddb6f

void UI::Render()
{
	Enemy_Poison::pointer()->render_Poison();
	Sensor::pointer()->Render();
	float Runtime = PlayerClass::pointer()->return_Runtime();
	Render_PI::pointer()->modelStack_Set(true);
	//Vector3 Pos = (Vector3(184, 5, 0) + Vector3(Runtime * 10, 48, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Stamina"), false, Vector3(110, 27, 0) + Vector3(Runtime * 1.75, 0, 0), Vector3(Runtime * 3.5, 5, 5));
	Render_PI::pointer()->modelStack_Set(false);

	float LightPower = PlayerClass::pointer()->return_LightPower();
	Render_PI::pointer()->modelStack_Set(true);
	Vector3 Pos2 = (Vector3(10, 5, 0) + Vector3(LightPower * 11, 55, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Battery"), false, Vector3(110, 31, 0) + Vector3(LightPower * 1.0, 0, 0), Vector3(LightPower * 2, 3, 5));
	Render_PI::pointer()->modelStack_Set(false);

<<<<<<< HEAD
	/*if (state == FLOOR1 || state == FLOOR2 || state == FLOOR3 || state == FLOOR4 || state == FLOOR5)
=======
<<<<<<< dda089ad6b72dd5b6f8e8d0ad7abb116fc753095
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
>>>>>>> 44426e81d4351c103c7110d8e3b8bd85597ddb6f
	{
		Render_PI::pointer()->modelStack_Set(true);
		Vector3 Pos = Vector3(levelTimer* 0.05, 40, 0)*0.5f;
		Render_PI::pointer()->RenderMeshIn2D(timer, false, Pos, Vector3(levelTimer * 0.7, 5, 5));
		Render_PI::pointer()->modelStack_Set(false);

<<<<<<< HEAD
	}*/
=======
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("StaminaIcon"), false, Vector3(107, 26, 0), Vector3(4, 5, 1));
	Render_PI::pointer()->modelStack_Set(false);
=======

	Vector3 Pos = Render_PI::Window_Scale();
	Pos.y -= 15;
	Pos.x *= 0.9;
	float TimeLeft = GameState::pointer()->Get_Timer();
	float hour_Angle = (180.f - TimeLeft)*-1.f;
	float Current_Min = TimeLeft - float(floor(TimeLeft / min_per_hour)*min_per_hour);
	float min_Angle = float(30.f - Current_Min) * 12.f * -1.f;
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(clock, false, Pos, Vector3(20, 20, 1));
	Render_PI::pointer()->modelStack_Set(false);
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(minute_hand, false, Pos, Vector3(20, 20, 1), min_Angle, Vector3(0, 0, 1));
	Render_PI::pointer()->modelStack_Set(false);
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(hour_hand, false, Pos, Vector3(20, 20, 1),hour_Angle, Vector3(0, 0, 1));
	Render_PI::pointer()->modelStack_Set(false);

	
>>>>>>> Clock Done!
	
>>>>>>> 44426e81d4351c103c7110d8e3b8bd85597ddb6f
}