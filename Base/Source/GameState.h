#pragma once
using namespace std;
class GameState
{
	
	
public:
	

	static GameState* pointer(){ return c_pointer; };
private:
	static GameState* c_pointer;
};