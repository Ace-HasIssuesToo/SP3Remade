#include "ReadTxtFile.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"

ReadTxtFile* ReadTxtFile::c_ReadTxtFile = new ReadTxtFile();

ReadTxtFile::ReadTxtFile() : fullIntro(0), introTimer(0), sequence(0), bgTimer(0), fullGameplay(0),
TimerStart(false), timerTime(false), timerReset(false), flashON(false), asylumON(false),
intro_dialogue(nullptr), city(nullptr), flash(nullptr), asylum(nullptr), textbox(nullptr)
{

}

ReadTxtFile::~ReadTxtFile()
{

}

void ReadTxtFile::clearIntro()
{
	sequence = 0;
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
}
Mesh* ReadTxtFile::GetText()
{
	return intro_dialogue;
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

	//cout << sequence << endl;
}

void ReadTxtFile::ReadFromTextFile()
{
	ifstream inIntro, inGameplay;
	string lineIntro, lineGameplay;

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

void ReadTxtFile::RenderText()
{
	vector<string> tempIntro;

	// Re-loop timer back to 0 secs
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

void ReadTxtFile::Render()
{
	if (sequence < 3)
		RenderCity();
	if (flashON == true)
		RenderFlash();
	if (asylumON == true)
		RenderAsylum();
	if (sequence != fullIntro.size())
		RenderTextBox();
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
<<<<<<< HEAD
		delete asylum;
		asylum = nullptr;
=======
<<<<<<< 680590776936ab288f01ffbf183b4ace13c2aa59
<<<<<<< HEAD
		delete asylum;
		asylum = nullptr;
=======
<<<<<<< HEAD
=======
<<<<<<< HEAD
		delete asylum;
		asylum = nullptr;
=======
>>>>>>> c480e6e9fc89873b4663ee066b9e6b32d93fa01f
>>>>>>> de08da505f2883da8197e7af6153638f6ac16f4e
>>>>>>> d95b00b47aa96f13513135d55ea7d5754178e0bd
=======
>>>>>>> 10 MB reached!
>>>>>>> 064852617059d73312bd6ff3648fefc7376cf973
	}

	if (c_ReadTxtFile != nullptr)
	{
		delete c_ReadTxtFile;
		c_ReadTxtFile = nullptr;
	}
}