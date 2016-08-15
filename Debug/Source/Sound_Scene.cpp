#include "Sound_Scene.h"

void Sound_Scene::Init()
{
	Game_Model::pointer()->SoundEngine = nullptr;
	Game_Model::pointer()->Environment_Sound = nullptr;
	Game_Model::pointer()->SoundEngine = createIrrKlangDevice();
	if (!Game_Model::pointer()->SoundEngine)
	{
		std::cout << "Sound Prepation failed!" << std::endl;
		system("pause");
	}
}

void Sound_Scene::Update(double dt)
{
	//Data\\Sound\\XXX.mp3
	if (Game_Model::pointer()->Environment_Sound == nullptr)
	{
		Game_Model::pointer()->Environment_Sound = Game_Model::pointer()->SoundEngine->play2D("Data\\Sound\\Horror_Environment.mp3", false, true);
	}
	if (Game_Model::pointer()->Environment_Sound->getIsPaused() == true)
	{
		Game_Model::pointer()->Environment_Sound->setIsPaused(false);
	}
	if (Game_Model::pointer()->Environment_Sound->isFinished() == true)
	{
		Game_Model::pointer()->Environment_Sound = nullptr;
	}
}

void Sound_Scene::Render()
{

}

void Sound_Scene::Exit()
{

}
