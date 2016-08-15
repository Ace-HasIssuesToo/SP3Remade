#ifndef VIEW
#define VIEW
#include "Camera.h"

class View
{
public:
	View(){};
	~View(){};
	Camera camera;
	float Angle;
};

#endif