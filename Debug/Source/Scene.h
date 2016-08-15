#ifndef SCENE
#define SCENE

class Scene
{
public:
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};
#endif