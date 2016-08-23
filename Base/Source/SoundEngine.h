#ifndef SOUNDENGINE
#define SOUNDENGINE

#include "Support_Codes.h"

class SoundEngine
{
public:
	static void Init();
	static void Exit();
	static ISoundEngine* Use();
private:
	SoundEngine();
	~SoundEngine();
	static ISoundEngine* m_Engine;
};
#endif