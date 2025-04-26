// ゴールクラス

// インクルードガード
#ifndef __GOAL_H__
#define __GOAL_H__

// インクルード部
#include "GameObject.hpp"

// コンポーネント
#include "BoxCollider.h"		// 当たり判定
//#include "Scanner.h"			// スキャンコンポーネント
#include "ModelRenderer3D.h"	// 3Dモデル描画

// クラス定義
class Goal : public GameObject
{
public:
	Goal(std::string name = "Goal");	// コンストラクタ
	~Goal();							// デストラクタ

	void Update();						// 更新処理

	void OnCollision(GameObject* obj);	// 当たったオブジェクトのあとの処理

	// ゲット関数
	// ゴールフラグを返す
	inline bool GetGoalFlg()
	{
		return m_GoalFlg;
	}

private:
	// コンポーネント
	BoxCollider* _boxCollider;			// ボックスコライダーコンポーネント
	//Scanner* _scanner;					// スキャナコンポーネント
	ModelRenderer3D* _modelRenderer3D;	// 3D描画コンポーネント

	bool m_GoalFlg;						// ゴールフラグ

};

#endif // __GOAL_H__