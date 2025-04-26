#include "XController.h"

//--------------------------------------------------------------------------------------
// �ÓI�����o
//--------------------------------------------------------------------------------------
double Window::g_dFps = 60;//FPS
double Window::g_dFrameTime = 0.01666;//1�t���[��������̎���

//--------------------------------------------------------------------------------------
// �O���錾
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//--------------------------------------------------------------------------------------
// Window::InitFps()�֐��FFPS�v���̏�����
//--------------------------------------------------------------------------------------
void Window::InitFps()
{
	QueryPerformanceFrequency(&m_freq);
	QueryPerformanceCounter(&m_starttime);//���݂̎��Ԃ��擾�i1�t���[���ځj
}

//--------------------------------------------------------------------------------------
// Window::CalculationFps()�֐��FFPS�v��
//--------------------------------------------------------------------------------------
void Window::CalculationFps()
{
	if (m_iCount == 60)//�J�E���g��60�̎��̏���
	{
		QueryPerformanceCounter(&m_nowtime);//���݂̎��Ԃ��擾�i60�t���[���ځj
		//FPS = 1�b / 1�t���[���̕`��ɂ����鎞��
		//    = 1000ms / ((���݂̎���ms - 1�t���[���ڂ̎���ms) / 60�t���[��)
		g_dFps = 1000.0 / (static_cast<double>((m_nowtime.QuadPart - m_starttime.QuadPart) * 1000 / m_freq.QuadPart) / 60.0);
		m_iCount = 0;//�J�E���g�������l�ɖ߂�
		m_starttime = m_nowtime;//1�t���[���ڂ̎��Ԃ����݂̎��Ԃɂ���
	}
	m_iCount++;//�J�E���g+1
}

//--------------------------------------------------------------------------------------
// Window::CalculationSleep()�֐��FSleep�����鎞�Ԃ̌v�Z
//--------------------------------------------------------------------------------------
void Window::CalculationSleep()
{
	QueryPerformanceCounter(&m_nowtime);//���݂̎��Ԃ��擾
	//Sleep�����鎞��ms = 1�t���[���ڂ��猻�݂̃t���[���܂ł̕`��ɂ�����ׂ�����ms - 1�t���[���ڂ��猻�݂̃t���[���܂Ŏ��ۂɂ�����������ms
	//                  = (1000ms / 60)*�t���[���� - (���݂̎���ms - 1�t���[���ڂ̎���ms)
	DWORD dwSleepTime = static_cast<DWORD>((1000.0 / 60.0) * m_iCount - (m_nowtime.QuadPart - m_starttime.QuadPart) * 1000 / m_freq.QuadPart);
	if (dwSleepTime > 0 && dwSleepTime < 18)//�傫���ϓ����Ȃ����SleepTime��1�`17�̊Ԃɔ[�܂�
	{
		timeBeginPeriod(1);
		Sleep(dwSleepTime);
		timeEndPeriod(1);
	}
	else//�傫���ϓ����������ꍇ
	{
		timeBeginPeriod(1);
		Sleep(1);
		timeEndPeriod(1);
	}
}

//--------------------------------------------------------------------------------------
// Window::CalculationFrameTime()�֐��F1�t���[��������̎��Ԃ̌v��
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
// Window::GetFps()�֐��FFPS�̎擾
//--------------------------------------------------------------------------------------
double Window::GetFps()
{
	return g_dFps;
}

//--------------------------------------------------------------------------------------
// Window::GetFrameTime()�֐��F1�t���[��������̎��Ԃ̎擾
//--------------------------------------------------------------------------------------
double Window::GetFrameTime()
{
	return g_dFrameTime;
}