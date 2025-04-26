#pragma once

#include <windows.h>
#pragma comment(lib,"winmm.lib")
#pragma comment (lib, "xinput.lib")
#include <xinput.h>

//--------------------------------------------------------------------------------------
// WindowÉNÉâÉXÅFWindowä÷åW
//--------------------------------------------------------------------------------------
class Window
{
public:
	void InitFps();
	void CalculationFps();
	void CalculationSleep();
	void CalculationFrameTime();


	static double GetFps();
	static double GetFrameTime();
private:
	LARGE_INTEGER m_freq = { 0 };
	LARGE_INTEGER m_starttime = { 0 };
	LARGE_INTEGER m_nowtime = { 0 };
	LARGE_INTEGER m_frametime_a = { 0 };
	LARGE_INTEGER m_frametime_b = { 0 };
	int m_iCount = 0;

	static double g_dFps;
	static double g_dFrameTime;
};

