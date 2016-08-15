#ifndef GAME_MODEL
#define GAME_MODEL
#include "Light.h"
#include <vector>
#include "Light.h"
#include "GL\glew.h"
#include "LoadHmap.h"
#include "SpriteAnimation.h"
#include "Application.h"
#include <irrKlang.h>
#include "View.h"
#include "MatrixStack.h"
#include <fstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Angle_And_Target.h"
#include "Input_Controller.h"
#include "Enemy_Class.h"
#include "Bullet_Class.h"
using namespace irrklang;


class Game_Model
{
public:
	std::vector<unsigned char>m_heightMap;
	static Game_Model* pointer(){ return m_pointer; };
	unsigned Get_m_DataType(unsigned input){ return m_DataType[input]; };
	void Init();
	void Exit();
	void Render_Set();
	void modelStack_Set(bool switches);
	void modelStack_Define(Vector3 Translate, float Angle, Vector3 Rotate, Vector3 Scale);
	void Fog_Set(bool switches);
	enum DataType
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_cosCutOff,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		/*
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_cosCutOff,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		*/
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,
		Num_Data,
	};

	enum Game_Scenes
	{
		Game_Menu,
		Exit_Game,
	};
	//Gun Variable
	float Gun_CD;
	bool Tazer;

	//Game Variable
	std::vector<Mesh*> Mesh_Data;
	std::vector<Mesh*> Sprite_Data;
	std::vector<Scene*>Scene_Data;
	std::vector<Bullet*>Bullet_Data;
	Enemy_Class Enemy_Data[10];
	int game_current_scene;
	int BluePrint[100][100];
	unsigned int Game_Scale;
	unsigned int Room_Range;
	static View* Current_Camera;
	float Mouse_Sensitivity;
	Light lights[8];
	unsigned m_DataType[Num_Data];

	//Sound Variable
	ISoundEngine * SoundEngine;
	ISound* Environment_Sound;
	static MS modelStack;
	static MS viewStack;
	static MS projectionStack;

private:
	std::vector<unsigned char> Terrain;
	Game_Model(){};
	~Game_Model(){};
	unsigned m_vertexArrayID;
	unsigned m_programID;
	static Game_Model* m_pointer;


};

#endif