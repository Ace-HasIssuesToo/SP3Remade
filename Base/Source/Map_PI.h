#ifndef MAP_PI
#define MAP_PI
#include "Support_Codes.h"

class Map
{
public:
	void Clear();
	void Render(Vector3 pos , bool Shadow);
	bool Init(std::string Filename);
	std::string Get_Type(Vector3 pos);
	static Vector3 Pokemon_Offset(Vector3 pos);
	static bool In_Range(Vector3 WorldPos, Vector3 pos);
	void SetLightRange(float lightrange);
	void RenderEvent(Vector3 pos,  bool Dark);
	Vector3 Map_Rand();
private:
	std::map<std::string, std::string> Map_Data;
	Vector3 Limitation;
};
static const float Light_Range = 3;
const float sizes = 10;
#endif