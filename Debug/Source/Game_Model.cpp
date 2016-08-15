#include "Game_Model.h"
#include "shader.hpp"
#include "Utility.h"
#include <sstream>
#include "Light_Scene.h"

Game_Model* Game_Model::m_pointer = new Game_Model();
View* Game_Model::Current_Camera = new View();
MS Game_Model::modelStack;
MS Game_Model::viewStack;
MS Game_Model::projectionStack;

void Game_Model::Init()
{
	Math::InitRNG();
	Game_Scale = 5;
	Room_Range = 2;

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	//m_programID = LoadShaders("Shader//comg.vertexshader", "Shader//MultiText.fragmentshader");
	m_programID = LoadShaders("Shader//Fog.vertexshader", "Shader//Fog.fragmentshader"); //week 7

	// Get a handle for our uniform
	m_DataType[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_DataType[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_DataType[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_DataType[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_DataType[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_DataType[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_DataType[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_DataType[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_DataType[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_DataType[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_DataType[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_DataType[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_DataType[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_DataType[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_DataType[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_DataType[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_DataType[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_DataType[U_LIGHT0_cosCutOff] = glGetUniformLocation(m_programID, "lights[0].cosCutOff");
	m_DataType[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_DataType[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	/*
	m_DataType[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_DataType[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_DataType[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_DataType[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_DataType[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_DataType[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_DataType[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_DataType[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_DataType[U_LIGHT1_cosCutOff] = glGetUniformLocation(m_programID, "lights[1].cosCutOff");
	m_DataType[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_DataType[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	*/
	// Get a handle for our "colorTexture" uniform
	m_DataType[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_DataType[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_DataType[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_DataType[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");
	// Get a handle for our "textColor" uniform
	m_DataType[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_DataType[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	//fog
	m_DataType[U_FOG_COLOR] = glGetUniformLocation(m_programID, "fogParam.color");
	m_DataType[U_FOG_START] = glGetUniformLocation(m_programID, "fogParam.start");
	m_DataType[U_FOG_END] = glGetUniformLocation(m_programID, "fogParam.end");
	m_DataType[U_FOG_DENSITY] = glGetUniformLocation(m_programID, "fogParam.density");
	m_DataType[U_FOG_TYPE] = glGetUniformLocation(m_programID, "fogParam.type");
	m_DataType[U_FOG_ENABLED] = glGetUniformLocation(m_programID, "fogParam.enabled");
	
	// Use our shader
	glUseProgram(m_programID);


	glUniform1i(m_DataType[U_TEXT_ENABLED], 0);
	
	Color fogColor(0.2,0.2,0.2);
	glUniform3fv(m_DataType[U_FOG_COLOR], 1, &fogColor.r); //SPECIAL
	glUniform1f(m_DataType[U_FOG_START], 0);
	glUniform1f(m_DataType[U_FOG_END], Game_Scale*Room_Range);
	glUniform1f(m_DataType[U_FOG_DENSITY], 1.0f);
	glUniform1f(m_DataType[U_FOG_TYPE], 0);
	glUniform1f(m_DataType[U_FOG_ENABLED], 1);
	
	


}


void Game_Model::Fog_Set(bool switches)
{
	if (switches)
	{
		glUniform1f(m_DataType[U_FOG_DENSITY], (1.1f - Game_Model::pointer()->lights[0].power));
		glUniform1i(m_DataType[U_FOG_ENABLED], 1);
	}
	else
	{
		glUniform1i(m_DataType[U_FOG_ENABLED], 0);
	}
}

void Game_Model::Render_Set()
{
	/*
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();

	Current_Camera->camera.target = A_A_T::Target_Cal(Current_Camera->camera.position, Current_Camera->Angle, 0.1);
	viewStack.LookAt(
		Current_Camera->camera.position.x, Current_Camera->camera.position.y, Current_Camera->camera.position.z,
		Current_Camera->camera.target.x, Current_Camera->camera.target.y, Current_Camera->camera.target.z,
		Current_Camera->camera.up.x, Current_Camera->camera.up.y, Current_Camera->camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();


}

void  Game_Model::modelStack_Set(bool switches)
{
	if (switches)
	{
		modelStack.PushMatrix();
	}
	else
	{
		modelStack.PopMatrix();
	}
}

void Game_Model::modelStack_Define(Vector3 Translate, float Angle, Vector3 Rotate, Vector3 Scale)
{
	Game_Model::pointer()->modelStack.Translate(Translate.x, Translate.y, Translate.z);
	if (Rotate != Vector3())
	{
		Game_Model::pointer()->modelStack.Rotate(Angle, Rotate.x, Rotate.y, Rotate.z);
	}
	if (Scale.x != 0 && Scale.y != 0 && Scale.z != 0)
	{
		Game_Model::pointer()->modelStack.Scale(Scale.x, Scale.y, Scale.z);
	}
}

void Game_Model::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
	}
	/*
	if (SoundEngine != nullptr)
		SoundEngine->drop();
		*/
	while (!Mesh_Data.empty())
	{
		Mesh* D = Mesh_Data.back();
		delete D;
		Mesh_Data.pop_back();
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

