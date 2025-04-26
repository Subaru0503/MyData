// 時間管理クラス

// インクルードガード
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include "Time.h"	// 時間

// クラス定義
class TimeManager
{
public:
	inline static TimeManager& GetInstance()
	{
		static TimeManager instance;
		return instance;
	}
	void Init();	// 初期化処理

	// 更新処理
	void Update();

	// クリアタイムを求める
	void CreateClearTime(std::vector<Time*> timeObj);

	// リセット関数
	inline void ResetTime()
	{
		// 全て削除
		for (auto it = m_TimeObj.begin(); it != m_TimeObj.end();)
		{
			GameObject* m_obj = *it;

			it = m_TimeObj.erase(it);
		}
		m_Time = 0.0f;
	}

	// セット関数
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

	// ゲット関数
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

	void TimeUpdate();				// 表示時間の更新

private:
	std::vector<Time*>  m_TimeObj;	// 時間オブジェクト

	float m_Time;					// 経過時間
	float m_TimeLimit;				// 制限時間
};

#endif // __TIME_MANAGER_H__