#include "Map_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Player.h"


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

void Map::Render(Vector3 pos)
{
	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * 10);
	std::stringstream Location;
	Vector3 Size = Render_PI::Window_Scale()*(1.f/10.f);
	Vector3 Displacement = Vector3(pos.x - Math::Max(floor(pos.x), 0.f), pos.y - Math::Max(floor(pos.y), 0.f), 0)*-1;
	for (int X = Math::Min(ceil(pos.x + 10), Limitation.x); Math::Max(floor(pos.x), 0.f) <= X;  X--)
	{
		for (int Y = Math::Min(ceil(pos.y + 10), Limitation.y); Math::Max(floor(pos.y), 0.f) <= Y;  Y--)
		{
			Location.str(std::string());
			Location.clear();
			Location << X << " / " << Y;
			std::map<std::string, std::string>::iterator it;
			string Strings = Location.str();
			it = Map_Data.find(Strings);
			if (it == Map_Data.end())
			{
				return;
			}
			else
			{
				Render_PI::pointer()->modelStack_Set(true);
				Vector3 Render_Pos = Displacement + Vector3((X - Math::Max(floor(pos.x), 0.f)) + 0.5, (Y - Math::Max(floor(pos.y), 0.f)) + 0.5, 0);
				Render_PI::pointer()->RenderMeshIn2D(Texture::Get(Map_Data.at(Location.str())),false, Vector3(Render_Pos.y*Size.x, Render_Pos.x*Size.y, -1), Vector3(Size.x, Size.y, 1));
				Render_PI::pointer()->modelStack_Set(false);
			}
		}
	}
}

std::string Map::Get_Type(Vector3 pos)
{
	pos = (Vector3(pos.y / Render_PI::Window_Scale().y, pos.x / Render_PI::Window_Scale().x, 0) * 10);
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