#ifndef TEXTURE_PI
#define TEXTURE_PI

#include "Support_Codes.h"

class Texture
{
public:
	static Mesh* Get(std::string Mesh_Name);
	static bool Set(Mesh* Mesh_);
	static bool Set(std::string FileName);
	static void Init();
	static void Exit();
private:
	Texture(){};
	~Texture(){};
	static Texture* m_pointer;
	std::map<std::string, Mesh*> Textures_Data;
};

#endif