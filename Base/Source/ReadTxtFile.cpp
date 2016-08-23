#include "ReadTxtFile.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"

ReadTxtFile* ReadTxtFile::c_ReadTxtFile = new ReadTxtFile();

ReadTxtFile::ReadTxtFile() : fullIntro(0)
{

}

ReadTxtFile::~ReadTxtFile()
{

}

void ReadTxtFile::Init()
{
	intro_dialogue = MeshBuilder::GenerateText("intro_dialogue", 16, 16);
	intro_dialogue->textureArray[0] = LoadTGA("Data//Texture//calibri.tga");
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
		cout << "Sentence taken in" << endl;
	}
	inStory.close();
}

void ReadTxtFile::Render()
{
	Render_PI::pointer()->modelStack_Set(true);
	std::ostringstream ss;
	ss.precision(0);
	for (int i = 0; i < fullIntro.size(); i++)
	{
		ss << fullIntro[i] << endl;
	}
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(1, 1, 1), (Render_PI::Window_Scale(), 1, 1), Vector3(5, 5, 1));
	Render_PI::pointer()->modelStack_Set(false);
}

void ReadTxtFile::Exit()
{ 
	if (intro_dialogue != nullptr)
	{
		delete intro_dialogue;
		intro_dialogue = nullptr;
	}
	if (c_ReadTxtFile != nullptr)
	{
		delete c_ReadTxtFile;
		c_ReadTxtFile = nullptr;
	}
}