#include "Gun_Scene.h"

void Gun_Scene::Init()
{
	for (int i = 0; i < 5; i++)
	{
		Bullet* Create = new Bullet;
		Create->Clear();
		Game_Model::pointer()->Bullet_Data.push_back(Create);
	}
	Game_Model::pointer()->Gun_CD = 0;
	Game_Model::pointer()->Tazer = false;

	Mesh* T_Mesh = MeshBuilder::GenerateOBJ("Pistol", "Data\\Equipments\\Pistol.obj");
	T_Mesh->textureArray[0] = LoadTGA("Data\\Equipments\\Equipment.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);
	T_Mesh = MeshBuilder::GenerateOBJ("Bullet", "Data\\Equipments\\Bullet.obj");
	T_Mesh->textureArray[0] = LoadTGA("Data\\Equipments\\Equipment.tga");
	Game_Model::pointer()->Mesh_Data.push_back(T_Mesh);

}

void Gun_Scene::Update(double dt)
{
	int Player_X = int(Game_Model::pointer()->Current_Camera->camera.position.x / Game_Model::pointer()->Game_Scale);
	int  Player_Z = int(Game_Model::pointer()->Current_Camera->camera.position.z / Game_Model::pointer()->Game_Scale);
	for (std::vector<Bullet *>::iterator X = Game_Model::pointer()->Bullet_Data.begin(); X != Game_Model::pointer()->Bullet_Data.end(); ++X)
	{
		if (((Bullet*)*X)->Active)
		{
			((Bullet*)*X)->Pos = A_A_T::Target_Cal(((Bullet*)*X)->Pos, ((Bullet*)*X)->Angle, 1 * dt);
		}

		int Bullet_X = int(((Bullet*)*X)->Pos.x / Game_Model::pointer()->Game_Scale);
		int  Bullet_Z = int(((Bullet*)*X)->Pos.z / Game_Model::pointer()->Game_Scale);
		if (((Bullet_X - Player_X < Math::Square(Game_Model::pointer()->Room_Range)) && (Player_X - Bullet_X < Math::Square(Game_Model::pointer()->Room_Range))) && ((Bullet_Z - Player_Z < Math::Square(Game_Model::pointer()->Room_Range)) && (Player_Z - Bullet_Z < Math::Square(Game_Model::pointer()->Room_Range))))
		{
			((Bullet*)*X)->Clear();
		}
		else if (((Bullet*)*X)->Fly_Time <= 0)
		{
			((Bullet*)*X)->Clear();
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{

				if (Game_Model::pointer()->Enemy_Data[i].state != Game_Model::pointer()->Enemy_Data[i].Shut_Down)
				{
					int Enemy_X = int(Game_Model::pointer()->Enemy_Data[i].Position.x / Game_Model::pointer()->Game_Scale);
					int  Enemy_Z = int(Game_Model::pointer()->Enemy_Data[i].Position.z / Game_Model::pointer()->Game_Scale);
					if (((Bullet_X - Enemy_X < Math::Square(Game_Model::pointer()->Room_Range)) && (Enemy_X - Bullet_X < Math::Square(Game_Model::pointer()->Room_Range))) && ((Bullet_Z - Enemy_Z < Math::Square(Game_Model::pointer()->Room_Range)) && (Enemy_Z - Bullet_Z < Math::Square(Game_Model::pointer()->Room_Range))))
					{
						((Bullet*)*X)->Clear();
						Game_Model::pointer()->Enemy_Data[i].Teleport(i);
					}
				}
			}
		}
		if (((Bullet*)*X)->Fly_Time > 0)
		{
			((Bullet*)*X)->Fly_Time -= dt;
		}
	}


	if (Input_Controller::pointer()->HaveBeenPressed[Input_Controller::pointer()->Gun_Shoot] && Game_Model::pointer()->Gun_CD == 0)
	{
		for (std::vector<Bullet *>::iterator X = Game_Model::pointer()->Bullet_Data.begin(); X != Game_Model::pointer()->Bullet_Data.end(); ++X)
		{
			if (((Bullet*)*X)->Active == false)
			{
				Vector3 Pos = A_A_T::Target_Cal(Game_Model::pointer()->Current_Camera->camera.position, Game_Model::pointer()->Current_Camera->Angle, 0.5);
				((Bullet*)*X)->Shot(Pos, Game_Model::pointer()->Current_Camera->Angle, 0);
			}
		}
		Game_Model::pointer()->Gun_CD = 1;
	}
	if (Game_Model::pointer()->Gun_CD > 0)
	{
		Game_Model::pointer()->Gun_CD -= dt;
	}
	if (Game_Model::pointer()->Gun_CD < 0)
	{
		Game_Model::pointer()->Gun_CD = 0;
	}
}

void Gun_Scene::Render()
{

	Game_Model::pointer()->modelStack_Set(true);
	Vector3 Pos = Game_Model::pointer()->Current_Camera->camera.target;
	Pos.y = float(Game_Model::pointer()->Game_Scale) / 8;
	Game_Model::pointer()->modelStack_Define(Pos, -90 - Game_Model::pointer()->Current_Camera->Angle, Vector3(0, 1, 0), Vector3(Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale));
	Render_Function::RenderMesh(Render_Function::Mesh_Search("Pistol"), true);
	Game_Model::pointer()->modelStack_Set(false);

	for (std::vector<Bullet *>::iterator X = Game_Model::pointer()->Bullet_Data.begin(); X != Game_Model::pointer()->Bullet_Data.end(); ++X)
	{
		Bullet* Q = ((Bullet*)*X);
		if (Q->Active)
		{
			Game_Model::pointer()->modelStack_Set(true);
			Game_Model::pointer()->modelStack_Define(Q->Pos, Q->Angle, Vector3(0, 1, 0), Vector3(Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale));
			Render_Function::RenderMesh(Render_Function::Mesh_Search("Bullet"), true);
			Game_Model::pointer()->modelStack_Set(false);
		}
	}
}

void Gun_Scene::Exit()
{

}
