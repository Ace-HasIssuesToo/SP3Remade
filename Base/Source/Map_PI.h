#ifndef MAP_PI
#define MAP_PI
#include "Support_Codes.h"

class Map
{
public:
	void Render(Vector3 pos , bool Shadow);
	bool Init(std::string Filename);
	std::string Get_Type(Vector3 pos);
	static Vector3 Pokemon_Offset(Vector3 pos);
	static bool In_Range(Vector3 WorldPos, Vector3 pos);
private:
	std::map<std::string, std::string> Map_Data;
	Vector3 Limitation;
	
};
<<<<<<< HEAD
const float Light_Range = 3;
=======
static const float Light_Range = 1;
>>>>>>> b76d3bc2a9360425fbd4e2fd91ee7242b22d5c60
const float sizes = 10;
#endif