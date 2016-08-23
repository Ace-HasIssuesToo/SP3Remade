#ifndef READTXTFILE_H
#define READTXTFILE_H

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class ReadTxtFile
{
public:
	ReadTxtFile();
	~ReadTxtFile();

	static ReadTxtFile* pointer() { return c_ReadTxtFile; };

	void Init();
	void ReadFromTextFile();
	vector<string> lineSplit(string input);
	void Render();
	void Exit();

private:
	static ReadTxtFile* c_ReadTxtFile;

	vector<string> fullIntro;

	float introTimer;

	Mesh* intro_dialogue;
};

#endif