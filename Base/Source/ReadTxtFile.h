#ifndef READTXTFILE_H
#define READTXTFILE_H

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"
#include "irrKlang.h"

using namespace irrklang;

class ReadTxtFile
{
public:
	ReadTxtFile();
	~ReadTxtFile();

	static ReadTxtFile* pointer() { return c_ReadTxtFile; };

	void Init();
	void ReadFromTextFile();
	void Update(double dt);
	void FloorUpdate(double dt);
	void RenderForIntro();
	void RenderForGameplay();
	void Exit();

	void SetStorage(int storage);
	int GetStorage();

	void clearIntro();

	void RenderCity();
	void RenderFlash();
	void RenderAsylum();
	void RenderTextForIntro();
	void RenderTextForGameplay();
	void RenderTextBox();
	void RenderForAfter();
	void RenderTextForAfter();
	void MusicInit();

	void EnterLoop();

	bool TimerStart;
	int sequence, order, next;
	float bgTimer;
	void tempGameplayFunction();

	// Sound Engine
	ISoundSource* introMusic;

private:
	static ReadTxtFile* c_ReadTxtFile;

	vector<string> lineSplit(string input);
	vector<string> fullIntro, fullGameplay, fullAfter, tempGameplay;

	int storage, gpPointer, gpgpPointer, duringPointer;
	float introTimer;
	bool timerTime, timerReset, flashON, asylumON, release, duringPress, introSound;

	Mesh* intro_dialogue;
	Mesh* city;
	Mesh* flash;
	Mesh* asylum;
	Mesh* textbox;
};

#endif
