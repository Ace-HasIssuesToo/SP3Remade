#include "Map_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Player.h"

Vector3 Map::Map_Rand()
{
	int x = Math::RandIntMinMax(0, Limitation.x*10.f);
	int y = Math::RandIntMinMax(0, Limitation.y*10.f);
	Vector3 pos = Vector3(x, y, 0);
	while (Get_Type(pos) != "Floor")
	{
		if (pos.x > 0)
		{
			pos.x--;
		}
		else
		{
			pos.x = Limitation.x;
			if (pos.y > 0)
			{
				pos.y--;
			}
			else
			{
				pos.y = Limitation.y;
			}
		}
	}
	return pos;
}

bool Map::Init(std::string Filename)
{
	std::ifstream file(Filename);	 // declare file stream: 
	std::string Line;
	int Size = -1;
	if (file.is_open())
	{
		while (getline(file, Line)) //read entire line
		{
			Size++;
		}
		file.close();
	}
	else
	{
		return false;
	}
	Limitation = Vector3();
	Limitation.x = Size;
	std::ifstream file2(Filename);
	std::stringstream Datas;//Datas to process
	std::string Type; //individual values
	int I = 0;
	while (getline(file2, Line)) //read entire line
	{
		Datas.str(std::string());
		Datas.clear();
		I = -1;
		Datas << Line;    //create istringstream for parsing
		while (getline(Datas, Type, ',')) //parse for commas
		{
			I++;
			std::stringstream Location;
			Location << Size << " / " << I;
			string Strings = Location.str();
			Map_Data.insert(std::pair<std::string, std::string>(Strings, Type));
			
		}
		Limitation.y = Math::Max(I*1.0f, Limitation.y);
		Size--;
	}
	file.close();
	return true;
}

void Map::RenderEvent(Vector3 pos, bool Dark)
{
	//Map Amount
	//Offset Calculation
	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * sizes);
	std::stringstream Location;
	Vector3 Size = Render_PI::Window_Scale()*(1.f / sizes);
	Vector3 Displacement = Vector3(pos.x - Math::Max(floor(pos.x), 0.f), pos.y - Math::Max(floor(pos.y), 0.f), 0)*-1;

	Vector3 Character_Pos = PlayerClass::pointer()->getPlayerPos();
	Character_Pos = pos + (Vector3((Character_Pos.y) / Render_PI::Window_Scale().y, (Character_Pos.x) / Render_PI::Window_Scale().x, 0) * sizes);

	for (int X = Math::Min(ceil(pos.x + sizes), Limitation.x); Math::Max(floor(pos.x), 0.f) <= X; X--)
	{
		for (int Y = Math::Min(ceil(pos.y + sizes), Limitation.y); Math::Max(floor(pos.y), 0.f) <= Y; Y--)
		{
			Location.str(std::string());
			Location.clear();
			Location << X << " / " << Y;
			std::map<std::string, std::string>::iterator it;
			string Strings = Location.str();
			it = Map_Data.find(Strings);
			if (Dark)
			{
				if (Map_Data.at(Location.str()) == "Wall")
				{
					Render_PI::pointer()->modelStack_Set(true);
					Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
					Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Mist_Wall"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
					Render_PI::pointer()->modelStack_Set(false);
				}
				else
				{
					Render_PI::pointer()->modelStack_Set(true);
					Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
					Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Mist_Floor"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
					Render_PI::pointer()->modelStack_Set(false);
				}
			}
			else
			{
				if (Map_Data.at(Location.str()) == "Wall")
				{
					Render_PI::pointer()->modelStack_Set(true);
					Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
					Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Bright_Wall"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
					Render_PI::pointer()->modelStack_Set(false);
				}
				else
				{
					Render_PI::pointer()->modelStack_Set(true);
					Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
					Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Bright_Floor"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
					Render_PI::pointer()->modelStack_Set(false);
				}
			}
		}
	}
}

void Map::Render(Vector3 pos, bool Shadow)
{
	float LR = PlayerClass::pointer()->GetLightRange();
	//Map Amount
	//Offset Calculation
	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * sizes);
	std::stringstream Location;
	Vector3 Size = Render_PI::Window_Scale()*(1.f / sizes);
	Vector3 Displacement = Vector3(pos.x - Math::Max(floor(pos.x), 0.f), pos.y - Math::Max(floor(pos.y), 0.f), 0)*-1;

	Vector3 Character_Pos = PlayerClass::pointer()->getPlayerPos();
	Character_Pos = pos + (Vector3((Character_Pos.y) / Render_PI::Window_Scale().y, (Character_Pos.x) / Render_PI::Window_Scale().x, 0) * sizes);

	for (int X = Math::Min(ceil(pos.x + sizes), Limitation.x); Math::Max(floor(pos.x), 0.f) <= X; X--)
	{
		for (int Y = Math::Min(ceil(pos.y + sizes), Limitation.y); Math::Max(floor(pos.y), 0.f) <= Y; Y--)
		{
			Location.str(std::string());
			Location.clear();
			Location << X << " / " << Y;
			std::map<std::string, std::string>::iterator it;
			string Strings = Location.str();
			it = Map_Data.find(Strings);
			if (X <= int((Character_Pos.x + 1) + LR) && X >= int((Character_Pos.x - 1) - LR) && Y <= int((Character_Pos.y + 1) + LR) && Y >= int((Character_Pos.y - 1) - LR))
			{
				if (!Shadow)
				{

					if (it == Map_Data.end())
					{
						Render_PI::pointer()->modelStack_Set(true);
						Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
						Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Something"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
						Render_PI::pointer()->modelStack_Set(false);
					}
					else
					{
						Render_PI::pointer()->modelStack_Set(true);
						Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
						Render_PI::pointer()->RenderMeshIn2D(Texture::Get(Map_Data.at(Location.str())), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
						Render_PI::pointer()->modelStack_Set(false);
					}
				}
			}
			else
			{
				if (Shadow)
				{
					if (Map_Data.at(Location.str()) == "Wall")
					{
						Render_PI::pointer()->modelStack_Set(true);
						Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
						Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Mist_Wall"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
						Render_PI::pointer()->modelStack_Set(false);
					}
					else
					{
						Render_PI::pointer()->modelStack_Set(true);
						Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
						Render_PI::pointer()->RenderMeshIn2D(Texture::Get("Mist_Floor"), false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
						Render_PI::pointer()->modelStack_Set(false);
					}
				}
			}
		}
	}
}

std::string Map::Get_Type(Vector3 pos)
{
	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * sizes);
	std::stringstream Location;
	Location << floor(pos.x) << " / " << floor(pos.y);
	std::map<std::string, std::string>::iterator it;
	string Strings = Location.str();
	it = Map_Data.find(Strings);
	if (it == Map_Data.end())
	{
		return "Wall";
	}
	return Map_Data.at(Location.str());
}

Vector3 Map::Pokemon_Offset(Vector3 pos)
{
	return (pos - PlayerClass::pointer()->getPlayerPosOffSet());
}


bool Map::In_Range(Vector3 WorldPos, Vector3 pos)
{
//	//float LR = float();
//	//LR = GameEnvironmentEvent::pointer()->ChangeLightRange(LR);
//	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * sizes);
//	std::stringstream Location;
//	Vector3 Size = Render_PI::Window_Scale()*(1.f / sizes);
//
//	Vector3 Character_Pos = PlayerClass::pointer()->getPlayerPos();
//	Character_Pos = pos + (Vector3((Character_Pos.y) / Render_PI::Window_Scale().y, (Character_Pos.x) / Render_PI::Window_Scale().x, 0) * sizes);
//	Vector3  Current_Pos = (Vector3((WorldPos.y) / Render_PI::Window_Scale().y, (WorldPos.x) / Render_PI::Window_Scale().x, 0) * sizes);
//
//	if (Current_Pos.x <= int((Character_Pos.x + 2) + LR) && Current_Pos.x >= int((Character_Pos.x - 2) - LR) && Current_Pos.y <= int((Character_Pos.y + 2) + LR) && Current_Pos.y >= int((Character_Pos.y - 2) - LR))
//	{
//		return true;
//	}
	return false;
}

void Map::Clear()
{
	Map_Data.clear();
}