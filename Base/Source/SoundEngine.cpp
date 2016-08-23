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
	if (m_Engine != nullptr)
	{
		m_Engine->drop();
		m_Engine = nullptr;
	}
}

ISoundEngine* SoundEngine::Use()
{
	return m_Engine;
}
