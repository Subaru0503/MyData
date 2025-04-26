// ゲームオーバーUIクラス

// インクルードガード
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

// インクルード部
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// クラス定義
class GameOver : public GameObject
{
public:
	GameOver(std::string name = "GameOver");	// コンストラクタ
	~GameOver();									// デストラクタ

	void Update();										// 更新処理

	// ゲット関数
	// 透明度の変化がなくなって描画できたフラグを返す
	inline bool GetDraw()
	{
		return m_Alpha >= 1.0f;
	}

private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;

	float m_Time;				// 経過時間
	float m_Alpha;				// アルファ値
};

#endif // __GAME_OVER_H__