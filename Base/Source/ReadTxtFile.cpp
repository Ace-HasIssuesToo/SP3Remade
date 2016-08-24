#include "ReadTxtFile.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"

ReadTxtFile* ReadTxtFile::c_ReadTxtFile = new ReadTxtFile();

<<<<<<< HEAD
ReadTxtFile::ReadTxtFile() : fullIntro{ 0 }, introTimer(0), sequence(0), bgTimer(0),
TimerStart(false), timerTime(false), timerReset(false), flashON(false), asylumON(false),
intro_dialogue(nullptr), city(nullptr), flash(nullptr), asylum(false)
=======
ReadTxtFile::ReadTxtFile() : fullIntro(0), introTimer(0), TimerStart(false), intro_dialogue(nullptr)
>>>>>>> e190b5b384e4dd40ab510f42893726d263076b05
{

}

ReadTxtFile::~ReadTxtFile()
{

}

void ReadTxtFile::clearIntro()
{
	fullIntro = { 0 };
<<<<<<< HEAD
	sequence = 0;
	introTimer = bgTimer = 0;
	timerTime = TimerStart = timerReset = flashON = asylumON = false;
	intro_dialogue = city = flash = asylum = nullptr;
=======
	introTimer = 0;
	TimerStart = false;
>>>>>>> e190b5b384e4dd40ab510f42893726d263076b05
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
}

void ReadTxtFile::Update(double dt)
{
	if (TimerStart)
		introTimer += dt;

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

	//Update background order
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

	cout << bgTimer << endl;
}

void ReadTxtFile::ReadFromTextFile()
{
	//ofstream myfile;
	//myfile.open("example.txt");
	//myfile << "Writing this to a file.\n";
	//myfile.close();

	ifstream inStory;
	string sentence;

	inStory.open("Data//Text//story.txt");
	
	while (!inStory.eof())
	{
		getline(inStory, sentence);
		fullIntro.push_back(sentence);
	}
	inStory.close();
}

vector<string> ReadTxtFile::lineSplit(string input)
{
	int maxCharac = 27;
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

void ReadTxtFile::RenderText()
{
	// Every 5 secs, change to next line of array
	vector<string> tempIntro;

	float tempTimer = 0.f;
	//while (introTimer > 5.f)
	//{
	//	//Loop every 5 seconds


	//	introTimer = tempTimer;
	//}

<<<<<<< HEAD
	if (sequence == fullIntro.size())
	{
		ostringstream ss;
		ss.str("");
		ss << "Press 'Enter'  to continue";
		Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(1, 1, 1), Vector3(1, 5, 1), Vector3(5, 5, 1));
=======
	cout << "False / True : " << TimerStart << endl;
	cout << "introTimer : " << introTimer << endl;
	cout << "tempTimer : " << tempTimer << endl;

	for (int i = 0; i < fullIntro.size(); i++)
	{
		tempIntro = lineSplit(fullIntro.at(i));
	}

	for (int i = 0; i < tempIntro.size(); i++)
	{
		int Y = tempIntro.size() - i;
		Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, tempIntro.at(i), Color(1, 1, 1), Vector3(1, 5*Y, 1), Vector3(5, 5, 1));
>>>>>>> e190b5b384e4dd40ab510f42893726d263076b05
	}
}

void ReadTxtFile::Render()
{
	if (sequence < 3)
		RenderCity();
	if (flashON == true)
		RenderFlash();
	if (asylumON == true)
		RenderAsylum();
	RenderText();
}

void ReadTxtFile::Exit()
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
		delete flash;
		flash = nullptr;
	}
	if (asylum != nullptr)
	{
		delete asylum;
		asylum = nullptr;
	}
	if (c_ReadTxtFile != nullptr)
	{
		delete c_ReadTxtFile;
		c_ReadTxtFile = nullptr;
	}
}