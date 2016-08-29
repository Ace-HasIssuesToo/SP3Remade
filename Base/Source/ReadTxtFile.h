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
<<<<<<< HEAD
	void RenderForAfter();
	void RenderTextForAfter();

	void EnterLoop();

=======
	Mesh* GetText();
>>>>>>> 99c5520e85fffbac70454a40e72ac1e955dcd0dd
	bool TimerStart;
	int sequence, order, next;
	float bgTimer;
	void tempGameplayFunction();

private:
	static ReadTxtFile* c_ReadTxtFile;

	vector<string> lineSplit(string input);
	vector<string> fullIntro, fullGameplay, fullAfter, tempGameplay;

	int storage, gpPointer, gpgpPointer, duringPointer;
	float introTimer;
	bool timerTime, timerReset, flashON, asylumON, release, duringPress;

	Mesh* intro_dialogue;
	Mesh* city;
	Mesh* flash;
	Mesh* asylum;
	Mesh* textbox;
};

#endif
