#ifndef START_SYSTEM
#define START_SYSTEM

#include "System.h"
#include "Game_Model.h"
#include "Application.h"
#include "Actions.h"

class Start_System : public System
{
public:
	virtual void Update(float dt);

	Player* X;

};
#endif