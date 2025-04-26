// �C���N���[�h��
#include "TimeManager.h"

// ����������
void TimeManager::Init()
{
	int time[4];
	time[0] = (int)(m_Time / 60.0f / 10.0f);		// 10�̈�(��)
	time[1] = (int)(m_Time / 60.0f) % 10;			// 1�̈�(��)
	time[2] = (int)(((int)m_Time % 60) / 10.0f);	// 10�̈�(�b)
	time[3] = (int)m_Time % 60 % 10;				// 1�̈�(�b)

	// �A�j���i���o�[�Z�b�g
	for (int i = (int)m_TimeObj.size() - 1; i >= 0; i--)
	{
		m_TimeObj[i]->SetAnimeNo(time[i]);
	}
}

// �X�V����
void TimeManager::Update()
{

	TimeUpdate();			// �\�����鎞�Ԃ̍X�V
}

// �N���A�^�C�������߂�
void TimeManager::CreateClearTime(std::vector<Time*> timeObj)
{
	// �N���A�^�C�� = �������� - �c�莞��
	float clearTime = m_TimeLimit - m_Time;

	int time[4];
	time[0] = (int)(clearTime / 60.0f / 10.0f);		// 10�̈�(��)
	time[1] = (int)(clearTime / 60.0f) % 10;		// 1�̈�(��)
	time[2] = (int)(((int)clearTime % 60) / 10.0f);	// 10�̈�(�b)
	time[3] = (int)clearTime % 60 % 10;			// 1�̈�(�b)

	// �A�j���i���o�[�Z�b�g
	for (int i = (int)timeObj.size() - 1; i >= 0; i--)
	{
		timeObj[i]->SetAnimeNo(time[i]);
	}
}

// �\�����Ԃ̍X�V
void TimeManager::TimeUpdate()
{
	// �Ȃ������珈�����Ȃ�
	if (m_TimeObj.size() < 1) return;

	int time[4];
	time[0] = (int)(m_Time / 60.0f / 10.0f);		// 10�̈�(��)
	time[1] = (int)(m_Time / 60.0f) % 10;			// 1�̈�(��)
	time[2] = (int)(((int)m_Time % 60) / 10.0f);	// 10�̈�(�b)
	time[3] = (int)m_Time % 60 % 10;		// 1�̈�(�b)

	// �A�j���i���o�[�Z�b�g
	for (int i = (int)m_TimeObj.size() - 1;  i >= 0; i--)
	{
		m_TimeObj[i]->SetAnimeNo(time[i]);
	}

	m_Time -= 1.0f / 60.0f;	// �o�ߎ���
}
