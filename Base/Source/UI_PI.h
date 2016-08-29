#ifndef UI_PI
#define UI_PI
#include "Support_Codes.h"

class UI
{
private:
	static Mesh* clock;
	static Mesh* minute_hand;
	static Mesh* hour_hand;
public:
	static void Init();
	static void Render();
};
static const int min_per_hour = int(180.f / 6.f);
#endif