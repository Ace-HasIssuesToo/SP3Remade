#include "StoryPlot.h"
#include "Texture_PI.h"
#include "Player.h"

StoryPlot* StoryPlot::c_StoryPlot = new StoryPlot();

StoryPlot::StoryPlot()
{

}

StoryPlot::~StoryPlot()
{

}

void StoryPlot::Init()
{
	introduction = MeshBuilder::GenerateQuad("introduction", Color(1, 1, 1));
	introduction->textureArray[0] = LoadTGA("Data//Texture//azure_cityscape.tga");

	intro_dialogue = MeshBuilder::GenerateText("intro_dialogue", 16, 16);
	intro_dialogue->textureID = LoadTGA("Data//Texture//pokeFont.tga");

	/*
	Beginning:
	The beginnings of a morning is the end of a night.
	The city still bustles with life.
	Which better place to be besides the heart of the city?
	*screen darkens* *screen shows the words*
	My job at an Asylum.
	And my first shift...
	*screen flashes to show inverted bg of words + dead pokemon*
	...has just started.

	Interactive objects that tells player how he accepted the job
	*/
}

void StoryPlot::Update(double dt, Map* map)
{
	
}

void StoryPlot::RenderPartOne()
{
	Render_PI::pointer()->modelStack_Set(true);

	std::ostringstream ss;
	ss.precision(5);
	ss << "The beginnings of a morning is the end of a night.";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	ss.str("");
	ss.precision(5);
	ss << "The city still bustles with life.";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	ss.str("");
	ss.precision(5);
	ss << "Which better place to be in besides the heart of the city?";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	ss.str("");
	ss.precision(5);
	ss << "My job at an Asylum.";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	ss.str("");
	ss.precision(5);
	ss << "And my first shift...";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	ss.str("");
	ss.precision(5);
	ss << "...has just started.";
	Render_PI::pointer()->RenderTextOnScreen(intro_dialogue, ss.str(), Color(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	Render_PI::pointer()->modelStack_Set(false);
}

void StoryPlot::RenderEnd()
{

}

void StoryPlot::Exit()
{
	if (introduction != nullptr)
	{
		delete introduction;
		introduction = nullptr;
	}

	if (intro_dialogue != nullptr)
	{
		delete intro_dialogue;
		intro_dialogue = nullptr;
	}

	if (c_StoryPlot != nullptr)
	{
		delete c_StoryPlot;
		c_StoryPlot = nullptr;
	}
}