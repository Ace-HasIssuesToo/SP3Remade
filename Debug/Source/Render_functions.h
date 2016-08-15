#ifndef RENDER_FUNCTIONS
#define RENDER_FUNCTIONS

#include "Mesh.h"
#include "Vertex.h"
#include "MatrixStack.h"
#include <string>

class Render_Function
{
public:
	static Mesh* Mesh_Search(std::string Input_Controller, bool Sprite_Mesh_Using = false);
	static void RenderText(Mesh* mesh, std::string text, Color color);
	static void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	static void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y);
	static void RenderMesh(Mesh *mesh, bool enableLight);
};

#endif