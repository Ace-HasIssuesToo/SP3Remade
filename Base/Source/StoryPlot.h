#ifndef STORY_PLOT_H
#define STORY_PLOT_H

#include "Support_Codes.h"
#include "Render_PI.h"
#include "Map_PI.h"

class StoryPlot
{
public:
	StoryPlot();
	~StoryPlot();

	static StoryPlot* pointer() { return c_StoryPlot; };

	void Init();
	void Update(double dt, Map* map);
	void Exit();

	void RenderPartOne();
	void RenderEnd();

private:
	static StoryPlot* c_StoryPlot;

	float dialogueTimer;

	Mesh* introduction;
	Mesh* intro_dialogue;
};

#endif