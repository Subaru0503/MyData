// インクルード部
#include "TimeManager.h"

// 初期化処理
void TimeManager::Init()
{
	int time[4];
	time[0] = (int)(m_Time / 60.0f / 10.0f);		// 10の位(分)
	time[1] = (int)(m_Time / 60.0f) % 10;			// 1の位(分)
	time[2] = (int)(((int)m_Time % 60) / 10.0f);	// 10の位(秒)
	time[3] = (int)m_Time % 60 % 10;				// 1の位(秒)

	// アニメナンバーセット
	for (int i = (int)m_TimeObj.size() - 1; i >= 0; i--)
	{
		m_TimeObj[i]->SetAnimeNo(time[i]);
	}
}

// 更新処理
void TimeManager::Update()
{

	TimeUpdate();			// 表示する時間の更新
}

// クリアタイムを求める
void TimeManager::CreateClearTime(std::vector<Time*> timeObj)
{
	// クリアタイム = 制限時間 - 残り時間
	float clearTime = m_TimeLimit - m_Time;

	int time[4];
	time[0] = (int)(clearTime / 60.0f / 10.0f);		// 10の位(分)
	time[1] = (int)(clearTime / 60.0f) % 10;		// 1の位(分)
	time[2] = (int)(((int)clearTime % 60) / 10.0f);	// 10の位(秒)
	time[3] = (int)clearTime % 60 % 10;			// 1の位(秒)

	// アニメナンバーセット
	for (int i = (int)timeObj.size() - 1; i >= 0; i--)
	{
		timeObj[i]->SetAnimeNo(time[i]);
	}
}

// 表示時間の更新
void TimeManager::TimeUpdate()
{
	// なかったら処理しない
	if (m_TimeObj.size() < 1) return;

	int time[4];
	time[0] = (int)(m_Time / 60.0f / 10.0f);		// 10の位(分)
	time[1] = (int)(m_Time / 60.0f) % 10;			// 1の位(分)
	time[2] = (int)(((int)m_Time % 60) / 10.0f);	// 10の位(秒)
	time[3] = (int)m_Time % 60 % 10;		// 1の位(秒)

	// アニメナンバーセット
	for (int i = (int)m_TimeObj.size() - 1;  i >= 0; i--)
	{
		m_TimeObj[i]->SetAnimeNo(time[i]);
	}

	m_Time -= 1.0f / 60.0f;	// 経過時間
}
