#include "UI_PI.h"
#include "Render_PI.h"
#include "Player.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Sensor.h"
#include "GameState.h"
#include "DecoText.h"


Mesh* UI::clock = nullptr;
Mesh* UI::minute_hand = nullptr;
Mesh* UI::hour_hand = nullptr;

void UI::Exit()
{
	if (clock != nullptr)
	{
		delete clock;
	}
	if (clock != nullptr)
	{
		delete minute_hand;
	}
	if (clock != nullptr)
	{
		delete hour_hand;
	}
}

void UI::Init()
{
	clock = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\Clock_Face.obj");
	clock->textureArray[0] = LoadTGA("Data\\UI\\Clock.tga");
	minute_hand = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\minute_hand.obj");
	minute_hand->textureArray[0] = LoadTGA("Data\\UI\\hand.tga");
	hour_hand = MeshBuilder::GenerateOBJ("clock", "Data\\UI\\hour_hand.obj");
	hour_hand->textureArray[0] = LoadTGA("Data\\UI\\hand.tga");
}
void UI::Render()
{
	Enemy_Poison::pointer()->render_Poison();
	Sensor::pointer()->Render();
	float Runtime = PlayerClass::pointer()->return_Runtime();
	float LightPower = PlayerClass::pointer()->return_LightPower();


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

	Vector3 PosBattery = Vector3(107, 15, 0);
	Vector3 SizeBattery = Vector3(4, 20, 1);
	Render_PI::pointer()->modelStack_Set(true);
	if (LightPower > 8.f && LightPower <= 10.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryFull"), false, PosBattery, SizeBattery);
	}
	else if (LightPower > 6.f && LightPower <= 8.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryFour"), false, PosBattery, SizeBattery);
	}
	else if (LightPower > 4.f && LightPower <= 6.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryThree"), false, PosBattery, SizeBattery);
	}
	else if (LightPower > 2.f && LightPower <= 4.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryTwo"), false, PosBattery, SizeBattery);
	}
	else if (LightPower > 0.f && LightPower <= 2.f)
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryOne"), false, PosBattery, SizeBattery);
	}
	else
	{
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("BatteryZero"), false, PosBattery, SizeBattery);
	}
	Render_PI::pointer()->modelStack_Set(false);


	for (int i = 0; i < floor((Runtime)); i++)
	{
		Render_PI::pointer()->modelStack_Set(true);
		Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Running_Man"), false, Vector3(112 + ((floor((Runtime)) - i)*1.5f), 28, 0), Vector3(4, 4, 1));
		Render_PI::pointer()->modelStack_Set(false);
	}


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


	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderTextOnScreen(GameState::pointer()->GetText(), DecoText::Get(PlayerClass::pointer()->returnDeco()), Color(0.5, 0.9, 0.1), Vector3(25, 50, 0), Vector3(5, 5, 1));
	Render_PI::pointer()->modelStack_Set(false);

}