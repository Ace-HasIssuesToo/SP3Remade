#ifndef INPUT_CONTROLLER
#define INPUT_CONTROLLER
#include "Main_Shaft.h"

class Input_PI :public Scene
{
public:
	static Input_PI* pointer()
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
		PokeThrowFront,
		PokeThrowBack,
		PokeThrowLeft,
		PokeThrowRight,
		DuringGP,
		Interact,
		IntroSkip,
		GameplayNext,
		Run,
		OnLight,
		OffLight,
		UseBattery,
		UseDrink,
		Phone_Switch,
		NextStatement,
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
	Input_PI(){};
	~Input_PI(){};
	static Input_PI* m_pointer;
	
};

#endif