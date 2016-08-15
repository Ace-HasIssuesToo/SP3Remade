#include "Room_Scene.h"


bool Room_Scene::Collision_Check(Vector3 pos)
{
	bool Return = false;
	Vector3 Round = Vector3(round(pos.x), 0, round(pos.z));
	Vector3 Ceil = Vector3(ceil(pos.x), 0, ceil(pos.z));
	if (Round.x == Ceil.x)
	{
		pos.x += 0.3;
	}
	else
	{
		pos.x -= 0.3;
	}
	if (Round.z == Ceil.z)
	{
		pos.z += 0.3;
	}
	else
	{
		pos.z -= 0.3;
	}
	int X = int(pos.x / Game_Model::pointer()->Game_Scale);
	int Z = int(pos.z / Game_Model::pointer()->Game_Scale);
	if (Game_Model::pointer()->BluePrint[X][Z] == char(' '))
	{
		Return = true;
	}
	return Return;
}

void Room_Scene::Recursive_Maze_Generator(Vector3 Top, Vector3 Bottom, int Min_Height)
{
	Min_Height = Math::Max(Min_Height, 3);
	if (((Bottom.x - Top.x) <= 2 * Min_Height + 1) || ((Bottom.z - Top.z - 2 * Min_Height) <= 2 * Min_Height + 1))
	{
	}
	else
	{
		//Set Walls
		int X = Top.x + rand() % int(Bottom.x - Top.x - (2*Min_Height));
		int Z = Top.z + rand() % int(Bottom.z - Top.z - (2 * Min_Height));

		//Set Holes
		int X_hole[2] = { Top.x + 1, X + 1 };
		if (X - Top.x > 0)
		{
			X_hole[0] = (Top.x) + Math::Min(rand() % int(X - Top.x),1);
		}
		if (Bottom.x - X > 0)
		{
			X_hole[1] = (X)+rand() % Math::Min(int(Bottom.x - X), 1);
		}
		int Z_hole[2] = { Top.z + 1, Z + 1 };
		if (Z - Top.z > 0)
		{
			Z_hole[0] = (Top.z) + rand() % Math::Min(int(Z - Top.z), 1);
		}
		if (Bottom.z - Z > 0)
		{
			Z_hole[1] = (Z)+rand() % Math::Min(int(Bottom.z - Z), 1);
		}

		//Build Walls
			for (int i = Top.x; i < Bottom.x; i++)
			{
				if (i != X_hole[0] && i != X_hole[1])
				{
					Game_Model::pointer()->BluePrint[i][Z] = char('W');
				}
				else
				{
					Game_Model::pointer()->BluePrint[i][Z] = char(' ');
				}
			}
			for (int j = Top.z; j < Bottom.z; j++)
			{
				if (j != Z_hole[0] && j != Z_hole[1])
				{
					Game_Model::pointer()->BluePrint[X][j] = char('W');
				}
				else
				{
					Game_Model::pointer()->BluePrint[X][j] = char(' ');
				}
			}

		//More Rooms
		Vector3 Room1[2] = { Top, Vector3(X, 0, Z) };
		Vector3 Room4[2] = { Vector3(X, 0, Z), Bottom };
		Vector3 Room2[2] = { Vector3(X, 0, Top.z), Vector3(Bottom.x, 0, Z) };
		Vector3 Room3[2] = { Vector3(Top.x, 0, Z), Vector3(X, 0, Bottom.z) };
		Recursive_Maze_Generator(Room1[0], Room1[1], Min_Height);

		Recursive_Maze_Generator(Room2[0], Room2[1], Min_Height);

		Recursive_Maze_Generator(Room3[0], Room3[1], Min_Height);

		Recursive_Maze_Generator(Room4[0], Room4[1], Min_Height);


	}

};

void Room_Scene::Init()
{

	Mesh* T_Mesh = MeshBuilder::GenerateOBJ("Wall", "Data\\Room\\Wall.obj");
	T_Mesh->textureArray[0] = LoadTGA("Data\\Room\\Wall.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);
	
	T_Mesh = MeshBuilder::GenerateAxes("Axes", 1000, 1000, 1000);
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);

	T_Mesh = MeshBuilder::GenerateTerrain("Floor", "Data\\Room\\Floor.raw", Game_Model::pointer()->m_heightMap);
	T_Mesh->textureArray[0] = LoadTGA("Data\\Room\\Floor.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);

	T_Mesh = MeshBuilder::GenerateOBJ("Ceiling", "Data\\Room\\Wall.obj");
	T_Mesh->textureArray[0] = LoadTGA("Data\\Room\\Ceiling.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);

	T_Mesh = MeshBuilder::GenerateOBJ("Skyplane", "Data\\Room\\Skyplane.obj");
	T_Mesh->textureArray[0] = LoadTGA("Data\\Room\\Skyplane.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);

	T_Mesh = nullptr;
	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			if (x == 0 || z == 0 || x == 99 || z == 99)
			{
				Game_Model::pointer()->BluePrint[x][z] = char('W');
			}
			else
			{
				Game_Model::pointer()->BluePrint[x][z] = char('?');
			}
		}

	}
	Recursive_Maze_Generator(Vector3(1, 0, 1), Vector3(98, 0, 98), 3);
	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			if (Game_Model::pointer()->BluePrint[x][z] == char('?'))
			{
				Game_Model::pointer()->BluePrint[x][z] = char(' ');
			}
		}

	}
	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			if (Game_Model::pointer()->BluePrint[x][z] == char(' '))
			{
				if (Game_Model::pointer()->BluePrint[x - 1][z] != char(' ') && Game_Model::pointer()->BluePrint[x + 1][z] != char(' ') && Game_Model::pointer()->BluePrint[x][z - 1] != char(' ') && Game_Model::pointer()->BluePrint[x][z + 1] != char(' '))
				{
					Game_Model::pointer()->BluePrint[x - 1][z] = char(' ');
					Game_Model::pointer()->BluePrint[x + 1][z] = char(' ');
					Game_Model::pointer()->BluePrint[x][z - 1] = char(' ');
					Game_Model::pointer()->BluePrint[x][z + 1] = char(' ');
				}
			}
		}

	}
	std::ofstream myfile;
	myfile.open("example.txt"); 
	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			if (Game_Model::pointer()->BluePrint[x][z] == char(' '))
			{
				myfile << " ";
			}
			else
			{
				myfile << "W";
			}
		}
			myfile << "\n";

	}
	myfile.close();

}

void Room_Scene::Update(double dt)
{
}

void Room_Scene::Render()
{
	Render_Scene(Game_Model::pointer()->Current_Camera->camera.target);
}

void Room_Scene::Render_Scene(Vector3 Pos)
{

	Game_Model::pointer()->modelStack_Set(true);
	Game_Model::pointer()->modelStack_Define(Game_Model::pointer()->Current_Camera->camera.position, 0, Vector3(), Vector3(Math::Square(Game_Model::pointer()->Game_Scale)*Game_Model::pointer()->Room_Range, Math::Square(Game_Model::pointer()->Game_Scale)*Game_Model::pointer()->Room_Range, Math::Square(Game_Model::pointer()->Game_Scale)*Game_Model::pointer()->Room_Range));
	Render_Function::RenderMesh(Render_Function::Mesh_Search("Skyplane"), true);
	Game_Model::pointer()->modelStack_Set(false);
	
	int camera_X = int(Pos.x / Game_Model::pointer()->Game_Scale);
	int camera_Z = int(Pos.z / Game_Model::pointer()->Game_Scale);
	if (camera_X < Game_Model::pointer()->Room_Range)
	{
		camera_X = Game_Model::pointer()->Room_Range;
	}
	if (camera_Z < Game_Model::pointer()->Room_Range)
	{
		camera_Z = Game_Model::pointer()->Room_Range;
	}
	if (camera_X > 99 - Game_Model::pointer()->Room_Range)
	{
		camera_X = 99 - Game_Model::pointer()->Room_Range;
	}
	if (camera_Z > 99 - Game_Model::pointer()->Room_Range)
	{
		camera_Z = 99 - Game_Model::pointer()->Room_Range;
	}
	for (int X = camera_X - Game_Model::pointer()->Room_Range; X < camera_X + Game_Model::pointer()->Room_Range; X++)
	{
		for (int Z = camera_Z - Game_Model::pointer()->Room_Range; Z < camera_Z + Game_Model::pointer()->Room_Range; Z++)
		{
			Room_Render(X, Z);
		}
	}
}

void Room_Scene::Room_Render(int X, int Z)
{
	float S_Diff = 0.1;
	Game_Model::pointer()->modelStack_Set(true);
	Game_Model::pointer()->modelStack_Define(Vector3((X + 0.5)*Game_Model::pointer()->Game_Scale, 0, (Z + 0.5)*Game_Model::pointer()->Game_Scale), 0, Vector3(), Vector3());

	if (Game_Model::pointer()->BluePrint[X][Z] == char(' '))
	{
		Game_Model::pointer()->modelStack_Set(true);
		Game_Model::pointer()->modelStack_Define(Vector3(), A_A_T::Angle(X*Z*90), Vector3(0,1,0), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, 0.1, Game_Model::pointer()->Game_Scale+ S_Diff));
		Render_Function::RenderMesh(Render_Function::Mesh_Search("Floor"), true);
		Game_Model::pointer()->modelStack_Set(false);


		Game_Model::pointer()->modelStack_Set(true);
		Game_Model::pointer()->modelStack_Define(Vector3(0, Game_Model::pointer()->Game_Scale,0), 180, Vector3(1), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff));
		Render_Function::RenderMesh(Render_Function::Mesh_Search("Ceiling"), true);
		Game_Model::pointer()->modelStack_Set(false);
	}
	else
	{
		if (Game_Model::pointer()->BluePrint[X][Z + 1] == char(' '))
		{
			Game_Model::pointer()->modelStack_Set(true);
			Game_Model::pointer()->modelStack_Define(Vector3(0, Game_Model::pointer()->Game_Scale*0.5, Game_Model::pointer()->Game_Scale*0.5), 90, Vector3(1), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff));
			Render_Function::RenderMesh(Render_Function::Mesh_Search("Wall"), true);
			Game_Model::pointer()->modelStack_Set(false);
		}
		if (Game_Model::pointer()->BluePrint[X][Z - 1] == char(' '))
		{
			Game_Model::pointer()->modelStack_Set(true);
			Game_Model::pointer()->modelStack_Define(Vector3(0, Game_Model::pointer()->Game_Scale*0.5, Game_Model::pointer()->Game_Scale*(-0.5)), 270, Vector3(1), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff));
			Render_Function::RenderMesh(Render_Function::Mesh_Search("Wall"), true);
			Game_Model::pointer()->modelStack_Set(false);
		}
		if (Game_Model::pointer()->BluePrint[X + 1][Z] == char(' '))
		{
			Game_Model::pointer()->modelStack_Set(true);
			Game_Model::pointer()->modelStack_Define(Vector3(Game_Model::pointer()->Game_Scale*0.5, Game_Model::pointer()->Game_Scale*0.5, 0), 270, Vector3(0,0,1), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff));
			Render_Function::RenderMesh(Render_Function::Mesh_Search("Wall"), true);
			Game_Model::pointer()->modelStack_Set(false);
		}
		if (Game_Model::pointer()->BluePrint[X - 1][Z] == char(' '))
		{
			Game_Model::pointer()->modelStack_Set(true);
			Game_Model::pointer()->modelStack_Define(Vector3(Game_Model::pointer()->Game_Scale*(-0.5), Game_Model::pointer()->Game_Scale*0.5, 0), 90, Vector3(0,0,1), Vector3(Game_Model::pointer()->Game_Scale + S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff, Game_Model::pointer()->Game_Scale+ S_Diff));
			Render_Function::RenderMesh(Render_Function::Mesh_Search("Wall"), true);
			Game_Model::pointer()->modelStack_Set(false);
		}
	}

	Game_Model::pointer()->modelStack_Set(false);
}

void Room_Scene::Exit()
{

}