#ifndef DECOTEXT_PI
#define DECOTEXT_PI

#include "Support_Codes.h"

class DecoText
{
public:
	static DecoText* pointer(){ return m_pointer; };
	static string Get(std::string Deco_Name);
	static bool Set(std::string FileName);
	static void Init();
	static void Exit();
private:
	DecoText(){};
	~DecoText(){};
	static DecoText* m_pointer;
	std::map<std::string, std::string> Deco_Data;
};

#endif