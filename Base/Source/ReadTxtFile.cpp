#include "ReadTxtFile.h"
#include "Texture_PI.h"
#include "Player.h"
#include "GameState.h"

ReadTxtFile* ReadTxtFile::c_ReadTxtFile = new ReadTxtFile();

ReadTxtFile::ReadTxtFile() : fullIntro(0), introTimer(0)
{

}

ReadTxtFile::~ReadTxtFile()
{

}

void ReadTxtFile::Init()
{
	intro_dialogue = MeshBuilder::GenerateText("intro_dialogue", 16, 16);
	intro_dialogue->textureArray[0] = LoadTGA("Data//Texture//Redressed.tga");
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

void ReadTxtFile::Render()
{
	//Render_PI::pointer()->modelStack_Set(true);
	//Render_PI::pointer()->modelStack_Set(false);
	vector<string> tempIntro;

	//for (int i = 0; fullIntro.size(); i++)
		tempIntro = lineSplit(fullIntro.at(0));

	for (int i = 0; i < tempIntro.size(); i++)
	{
		int Y = tempIntro.size() - i;
		Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, tempIntro.at(i), Color(1, 1, 1), Vector3(1, 5*Y, 1), Vector3(5, 5, 1));
	}
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