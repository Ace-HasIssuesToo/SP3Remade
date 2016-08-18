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
	/*
	Beginning:


	Night One:
	-dont start with pokeballs

	Night Two:

	Night Three:

	Night Four:

	Night Five:

	End:

	*/
}

void StoryPlot::Update(double dt, Map* map)
{
	
}

void StoryPlot::RenderPsychic()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->modelStack_Set(false);
}

void StoryPlot::Exit()
{
	if (c_StoryPlot != nullptr)
	{
		delete c_StoryPlot;
		c_StoryPlot = nullptr;
	}
}