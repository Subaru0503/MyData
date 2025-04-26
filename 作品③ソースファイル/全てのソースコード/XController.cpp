#include "XController.h"

//--------------------------------------------------------------------------------------
// 静的メンバ
//--------------------------------------------------------------------------------------
double Window::g_dFps = 60;//FPS
double Window::g_dFrameTime = 0.01666;//1フレームあたりの時間

//--------------------------------------------------------------------------------------
// 前方宣言
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------------
// Window::InitFps()関数：FPS計測の初期化
//--------------------------------------------------------------------------------------
void Window::InitFps()
{
	QueryPerformanceFrequency(&m_freq);
	QueryPerformanceCounter(&m_starttime);//現在の時間を取得（1フレーム目）
}

//--------------------------------------------------------------------------------------
// Window::CalculationFps()関数：FPS計測
//--------------------------------------------------------------------------------------
void Window::CalculationFps()
{
	if (m_iCount == 60)//カウントが60の時の処理
	{
		QueryPerformanceCounter(&m_nowtime);//現在の時間を取得（60フレーム目）
		//FPS = 1秒 / 1フレームの描画にかかる時間
		//    = 1000ms / ((現在の時間ms - 1フレーム目の時間ms) / 60フレーム)
		g_dFps = 1000.0 / (static_cast<double>((m_nowtime.QuadPart - m_starttime.QuadPart) * 1000 / m_freq.QuadPart) / 60.0);
		m_iCount = 0;//カウントを初期値に戻す
		m_starttime = m_nowtime;//1フレーム目の時間を現在の時間にする
	}
	m_iCount++;//カウント+1
}

//--------------------------------------------------------------------------------------
// Window::CalculationSleep()関数：Sleepさせる時間の計算
//--------------------------------------------------------------------------------------
void Window::CalculationSleep()
{
	QueryPerformanceCounter(&m_nowtime);//現在の時間を取得
	//Sleepさせる時間ms = 1フレーム目から現在のフレームまでの描画にかかるべき時間ms - 1フレーム目から現在のフレームまで実際にかかった時間ms
	//                  = (1000ms / 60)*フレーム数 - (現在の時間ms - 1フレーム目の時間ms)
	DWORD dwSleepTime = static_cast<DWORD>((1000.0 / 60.0) * m_iCount - (m_nowtime.QuadPart - m_starttime.QuadPart) * 1000 / m_freq.QuadPart);
	if (dwSleepTime > 0 && dwSleepTime < 18)//大きく変動がなければSleepTimeは1～17の間に納まる
	{
		timeBeginPeriod(1);
		Sleep(dwSleepTime);
		timeEndPeriod(1);
	}
	else//大きく変動があった場合
	{
		timeBeginPeriod(1);
		Sleep(1);
		timeEndPeriod(1);
	}
}

//--------------------------------------------------------------------------------------
// Window::CalculationFrameTime()関数：1フレームあたりの時間の計測
//--------------------------------------------------------------------------------------
void Window::CalculationFrameTime()
{
	static int iFlg;
	if (iFlg == 0)
	{
		QueryPerformanceCounter(&m_frametime_a);
		iFlg = 1;
	}
	QueryPerformanceCounter(&m_frametime_b);
	g_dFrameTime = (m_frametime_b.QuadPart - m_frametime_a.QuadPart) * 1000.0 / m_freq.QuadPart;
	m_frametime_a = m_frametime_b;
}

//--------------------------------------------------------------------------------------
// Window::GetFps()関数：FPSの取得
//--------------------------------------------------------------------------------------
double Window::GetFps()
{
	return g_dFps;
}

//--------------------------------------------------------------------------------------
// Window::GetFrameTime()関数：1フレームあたりの時間の取得
//--------------------------------------------------------------------------------------
double Window::GetFrameTime()
{
	return g_dFrameTime;
}