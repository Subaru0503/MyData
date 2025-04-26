// 当たり判定管理クラス

// インクルードガード
#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

// インクルード部
#include "GameObject.hpp"

// クラス定義
class CollisionManager
{
public:
	inline static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	// オブジェクトリストに追加。
	inline void AddObj(GameObject* obj)
	{
		// オブジェクトナンバーの重複がないか確認
		for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++)
		{
			GameObject* m_obj = *it;
			// 既にあったら追加せずに飛ばす
			if (m_obj->Get3DObjNo() == obj->Get3DObjNo())
			{
				return;
			}
		}
		// オブジェクト追加
		m_pObjList.push_back(obj);
	}

	inline void RemoveALLObj()
	{
		// 全て削除
		for (auto it = m_pObjList.begin(); it != m_pObjList.end();)
		{
			it = m_pObjList.erase(it);
		}
	}

	// 更新処理
	void Update();

	// ゲット関数
	inline int GetObjSize()
	{
		return (int)m_pObjList.size();
	}

private:
	
	CollisionManager()
	{

	};
	~CollisionManager()
	{
	};

private:
	// コライダー持ちのオブジェクトリスト
	std::vector<GameObject*> m_pObjList;

	bool m_Collision;
};

#endif // __COLLISION_MANAGER_H__