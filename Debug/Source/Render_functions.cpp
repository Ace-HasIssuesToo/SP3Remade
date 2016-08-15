#include "Render_functions.h"
#include "GL\glew.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Game_Model.h"


Mesh* Render_Function::Mesh_Search(std::string Input_Controller, bool Sprite_Mesh_Using)
{
	std::vector<Mesh*> MeshList;
	if (Sprite_Mesh_Using)
	{
		MeshList = Game_Model::pointer()->Sprite_Data;
	}
	else
	{
		MeshList = Game_Model::pointer()->Mesh_Data;
	}
	Mesh* T = nullptr;
	for (std::vector<Mesh *>::iterator X = MeshList.begin(); X != MeshList.end(); ++X)
	{
		T = (Mesh *)*X;
		if (T->name == Input_Controller)
		{
			break;
		}
		else
		{
			T = nullptr;
		}
	}
	if (T == nullptr)
	{
		std::cout << Input_Controller << " Mesh isn't found!" << std::endl;
		system("pause");
	}
	return T;
}

void Render_Function::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureArray[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_ENABLED), 1);
	glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_COLOR), 1, &color.r);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 0);
	/*
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE), 0);
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 1);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE + i), i);
	}
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = Game_Model::pointer()->projectionStack.Top() * Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MVP), 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_ENABLED), 0);
	glEnable(GL_DEPTH_TEST);
}

void Render_Function::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)
		return;
	Game_Model::pointer()->modelStack.PushMatrix();
	Game_Model::pointer()->modelStack.Translate(x, y, 0);
	Game_Model::pointer()->modelStack.Scale(size, size, size);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_ENABLED), 1);
	glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_COLOR), 1, &color.r);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 0);
	/*
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureArray[0]);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE), 0);
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 1);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE + i), i);
	}
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = Game_Model::pointer()->projectionStack.Top() * Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MVP), 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_TEXT_ENABLED), 0);

	Game_Model::pointer()->modelStack.PopMatrix();
}

void Render_Function::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y)
{
	Game_Model::pointer()->modelStack.Scale(size, size, size);
	Game_Model::pointer()->modelStack.Translate(x, y, 0);

	Game_Model::pointer()->modelStack.PushMatrix();
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = Game_Model::pointer()->projectionStack.Top() * Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top();
	glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MVP), 1, GL_FALSE, &MVP.a[0]);
	if (enableLight)
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 1);
		modelView = Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top();
		int x = Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MODELVIEW);
		glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MODELVIEW), 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MODELVIEW_INVERSE_TRANSPOSE), 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_AMBIENT), 1, &mesh->material.kAmbient.r);
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_DIFFUSE), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_SPECULAR), 1, &mesh->material.kSpecular.r);
		glUniform1f(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_SHININESS), mesh->material.kShininess);
	}
	else
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 0);
	}
	/*
	if (mesh->textureID > 0)
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE), 0);
	}
	else
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 0);
	}
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; i++)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE + i), i);
		}
		else
		{
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 0);
		}
	}
	mesh->Render();
	if (mesh->textureArray[0] > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Game_Model::pointer()->modelStack.PopMatrix();

}

void Render_Function::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = Game_Model::pointer()->projectionStack.Top() * Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top();
	glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MVP), 1, GL_FALSE, &MVP.a[0]);
	

	modelView = Game_Model::pointer()->viewStack.Top() * Game_Model::pointer()->modelStack.Top();
	glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MODELVIEW), 1, GL_FALSE, &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	glUniformMatrix4fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MODELVIEW_INVERSE_TRANSPOSE), 1, GL_FALSE, &modelView.a[0]);
	
	if (enableLight)
	{

		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 1);
		//load material
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_AMBIENT), 1, &mesh->material.kAmbient.r);
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_DIFFUSE), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_SPECULAR), 1, &mesh->material.kSpecular.r);
		glUniform1f(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_MATERIAL_SHININESS), mesh->material.kShininess);
	}
	else
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_LIGHTENABLED), 0);
	}
	/*
	if (mesh->textureID > 0)
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE), 0);
	}
	else
	{
		glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED), 0);
	}
	*/
	for (int i = 0; i < mesh->MAX_TEXTURES; ++i)
	{
		if (mesh->textureArray[i] > 0)
		{
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 1);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh->textureArray[i]);
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE + i), i);
		}
		else
		{
			glUniform1i(Game_Model::pointer()->Get_m_DataType(Game_Model::pointer()->U_COLOR_TEXTURE_ENABLED + i), 0);
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
