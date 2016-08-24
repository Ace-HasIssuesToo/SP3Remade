<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
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
	void Update(double dt);
	void Render();
	void Exit();

	void clearIntro();

	void RenderCity();
	void RenderFlash();
	void RenderAsylum();
	void RenderText();

	bool TimerStart;

private:
	static ReadTxtFile* c_ReadTxtFile;

	vector<string> fullIntro;

	float introTimer;
	bool timerTime, timerReset;
	int sequence;
	float bgTimer;
	bool flashON, asylumON;

	Mesh* intro_dialogue;
	Mesh* city;
	Mesh* flash;
	Mesh* asylum;
};

#endif
>>>>>>> 79ff990fb42d9294e37cbdfd317736105a83ef51
>>>>>>> 838ff66356b36601a1c7edd1213c4b29db182104
