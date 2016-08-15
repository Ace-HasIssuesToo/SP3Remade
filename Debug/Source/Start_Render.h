#ifndef START_RENDER
#define START_RENDER

#include "MatrixStack.h"
#include "Render_functions.h"
#include "Mtx44.h"
#include "View.h"
#include "Camera.h"


class Start_Render:public View
{
public:
	Start_Render();
	~Start_Render();
	virtual void Render3D();
	virtual void Render2D();
	void Set3Dview();
	void Set2Dview(bool Switch);
	void Render_Map(bool light);
private:

	Camera camera;
	static MS modelStack;
	static MS viewStack;
	static MS projectionStack;
};

#endif