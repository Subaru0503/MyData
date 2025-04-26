// ���ԊǗ��N���X

// �C���N���[�h�K�[�h
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

// �C���N���[�h��
#include "GameObject.hpp"
#include "Time.h"	// ����

// �N���X��`
class TimeManager
{
public:
	inline static TimeManager& GetInstance()
	{
		static TimeManager instance;
		return instance;
	}
	void Init();	// ����������

	// �X�V����
	void Update();

	// �N���A�^�C�������߂�
	void CreateClearTime(std::vector<Time*> timeObj);

	// ���Z�b�g�֐�
	inline void ResetTime()
	{
		// �S�č폜
		for (auto it = m_TimeObj.begin(); it != m_TimeObj.end();)
		{
			GameObject* m_obj = *it;

			it = m_TimeObj.erase(it);
		}
		m_Time = 0.0f;
	}

	// �Z�b�g�֐�
	inline void SetTimeObj(Time* obj)
	{
		m_TimeObj.push_back(obj);
	}
	inline void SetTime(float time)
	{
		m_TimeLimit = time;
		m_Time = time;
		Init();
	}

	// �Q�b�g�֐�
	inline float GetTime()
	{
		return m_Time;
	}

private:

	TimeManager()
	{
		m_Time = 0.0f;
	};
	~TimeManager()
	{
	};

	void TimeUpdate();				// �\�����Ԃ̍X�V

private:
	std::vector<Time*>  m_TimeObj;	// ���ԃI�u�W�F�N�g

	float m_Time;					// �o�ߎ���
	float m_TimeLimit;				// ��������
};

#endif // __TIME_MANAGER_H__