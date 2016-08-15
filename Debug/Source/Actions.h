#ifndef ACTIONS
#define ACTIONS

#include "System.h"

class Actions: public System
{
public:
	virtual void Update(float dt);
	static Actions* Pointer(){ return m_pointer; };
	bool Get_actions(int Input){ return actions[Input]; };
	enum actions_type
	{
		Default,
		jump,
		Num_Actions,
	};
private:
	Actions(){};
	void Clear_Action()
	{
		for (int i = 0; i < Num_Actions; i++)
		{
			actions[i] = false;
		}
	};
	~Actions(){ delete m_pointer; };
	bool actions[Num_Actions];
	static Actions* m_pointer;
};
#endif