#include "SoundEngine.h"


ISoundEngine* SoundEngine::m_Engine = nullptr;

SoundEngine::SoundEngine() 
{

}

SoundEngine::~SoundEngine()
{

}

void SoundEngine::Init()
{
	m_Engine = createIrrKlangDevice();
}

void SoundEngine::Exit()
{
	m_Engine->drop();
}

ISoundEngine* SoundEngine::Use()
{
	return m_Engine;
}
