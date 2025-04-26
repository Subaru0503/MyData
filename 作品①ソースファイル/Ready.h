// スタート準備UIクラス

// インクルードガード
#ifndef __READY_H__
#define __READY_H__

// インクルード部
#include "GameObject.hpp"

// コンポーネント
#include "ModelRenderer2D.h"
#include "Move.h"
#include "SpinAnimation.h"

// クラス定義
class Ready : public GameObject
{
public:
	enum AnimKind
	{
		None,
		Before,
		Change,
		Scale,
		Start,
	};
public:
	Ready(std::string name = "Ready");	// コンストラクタ
	~Ready();							// デストラクタ

	void Update();						// 更新処理

	// ゲット関数
	inline bool GetStart()
	{
		return m_Start;
	}

private:
	void BeforeSpinAnimation();				// 回転移動アニメーション前にやる処理
	void MoveAndTextureChangeAnimation();	// 回転移動アニメーション+テクスチャ変更
	void ScaleAnimation();					// 拡縮アニメーション
private:
	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;
	Move* _move;
	SpinAnimation* _spinAnimation;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;

	AnimKind animKind;		// アニメーション種類

	float m_Delay;			// 回転アニメーション開始までのディレイ

	bool m_Start;			// ゲームスタート開始フラグ
	bool m_ScaleAnimFlg;	// 拡縮アニメーションフラグ
};

#endif // __GAME_OVER_H__