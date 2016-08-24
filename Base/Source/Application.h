#ifndef APPLICATION_H
#define APPLICATION_H

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DBG_NEW
#endif
#endif //_DEBUG

#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>

#include "timer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool GetMouseUpdate();
	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	const static int m_window_width = 800;
	const static int m_window_height = 600;

	static int GetWindowWidth(){ return m_window_width; };
	static int GetWindowHeight(){ return m_window_height; };
private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
};

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

#endif