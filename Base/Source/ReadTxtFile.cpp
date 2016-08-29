#include "ReadTxtFile.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"
#include "SoundEngine.h"

ReadTxtFile* ReadTxtFile::c_ReadTxtFile = new ReadTxtFile();

ReadTxtFile::ReadTxtFile() : fullIntro(0), introTimer(0), sequence(0), bgTimer(0), fullGameplay(0), order(0), next(0),
TimerStart(false), timerTime(false), timerReset(false), flashON(false), asylumON(false), introSound(true),
intro_dialogue(nullptr), city(nullptr), flash(nullptr), asylum(nullptr), textbox(nullptr), storage(0), release(false), introMusic(nullptr),
tempGameplay(0), gpPointer(0), gpgpPointer(0), duringPointer(0), duringPress(false)
{

}

ReadTxtFile::~ReadTxtFile()
{

}

void ReadTxtFile::SetStorage(int storage)
{
	this->storage = storage;
}

int ReadTxtFile::GetStorage()
{
	if (release)
		return storage;
	else
		return 0;
}

void ReadTxtFile::clearIntro()
{
	sequence = order = 0;
	introTimer = bgTimer = 0;
	timerTime = TimerStart = timerReset = flashON = asylumON = false;
}

void ReadTxtFile::Init()
{
	intro_dialogue = MeshBuilder::GenerateText("intro_dialogue", 16, 16);
	intro_dialogue->textureArray[0] = LoadTGA("Data//Texture//Redressed.tga");

	city = MeshBuilder::GenerateQuad("introduction", Color(0, 0, 0), 1.f);
	city->textureArray[0] = LoadTGA("Data//Texture//cityscape.tga");

	flash = MeshBuilder::GenerateSpriteAnimation("flash", 1, 4);
	flash->textureArray[0] = LoadTGA("Data//Texture//asylum.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(flash);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 1, 1, 0.5f, true);
	}

	asylum = MeshBuilder::GenerateSpriteAnimation("asylum", 1, 4);
	asylum->textureArray[0] = LoadTGA("Data//Texture//asylum.tga");
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(asylum);
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(2, 3, 0, 2.f, true);
	}

	textbox = MeshBuilder::GenerateQuad("textbox", Color(0, 0, 0), 1.f);
	textbox->textureArray[0] = LoadTGA("Data//Texture//textbox.tga");

	// Sound Engine
	introMusic = SoundEngine::Use()->addSoundSourceFromFile("Data//Sound//intro_music.mp3");
}

void ReadTxtFile::MusicInit()
{
	if (introSound)
	{
		SoundEngine::Use()->play2D(introMusic);
		introSound = false;
	}
}

void ReadTxtFile::Update(double dt)
{
	if (TimerStart)
		introTimer += dt;

	if (!TimerStart)
		introTimer = 0.f;

	//Update asylum sprite
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(flash);
	if (sa)
	{
		sa->Update(dt);
		sa->m_anim->animActive = true;
	}

	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(asylum);
	if (sa2)
	{
		sa2->Update(dt);
		sa2->m_anim->animActive = true;
	}

	//Update background sequence
	if (sequence >= 3)
	{
		flashON = true;
		bgTimer += dt;
	}
	if (bgTimer > 0.5f)
	{
		asylumON = true;
		flashON = false;
	}
	if (bgTimer > 15.f)
		asylumON = false;

<<<<<<< 95f352927d21644605e9f46273789b3cf40c46c8
	//cout << introTimer << endl;
=======
>>>>>>> fixed Some Text problem!
}

void ReadTxtFile::FloorUpdate(double dt)
{
	if (Input_PI::pointer()->HaveBeenPressed[Input_PI::DuringGP])
	{
		duringPointer++;
	}
}

void ReadTxtFile::ReadFromTextFile()
{
	ifstream inIntro, inGameplay, inAfter;
	string lineIntro, lineGameplay, lineAfter;

	inIntro.open("Data//Text//introduction.txt");
	while (!inIntro.eof())
	{
		getline(inIntro, lineIntro);
		fullIntro.push_back(lineIntro);
	}
	inIntro.close();

	inGameplay.open("Data//Text//gameplay.txt");
	while (!inGameplay.eof())
	{
		getline(inGameplay, lineGameplay);
		fullGameplay.push_back(lineGameplay);
	}
	inGameplay.close();

	inAfter.open("Data//Text//after.txt");
	while (!inAfter.eof())
	{
		getline(inAfter, lineAfter);
		fullAfter.push_back(lineAfter);
	}
	inAfter.close();

	//for (auto it = begin(fullGameplay); it != fullGameplay.end(); ++it)
	//{
	//	cout << *(it) << endl;
	//}
}

vector<string> ReadTxtFile::lineSplit(string input)
{
	int maxCharac = 35;
	vector<string> output;
	int division = 0;
	bool check = true;
	int value = input.length();

	while (check)
	{
		string temp = "";
		// Compare to max characters able to be displayed on screen
		for (int i = 0; i < maxCharac; i++)
		{
			// Separates one array from vector of arrays
			temp.push_back(input.at(division * maxCharac + i));
			if ((division * maxCharac + i) == (value - 1))
			{
				check = false;
				break;
			}
		}
		division++;
		output.push_back(temp);
	}

	return output;
}

void ReadTxtFile::tempGameplayFunction()
{
	while (tempGameplay.size() != 0)
	{
		tempGameplay.pop_back();
	}
	gpgpPointer = 0;
	gpPointer++;
	release = false;
	for (; gpPointer < fullGameplay.size(); gpPointer++)
	{
		if (fullGameplay.at(gpPointer).at(0) != '(')
			tempGameplay.push_back(fullGameplay.at(gpPointer));
		else
			break;
	}
}

void ReadTxtFile::RenderCity()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(100, 100, 1));
	Render_PI::pointer()->RenderMesh(city, false);
	Render_PI::pointer()->modelStack_Set(false);
}

void ReadTxtFile::RenderFlash()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(250, 100, 1));
	Render_PI::pointer()->RenderMesh(flash, false);
	Render_PI::pointer()->modelStack_Set(false);
}

void ReadTxtFile::RenderAsylum()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.5, 1), 0, 0, Vector3(250, 100, 1));
	Render_PI::pointer()->RenderMesh(asylum, false);
	Render_PI::pointer()->modelStack_Set(false);
}

void ReadTxtFile::RenderTextBox()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->modelStack_Define(Vector3(Render_PI::Window_Scale().x * 0.5, Render_PI::Window_Scale().y * 0.1, 1), 0, 0, Vector3(130, 15, 1));
	Render_PI::pointer()->RenderMesh(textbox, false);
	Render_PI::pointer()->modelStack_Set(false);
}

void ReadTxtFile::RenderTextForIntro()
{
	vector<string> tempIntro;

	if (sequence < fullIntro.size())
	{
		tempIntro = lineSplit(fullIntro.at(sequence));

		// Re-loop timer back to 0 secs
		if (introTimer > 5.f)
		{
			introTimer = 0.f;
			timerTime = true;
		}
		// Go to next line
		if (timerTime == true)
		{
			sequence++;
			timerReset = true;
		}
		// Reset variables
		if (timerReset == true)
		{
			timerReset = false;
			timerTime = false;
		}

		for (int i = 0; i < tempIntro.size(); i++)
		{
			int Y = tempIntro.size() - i;
			Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, tempIntro.at(i), Color(0, 0, 0), Vector3(10, 5 * Y + 2, 1), Vector3(5, 5, 1));
		}
	}

	if (sequence == fullIntro.size())
	{
		ostringstream ss;
		ss.str("");
		ss << "Press 'Enter'  to continue";
		Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(1, 1, 1), Vector3(75, 4, 1), Vector3(5, 5, 1));
	}
}

void ReadTxtFile::RenderTextForGameplay()
{
	RenderTextBox();
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, tempGameplay.at(gpgpPointer), Color(0, 0, 0), Vector3(10, 5 + 2, 1), Vector3(5, 5, 1));
}

void ReadTxtFile::RenderTextForAfter()
{
	vector<string> tempAfter;

	if (next < fullAfter.size())
	{
		tempAfter = lineSplit(fullAfter.at(next));

		// Re-loop timer back to 0 secs
		if (introTimer > 3.f)
		{
			introTimer = 0.f;
			timerTime = true;
		}
		// Go to next line
		if (timerTime == true)
		{
			next++;
			timerReset = true;
		}
		// Reset variables
		if (timerReset == true)
		{
			timerReset = false;
			timerTime = false;
		}

		for (int i = 0; i < tempAfter.size(); i++)
		{
			int Y = tempAfter.size() - i;
			Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, tempAfter.at(i), Color(0, 0, 0), Vector3(10, 5 * Y + 2, 1), Vector3(5, 5, 1));
		}
	}

	if (next == fullAfter.size())
	{
		ostringstream ss;
		ss.str("");
		ss << "End.";
		Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(1, 1, 1), Vector3(65, 4, 1), Vector3(5, 5, 1));
	}
}

void ReadTxtFile::RenderForIntro()
{
	if (sequence < 3)
		RenderCity();
	if (flashON == true)
		RenderFlash();
	if (asylumON == true)
		RenderAsylum();
	if (sequence != fullIntro.size())
		RenderTextBox();
	RenderTextForIntro();
}

void ReadTxtFile::RenderForGameplay()
{
	RenderTextForGameplay();
}

void ReadTxtFile::RenderForAfter()
{
	if (next != fullAfter.size())
		RenderTextBox();
	RenderTextForAfter();
}

void ReadTxtFile::EnterLoop()
{
	if (Input_PI::pointer()->HaveBeenPressed[Input_PI::GameplayNext])
	{
		gpgpPointer++;
		if (gpgpPointer >= tempGameplay.size())
		{
			release = true;
		}
	}
}

void ReadTxtFile::Exit()
{
	if (c_ReadTxtFile != nullptr)
	{
		if (intro_dialogue != nullptr)
		{
			delete intro_dialogue;
			intro_dialogue = nullptr;
		}
		if (city != nullptr)
		{
			delete city;
			city = nullptr;
		}
		if (flash != nullptr)
		{
			SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(flash);
			if (sa)
			{
				delete sa->m_anim;
				sa->m_anim = nullptr;
			}
			delete flash;
			flash = nullptr;
		}
		if (asylum != nullptr)
		{
			SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(asylum);
			if (sa2)
			{
				delete sa2->m_anim;
				sa2->m_anim = nullptr;
			}
			delete asylum;
			asylum = nullptr;
		}
		if (textbox != nullptr)
		{
			delete textbox;
			textbox = nullptr;

		}
<<<<<<< HEAD
=======
		delete asylum;
		asylum = nullptr;
	}
	if (textbox != nullptr)
	{
		delete textbox;
		textbox = nullptr;
	}
>>>>>>> 44426e81d4351c103c7110d8e3b8bd85597ddb6f

		delete c_ReadTxtFile;
		c_ReadTxtFile = nullptr;
	}
}