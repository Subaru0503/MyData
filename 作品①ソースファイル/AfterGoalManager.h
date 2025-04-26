// ゴール後管理クラス

// インクルードガード
#ifndef __AFTER_GOAL_MANAGER_H__
#define __AFTER_GOAL_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include "Clear.h"
#include "Goal.h"
#include "Player.h"
#include "Time.h"

// マネージャー
#include "TimeManager.h"

// クラス定義
class AfterGoalManager
{
public:
	inline static AfterGoalManager& GetInstance()
	{
		static AfterGoalManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// アルファ値変化
	void AlphaUpdate();
	// 描画フラグON
	inline void DrawON()
	{
		ModelRenderer2D* modelRenderer2D;

		for (int i = 0; i < m_TimeObj.size(); i++)
		{
			modelRenderer2D = m_TimeObj[i]->GetComponent<ModelRenderer2D>();
			modelRenderer2D->SetDraw(true);
		}
	}

	// オブジェクトリストに追加。
	inline void AddObj(GameObject* obj)
	{
		// オブジェクトナンバーの重複がないか確認
		for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++)
		{
			GameObject* m_obj = *it;
			// 既にあったら追加せずに飛ばす
			if (m_obj->GetTag() == obj->GetTag())
			{
				return;
			}
		}
		// オブジェクト追加
		m_pObjList.push_back(obj);
	}

	// リセット関数
	inline void Reset()
	{
		m_PlayBGM = false;
		m_pClear = nullptr;
		m_pPlayer = nullptr;
		m_pGoal = nullptr;
		// 全て削除
		for (auto it = m_pObjList.begin(); it != m_pObjList.end();)
		{
			it = m_pObjList.erase(it);
		}
		// 全て削除
		for (auto it = m_TimeObj.begin(); it != m_TimeObj.end();)
		{
			it = m_TimeObj.erase(it);
		}
		// 全て削除
		for (auto it = m_TimePos.begin(); it != m_TimePos.end();)
		{
			it = m_TimePos.erase(it);
		}
	}

	// セット関数
	inline void SetObj(Clear* obj, Player* player, Goal* goal)
	{
		m_pClear = obj;
		m_pPlayer = player;
		m_pGoal = goal;
		_clearModelRenderer2D = m_pClear->GetComponent<ModelRenderer2D>();
	}
	inline void SetTimeObj(Time* obj)
	{
		// 時間UI取得
		m_TimeObj.push_back(obj); //TimeManager::GetInstance().GetTimeObj();
	}
	inline void SetTimePos(DirectX::XMFLOAT3 pos)
	{
		m_TimePos.push_back(pos);
	}

	// ゲット関数
	inline bool GetObj()
	{
		return m_pClear == nullptr;
	}
	inline std::vector<Time*> GetTimeObj()
	{
		return m_TimeObj;
	}

private:

	AfterGoalManager()
	{
		m_PlayBGM = false;
	};
	~AfterGoalManager()
	{
	};

private:
	ModelRenderer2D* _clearModelRenderer2D;
	std::vector<GameObject*> m_pObjList;		// スカイドーム、カメラ
	std::vector<Time*>  m_TimeObj;				// 時間UIオブジェクト
	std::vector<DirectX::XMFLOAT3> m_TimePos;	// クリアタイム座標
	Clear* m_pClear;	// クリアUI
	Player* m_pPlayer;	// プレイヤー
	Goal* m_pGoal;		// ゴール

	bool m_PlayBGM;		// BGM再生フラグ
};

#endif // __AFTER_GOAL_MANAGER_H__