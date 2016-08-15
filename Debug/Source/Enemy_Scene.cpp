#include "Enemy_Scene.h"

void Enemy_Scene::Init()
{
	Mesh* T_Mesh = new Mesh;
	T_Mesh = MeshBuilder::GenerateSpriteAnimation("Ghost", 1, 5);
	T_Mesh->textureArray[0] = LoadTGA("Data\\Enemies\\Ghost.tga");
	SpriteAnimation *T_Sprite = dynamic_cast<SpriteAnimation  *>(T_Mesh);
	if (T_Sprite)
	{
		T_Sprite->m_anim = new Animation();
		T_Sprite->m_anim->Set(0, 3, 0, 1.0f, true);
	}
	Game_Model::pointer()->Sprite_Data.push_back(T_Sprite);

	for (int i = 0; i <  10; i++)
	{
		Game_Model::pointer()->Enemy_Data[i].Create();
		Game_Model::pointer()->Enemy_Data[i].Teleport(i);
		Game_Model::pointer()->Enemy_Data[i].state = Game_Model::pointer()->Enemy_Data[0].Normal;
	}

}

void Enemy_Scene::Update(double dt)
{
	//Set Sprites
	for (std::vector<Mesh *>::iterator X = Game_Model::pointer()->Sprite_Data.begin(); X != Game_Model::pointer()->Sprite_Data.end(); ++X)
	{
		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>((Mesh*)*X);
		if (sa)
		{
			sa->Update(dt);
			sa->m_anim->animActive = true;
		}
	}
	//Move Enemy_Class
	for (int i = 0; i < 10; i++)
	{
		Game_Model::pointer()->Enemy_Data[i].AI_Movement(dt);
	}

}

void Enemy_Scene::Render()
{
	std::vector<int> Temp;
	unsigned int Range = INT_MAX;
	while (Temp.size() < 10)
	{
		signed int X = -1;
		for (int i = 0; i < 10; i++)
		{
			bool Run = true;
			for (std::vector<int>::iterator X = Temp.begin(); X != Temp.end(); ++X)
			{
				if (((int)*X) == i)
				{
					Run = false;
					break;
				}
			}
			if (Run)
			{
				unsigned int Range_Compare = Math::Square(Game_Model::pointer()->Enemy_Data[i].Position.x - Game_Model::pointer()->Current_Camera->camera.position.x) + Math::Square(Game_Model::pointer()->Enemy_Data[i].Position.z - Game_Model::pointer()->Current_Camera->camera.position.z);
				if (X < 0 || Range_Compare < Range)
				{
					Range = Range_Compare;
					X = i;
				}
			}
		}
		Temp.push_back(X);
	}

	for (std::vector<int>::iterator X = Temp.begin(); X != Temp.end(); ++X)
	{
		int i = ((int)*X);
		if (Game_Model::pointer()->Enemy_Data[i].state != Game_Model::pointer()->Enemy_Data[i].Shut_Down)
		{

		Game_Model::pointer()->modelStack_Set(true);
		Game_Model::pointer()->modelStack_Define(Game_Model::pointer()->Enemy_Data[i].Position, A_A_T::Angle(-90 - Game_Model::pointer()->Current_Camera->Angle), Vector3(0, 1, 0), Vector3(Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale, Game_Model::pointer()->Game_Scale));
		Render_Function::RenderMesh(Render_Function::Mesh_Search("Ghost", true), false);
		Game_Model::pointer()->modelStack_Set(false);

		}
	}
}

void Enemy_Scene::Exit()
{

}
