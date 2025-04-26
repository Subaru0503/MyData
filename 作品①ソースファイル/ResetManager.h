///////////////////////////////////////
//
// オブジェクトリセット管理クラス
//
// オブジェクトの配置を初期位置に戻す
//
///////////////////////////////////////


// インクルードガード
#ifndef __RESET_MANAGER_H__
#define __RESET_MANAGER_H__

// インクルード部
#include "GameObject.hpp"
#include "Fade.h"

// クラス定義
class ResetManager
{
public:

	// インスタンス取得
	inline static ResetManager& GetInstance()
	{
		static ResetManager instance;
		return instance;
	}

	// 更新処理
	void Update();

	// オブジェクトを初期状態に戻す
	void ResetState();

	// オブジェクト削除
	inline void RemoveALLObj()
	{
		// 全て削除
		for (auto it = m_Obj.begin(); it != m_Obj.end();)
		{
			it = m_Obj.erase(it);
		}
	}

	//----セット関数----

	// オブジェクトをセット
	inline void SetObj(GameObject* obj)
	{
		// リストに追加
		m_Obj.push_back(obj);
	}

	// フェードセット
	void SetFade(Fade* fade);

	//----ゲット関数----

	// リセットフラグを返す
	bool GetResetFlg();

private:

	// コンストラクタ
	ResetManager()
	{
		m_ResetFlg = false;
	};

	// デストラクタ
	~ResetManager()
	{
	};

private:

	// 初期状態に戻すオブジェクトリスト
	std::vector<GameObject*> m_Obj;

	// フェード
	Fade* m_pFade;

	// リセットフラグ
	bool m_ResetFlg;
};

#endif // __RESET_MANAGER_H__