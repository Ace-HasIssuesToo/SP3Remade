#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER
#include "Game_Core.h"

class Input_Controller :public Scene
{
public:
	static Input_Controller* pointer()
	{
		return m_pointer;
	}
	enum Controls
	{
		Nothing = 0,
		Forward,
		Backward,
		Leftward,
		Rightward,
		Light_Switch,
		Gun_Shoot,
		Interact,
		Run,
		Phone_Switch,
		All_Control,
	};
	bool IsBeingPressed[All_Control];
	bool HaveBeenPressed[All_Control];

	virtual void Init();
	void Clear();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	Input_Controller(){};
	~Input_Controller(){};
	static Input_Controller* m_pointer;
	
};

#endif