#ifndef GAME_MODEL
#define GAME_MODEL
#include "Support_Codes.h"
#include "Scene.h"


class Render_PI
{
public:
	static Vector3 Window_Scale();
	static Render_PI* pointer(){ return m_pointer; };
	void Init();
	void Exit();
	void Render_Set();
	void modelStack_Set(bool switches);
	void modelStack_Define(Vector3 Translate, float Angle, Vector3 Rotate, Vector3 Scale);
	void Fog_Set(bool switches);
	void Ortho_Set(bool Ortho);
	bool Ortho_Get(){ return Ortho; };
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, Vector3 Translate, Vector3 Scale);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, Vector3 Translate, Vector3 Scale);
	void RenderMesh(Mesh *mesh, bool enableLight);
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
	void Lights_Set(int i, Light light);
	void Camera_Set(Camera_PI camera);


private:
	bool Ortho;
	Camera_PI Current_Camera;
	Light Current_lights[8];
	unsigned m_DataType[Num_Data];
	Render_PI(){};
	~Render_PI(){};
	unsigned m_vertexArrayID;
	unsigned m_programID;
	static Render_PI* m_pointer;
	MS modelStack;
	MS viewStack;
	MS projectionStack;

};

#endif