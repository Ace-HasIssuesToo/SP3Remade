#ifndef EVENT
#define EVENT
#include "Map_PI.h"

class Event
{
public:
	static Event* pointer(){ return m_pointer; };
	void Init();
	void Update(double dt, Map* map);
	void Render(Map* map, Vector3 pos);
	void Exit();
	void Clear();
	bool check_Effect(){ return bool(current_Effect); };
	void Set_Multiplier(int Multiplier){ RandMultiplier = Multiplier; };

private:
	Event(){};
	~Event(){};
	static Event* m_pointer;
	enum Effects
	{
		No_Effect,
		Lightning,
		BlackOut,
		Stun,
		All_Effect,
	};
	Effects current_Effect;
	float Effect_Time;
	int RandMultiplier;
	bool Black;
	float FlashDelay;
	float LastTime, CurrentTime;
};

#endif