#include "Render_PI.h"
#include <sstream>

Render_PI* Render_PI::m_pointer = new Render_PI();

Vector3 Render_PI::Window_Scale()
{
	//Calculating aspect ratio
	float m_worldHeight = 100.f;
	float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	return Vector3(m_worldWidth,m_worldHeight,  0);
}

void Render_PI::Lights_Set(int i, Light light)
{
	Current_lights[i] = light;
}

void Render_PI::Camera_Set(Camera_PI camera)
{
	Current_Camera = camera;
}

Position Transform(Vector3 A)
{
	return Position(A.x, A.y, A.z);
}

Vector3 Transform(Position A)
{
	return Vector3(A.x, A.y, A.z);
}

Light Test_Control(Light Input)
{
	if (Application::IsKeyPressed('W'))
		Input.position.y += 0.1;
	if (Application::IsKeyPressed('S'))
		Input.position.y -= 0.1;
	if (Application::IsKeyPressed('A'))
		Input.position.z += 0.1;
	if (Application::IsKeyPressed('D'))
		Input.position.z -= 0.1;
	if (Application::IsKeyPressed('Q'))
		Input.position.x += 0.1;
	if (Application::IsKeyPressed('E'))
		Input.position.x -= 0.1;
	if (Application::IsKeyPressed('Z'))
		Input.power += 0.1;
	if (Application::IsKeyPressed('X'))
		Input.power -= 0.1;
	return Input;
}

void Render_PI::Init()
{
	Math::InitRNG();

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


	Current_lights[0].type = Light::LIGHT_SPOT;
	Current_lights[0].position.Set(0, 0, 0);
	Current_lights[0].color.Set(1, 1, 1);
	Current_lights[0].power = 100;
	Current_lights[0].kC = 1.f;
	Current_lights[0].kL = 0.01f;
	Current_lights[0].kQ = 0.001f;
	Current_lights[0].cosCutOff = cos(Math::DegreeToRadian(20));
	Current_lights[0].cosInner = cos(Math::DegreeToRadian(5));
	Current_lights[0].exponent = 3.f;
	Current_lights[0].spotDirection.Set(0.f, 1.f, 0.f);


	glUniform1i(m_DataType[U_NUMLIGHTS], 1);

	glUniform1i(m_DataType[U_TEXT_ENABLED], 0);

	glUniform1i(m_DataType[U_LIGHT0_TYPE], Current_lights[0].type);
	glUniform3fv(m_DataType[U_LIGHT0_COLOR], 1, &Current_lights[0].color.r);
	glUniform1f(m_DataType[U_LIGHT0_POWER], Current_lights[0].power);
	glUniform1f(m_DataType[U_LIGHT0_KC], Current_lights[0].kC);
	glUniform1f(m_DataType[U_LIGHT0_KL], Current_lights[0].kL);
	glUniform1f(m_DataType[U_LIGHT0_KQ], Current_lights[0].kQ);
	glUniform1f(m_DataType[U_LIGHT0_cosCutOff], Current_lights[0].cosCutOff);
	glUniform1f(m_DataType[U_LIGHT0_COSINNER], Current_lights[0].cosInner);
	glUniform1f(m_DataType[U_LIGHT0_EXPONENT], Current_lights[0].exponent);

	
	Color fogColor(0.2,0.2,0.2);
	glUniform3fv(m_DataType[U_FOG_COLOR], 1, &fogColor.r); //SPECIAL
	glUniform1f(m_DataType[U_FOG_START], 0);
	glUniform1f(m_DataType[U_FOG_END], 5*5);
	glUniform1f(m_DataType[U_FOG_DENSITY], 0.01f);
	glUniform1f(m_DataType[U_FOG_TYPE], 0);
	glUniform1f(m_DataType[U_FOG_ENABLED], 0);
	Current_Camera.Init(Vector3(5, 5, 5), Vector3(0, 0, 0), Vector3(0, 1, 0), 0, 0);
	

}

void Render_PI::Fog_Set(bool switches)
{
	if (switches)
	{
		glUniform1i(m_DataType[U_FOG_ENABLED], 0);
	}
	else
	{
		glUniform1i(m_DataType[U_FOG_ENABLED], 0);
	}
}

void Render_PI::Render_Set()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	Ortho = false;

	// Camera_PI matrix
	viewStack.LoadIdentity();

	viewStack.LookAt(
		Current_Camera.position.x, Current_Camera.position.y, Current_Camera.position.z,
		Current_Camera.target.x, Current_Camera.target.y, Current_Camera.target.z,
		Current_Camera.up.x, Current_Camera.up.y, Current_Camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if (Current_lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(Current_lights[0].position.x, Current_lights[0].position.y, Current_lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_DataType[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (Current_lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * Current_lights[0].position;
		glUniform3fv(m_DataType[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * Current_lights[0].spotDirection;
		glUniform3fv(m_DataType[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * Current_lights[0].position;
		glUniform3fv(m_DataType[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
}

void Render_PI::Ortho_Set(bool Ortho)
{
	if (this->Ortho != Ortho)
	{
		if (Ortho)
		{
			glDisable(GL_DEPTH_TEST);
			Mtx44 ortho;
			Vector3 Window_ = Window_Scale();
			ortho.SetToOrtho(0, Window_.y, 0, Window_.x, -10, 10);
			projectionStack.PushMatrix();
			projectionStack.LoadMatrix(ortho);
			viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
			modelStack.LoadIdentity();
		}
		else
		{
			viewStack.PopMatrix();
			projectionStack.PopMatrix();
			glEnable(GL_DEPTH_TEST);
		}
		this->Ortho = Ortho;
	}
}

void  Render_PI::modelStack_Set(bool switches)
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

void Render_PI::modelStack_Define(Vector3 Translate, float Angle, Vector3 Rotate, Vector3 Scale)
{
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	if (Rotate != Vector3())
	{
		modelStack.Rotate(Angle, Rotate.x, Rotate.y, Rotate.z);
	}
	if (Scale.x != 0 && Scale.y != 0 && Scale.z != 0)
	{
		modelStack.Scale(Scale.x, Scale.y, Scale.z);
	}
}

void Render_PI::Exit()
{
	if (m_pointer != nullptr)
	{
		delete m_pointer;
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Render_PI::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_DataType[U_TEXT_ENABLED], 1);
	glUniform3fv(m_DataType[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_DataType[U_LIGHTENABLED], 0);
	/*
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_DataType[U_COLOR_TEXTURE), 0);
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
		glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 1);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
		glUniform1i(m_DataType[U_COLOR_TEXTURE + i], i);
	}
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_DataType[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_DataType[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Render_PI::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, Vector3 Translate, Vector3 Scale)
{
	if (this->Ortho == false)
	{
			glDisable(GL_DEPTH_TEST);
			Mtx44 ortho;
			Vector3 Window_ = Window_Scale();
			ortho.SetToOrtho(0, Window_.x, 0, Window_.y, -10, 10);
			projectionStack.PushMatrix();
			projectionStack.LoadMatrix(ortho);
			viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
			modelStack.LoadIdentity();
	}

	if (!mesh || mesh->textureID <= 0)
		return;
	modelStack.PushMatrix();
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	modelStack.Scale(Scale.x, Scale.y, Scale.z);
	glUniform1i(m_DataType[U_TEXT_ENABLED], 1);
	glUniform3fv(m_DataType[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_DataType[U_LIGHTENABLED], 0);
	/*
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(m_DataType[U_COLOR_TEXTURE), 0);
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
		glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 1);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
		glUniform1i(m_DataType[U_COLOR_TEXTURE + i], i);
	}
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_DataType[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_DataType[U_TEXT_ENABLED], 0);

	modelStack.PopMatrix();

	if (this->Ortho == false)
	{
		viewStack.PopMatrix();
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}

void Render_PI::RenderMeshIn2D(Mesh *mesh, bool enableLight, Vector3 Translate, Vector3 Scale)
{
	if (this->Ortho == false)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		Vector3 Window_ = Window_Scale();
		ortho.SetToOrtho(0, Window_.x, 0, Window_.y, -10, 10);
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
		viewStack.LoadIdentity();
		modelStack.PushMatrix();
		modelStack.LoadIdentity();

	}

	modelStack.PushMatrix();
	modelStack.Translate(Translate.x, Translate.y, Translate.z);
	modelStack.Scale(Scale.x, Scale.y, Scale.z);
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_DataType[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight)
	{
		glUniform1i(m_DataType[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		int x = m_DataType[U_MODELVIEW];
		glUniformMatrix4fv(m_DataType[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_DataType[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(m_DataType[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_DataType[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_DataType[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_DataType[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_DataType[U_LIGHTENABLED], 0);
	}
	/*
	if (mesh->textureID > 0)
	{
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_DataType[U_COLOR_TEXTURE), 0);
	}
	else
	{
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 0);
	}
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_DataType[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	if (mesh->textureArray[0] > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();

	if (this->Ortho == false)
	{
		viewStack.PopMatrix();
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

}

void Render_PI::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_DataType[U_MVP], 1, GL_FALSE, &MVP.a[0]);


	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_DataType[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	glUniformMatrix4fv(m_DataType[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{

		glUniform1i(m_DataType[U_LIGHTENABLED], 1);
		//load material
		glUniform3fv(m_DataType[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_DataType[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_DataType[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_DataType[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_DataType[U_LIGHTENABLED], 0);
	}
	/*
	if (mesh->textureID > 0)
	{
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_DataType[U_COLOR_TEXTURE), 0);
	}
	else
	{
	glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED), 0);
	}
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(m_DataType[U_COLOR_TEXTURE + i], i);
		}
		else
		{
			glUniform1i(m_DataType[U_COLOR_TEXTURE_ENABLED + i], 0);
		}
	}
	mesh->Render();
	/*
	if (mesh->textureArray[0] > 0)
	{
	glBindTexture(GL_TEXTURE_2D, 0);
	}
	*/
}
