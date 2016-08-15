#include "Light_Scene.h"

Position Transform(Vector3 A)
{
	return Position(A.x, A.y, A.z);
}
Vector3 Transform(Position A)
{
	return Vector3(A.x, A.y, A.z);
}

void Light_Scene::Init()
{

	Game_Model::pointer()->lights[0].type = Light::LIGHT_SPOT;
	Game_Model::pointer()->lights[0].position.Set(1.5 * Game_Model::pointer()->Game_Scale, 0.5 * Game_Model::pointer()->Game_Scale, 1.5 * Game_Model::pointer()->Game_Scale);
	Game_Model::pointer()->lights[0].color.Set(1, 1, 1);
	Game_Model::pointer()->lights[0].power = 0;
	Game_Model::pointer()->lights[0].kC = 1.f;
	Game_Model::pointer()->lights[0].kL = 0.01f;
	Game_Model::pointer()->lights[0].kQ = 0.001f;
	Game_Model::pointer()->lights[0].cosCutOff = cos(Math::DegreeToRadian(10));
	Game_Model::pointer()->lights[0].cosInner = cos(Math::DegreeToRadian(10));
	Game_Model::pointer()->lights[0].exponent = 3.f;
	Game_Model::pointer()->lights[0].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_TYPE], Game_Model::pointer()->lights[0].type);
	glUniform3fv(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_COLOR], 1, &Game_Model::pointer()->lights[0].color.r);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_POWER], Game_Model::pointer()->lights[0].power);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_KC], Game_Model::pointer()->lights[0].kC);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_KL], Game_Model::pointer()->lights[0].kL);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_KQ], Game_Model::pointer()->lights[0].kQ);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_cosCutOff], Game_Model::pointer()->lights[0].cosCutOff);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_COSINNER], Game_Model::pointer()->lights[0].cosInner);
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_EXPONENT], Game_Model::pointer()->lights[0].exponent);

	glUniform1i(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_NUMLIGHTS], 1);
}

void Light_Scene::Update(double dt)
{
	glUniform1f(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_POWER], Game_Model::pointer()->lights[0].power);

}

void Light_Scene::Render()
{
	if (Game_Model::pointer()->lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(Game_Model::pointer()->lights[0].position.x, Game_Model::pointer()->lights[0].position.y, Game_Model::pointer()->lights[0].position.z);
		Vector3 lightDirection_cameraspace = Game_Model::pointer()->viewStack.Top() * lightDir;
		glUniform3fv(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (Game_Model::pointer()->lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = Transform(Game_Model::pointer()->viewStack.Top() * Transform(Game_Model::pointer()->lights[0].position));
		glUniform3fv(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->lights[0].spotDirection;
		glUniform3fv(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = Transform(Game_Model::pointer()->viewStack.Top() * Transform(Game_Model::pointer()->lights[0].position));
		glUniform3fv(Game_Model::pointer()->m_DataType[Game_Model::pointer()->U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

void Light_Scene::Exit()
{

}
