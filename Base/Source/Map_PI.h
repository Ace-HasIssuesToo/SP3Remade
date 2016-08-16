#ifndef MAP_PI
#define MAP_PI
#include "Support_Codes.h"

class Map
{
public:
	void Render(Vector3 pos);
	bool Init(std::string Filename);
	std::string Get_Type(Vector3 pos);
private:
	std::map<std::string, std::string> Map_Data;
	Vector3 Limitation;
};

#endif