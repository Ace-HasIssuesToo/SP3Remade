#ifndef SUPPORT_CODES
#define SUPPORT_CODES

#include "Vector3.h"
#include "Mtx44.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "MyMath.h"
#include <irrKlang.h>
#include "MatrixStack.h"
#include "Application.h"
#include "Camera_PI.h"

using namespace irrklang;
using namespace std;

struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};
Position operator*(const Mtx44& lhs, const Position& rhs);

struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};

struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
	Vertex(){}
};

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	Material()
	{
		//some default values
		kAmbient.Set(0.1f, 0.1f, 0.1f);
		kDiffuse.Set(0.6f, 0.6f, 0.6f);
		kSpecular.Set(0.3f, 0.3f, 0.3f);
		kShininess = 5.f;
	}
};

struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Position position;
	Color color;
	float power;
	float kC;
	float kL;
	float kQ;
	Vector3 spotDirection;
	float cosCutOff;
	float cosInner;
	float exponent;

	Light()
	{
		type = LIGHT_POINT;
		color.Set(1, 1, 1);
		power = 1.f;
		kC = 1.f;
		kL = 0.f;
		kQ = 0.f;
		cosCutOff = cosInner = 0.8f;
		exponent = 1.f;
	}
};


GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
GLuint LoadTGA(const char *file_path);
bool LoadOBJ(
	const char *file_path,
	std::vector<Position> & out_vertices,
	std::vector<TexCoord> & out_uvs,
	std::vector<Vector3> & out_normals
	);

void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
	);


class Mesh
{
public:
	static const int MAX_TEXTURES = 2;

	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(){};
	Mesh(const std::string &meshName);
	~Mesh();
	virtual void Render();
	void Render(unsigned offset, unsigned count);

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;

	Material material;
	unsigned textureID;
	unsigned textureArray[MAX_TEXTURES];


};


struct Animation {
	Animation() {};
	void Set(int startFrame, int endFrame, int repeat, float time, bool active)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this->animTime = time;
		this->animActive = active;
	};
	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
	bool animActive;
};

class SpriteAnimation : public Mesh {
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();
	void Play(float dt);
	void Update(double dt);
	virtual void Render();
	int m_row;
	int m_col;
	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};

class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX = 0.0f, float lengthY = 0.0f, float lengthZ = 0.0f);
	static Mesh* GenerateCrossHair(const std::string &meshName, float colour_r = 1.0f, float colour_g = 1.0f, float colour_b = 0.0f, float length = 1.0f);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR = 1.f, float innerR = 0.f);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius = 1.f);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned row, unsigned col);

	//TSL
	static Mesh* GenerateSkyPlane(const std::string &meshName, Color color, int slices, float PlanetRadius, float AtmosphereRadius, float hTile, float vTile);
	static Mesh* GenerateTerrain(const std::string &meshName, const std::string &file_path, std::vector<unsigned char> &heightMap);
	static SpriteAnimation* GenerateSpriteAnimation(const std::string &meshName, unsigned numRow, unsigned numCol);
};

bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap);

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z);



#endif