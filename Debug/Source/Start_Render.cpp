#include "Start_Render.h"
#include "Game_Model.h"
#include "Application.h"

MS Start_Render::modelStack;
MS Start_Render::viewStack;
MS Start_Render::projectionStack;

Start_Render::Start_Render()
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	camera.Init(Vector3(-1,1,-1),Vector3(0,0,0),Vector3(0,1,0));
}

Vector3 PtoV(Position Input)
{
	return Vector3(Input.x, Input.y, Input.z);
};
Position VtoP(Vector3 Input)
{
	return Position(Input.x, Input.y, Input.z);
};

void Start_Render::Set3Dview()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();
	camera = Game_Model::pointer()->Start_cam.Get_camera();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if (Game_Model::pointer()->Get_lights(0).type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(Game_Model::pointer()->Get_lights(0).position.x, Game_Model::pointer()->Get_lights(0).position.y, Game_Model::pointer()->Get_lights(0).position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::U_LIGHT0_POSITION), 1, &lightDirection_cameraspace.x);
	}
	else if (Game_Model::pointer()->Get_lights(0).type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = VtoP(viewStack.Top() * PtoV(Game_Model::pointer()->Get_lights(0).position));
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::U_LIGHT0_POSITION), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * Game_Model::pointer()->Get_lights(0).spotDirection;
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::U_LIGHT0_SPOTDIRECTION), 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = VtoP(viewStack.Top() * PtoV(Game_Model::pointer()->Get_lights(0).position));
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::U_LIGHT0_POSITION), 1, &lightPosition_cameraspace.x);
	}
}

void Start_Render::Set2Dview(bool Switch)
{
	if (Switch)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
		modelStack.LoadIdentity();
	}
	else
	{
		modelStack.PopMatrix();
		viewStack.PopMatrix();
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}


void Start_Render::Render3D()
{
	Set3Dview();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Axes).Get_mesh(), false, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();



	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	Render_Map(true);
	modelStack.PopMatrix();
	
	
	
}


void Start_Render::Render2D()
{
	Set2Dview(true);
	float X_Pos = ((Application::mouse_current_x - 100)/600)*15;
	float Y_Pos = ((400 - (Application::mouse_current_y - 100))/400)*10;

	std::cout << X_Pos << " / " << Y_Pos << std::endl;
	modelStack.PushMatrix();
	Render_Function::RenderMeshIn2D(Game_Model::pointer()->Get_m_object(Game_Model::Aim).Get_mesh(), false, 5, X_Pos, Y_Pos, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	Render_Function::RenderTextOnScreen(Game_Model::pointer()->Get_m_object(Game_Model::Text).Get_mesh(), "PHONE RINGS", Color(1, 0, 0), 5, 5, 50, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	Color color = Color(0.3, 0.3, 0.3);
	if (X_Pos >= 0.6 && X_Pos <= 5 && Y_Pos >= 6.0 && Y_Pos <= 6.4)
	{
		color = Color(1, 0, 0);
	}
	modelStack.PushMatrix();
	Render_Function::RenderTextOnScreen(Game_Model::pointer()->Get_m_object(Game_Model::Text).Get_mesh(), "NEW CALL", color, 3, 3,30, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	color = Color(0.3, 0.3, 0.3);
	if (X_Pos >= 0.675 && X_Pos <= 7.9 && Y_Pos >= 4.2 && Y_Pos <= 4.4)
	{
		color = Color(1, 0, 0);
	}
	modelStack.PushMatrix();
	Render_Function::RenderTextOnScreen(Game_Model::pointer()->Get_m_object(Game_Model::Text).Get_mesh(), "CONTINUE CALL", color, 3, 3, 20, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	color = Color(0.3, 0.3, 0.3);
	if (X_Pos >= 0.6 && X_Pos <= 5 && Y_Pos >= 2.0 && Y_Pos <= 2.4)
	{
		color = Color(1, 0, 0);
	}
	modelStack.PushMatrix();
	Render_Function::RenderTextOnScreen(Game_Model::pointer()->Get_m_object(Game_Model::Text).Get_mesh(), "END CALL", color, 3, 3, 10, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();
	Set2Dview(false);
}


void Start_Render::Render_Map(bool light)
{
	int i = floor(camera.position.x);
	int j = floor(camera.position.z);
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 10, camera.position.z);
	modelStack.Scale(0.01, 0.01, 0.01);
	Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Sky).Get_mesh(), false, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(50, 0, 50);
	modelStack.Scale(100,5,100);
	Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Ground).Get_mesh(), false, modelStack, viewStack, projectionStack);
	modelStack.PopMatrix();

	if (i < 5)
	{
		i = 5;
	}
	if (j < 5)
	{
		j = 5;
	}
	if (i > 94)
	{
		i = 94;
	}
	if (j > 94)
	{
		j = 94;
	}
	for (int x = i - 5; x < i + 5; x++)
	{
		for (int z = j - 5; z < j + 5; z++)
		{
			if (Game_Model::pointer()->Get_Forest(x, z) == char('W'))
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, Game_Model::pointer()->Get_Terrin_Height(x / 100, z / 100) * 5, z);
				Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Wall).Get_mesh(), light,  modelStack, viewStack, projectionStack);
				modelStack.PopMatrix();
			}
			else if (Game_Model::pointer()->Get_Forest(x, z) == char('T'))
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, Game_Model::pointer()->Get_Terrin_Height(x / 100, z / 100) *5, z);
				modelStack.Rotate((x*z), 0, 1, 0);
				Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Tree).Get_mesh(), light, modelStack, viewStack, projectionStack);
				modelStack.PopMatrix();
			}
			else if (Game_Model::pointer()->Get_Forest(x, z) == char('R'))
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, Game_Model::pointer()->Get_Terrin_Height(x / 100, z / 100) *5, z);
				modelStack.Rotate((x*z), 0, 1, 0);
				Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Rock).Get_mesh(), light, modelStack, viewStack, projectionStack);
				modelStack.PopMatrix();
			}
			else if (Game_Model::pointer()->Get_Forest(x, z) == char('L'))
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, Game_Model::pointer()->Get_Terrin_Height(x / 100, z / 100) *5, z);
				modelStack.Rotate((x*z), 0, 1, 0);
				Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Log).Get_mesh(), light, modelStack, viewStack, projectionStack);
				modelStack.PopMatrix();
			}
			else if (Game_Model::pointer()->Get_Forest(x, z) == char('B'))
			{
				modelStack.PushMatrix();
				modelStack.Translate(x, Game_Model::pointer()->Get_Terrin_Height(x / 100, z / 100) *5, z);
				modelStack.Rotate((x*z), 0, 1, 0);
				Render_Function::RenderMesh(Game_Model::pointer()->Get_m_object(Game_Model::Bush).Get_mesh(), light, modelStack, viewStack, projectionStack);
				modelStack.PopMatrix();
			}
		}
	}
}