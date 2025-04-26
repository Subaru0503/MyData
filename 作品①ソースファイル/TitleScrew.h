//////////////////////////////
//
// タイトル名
//
//////////////////////////////

//----インクルードガード----
#ifndef __TITLE_SCREW_H__
#define __TITLE_SCREW_H__

//----インクルード部----
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"
#include "Move.h"

// アニメーション用
#include "Move2DAnimation.h"
#include "SpinAnimation.h"

#include "float3.h"

// クラス定義
class TitleScrew : public GameObject
{
private:
	// 最大まで回したときのSE再生状態
	enum SoundState
	{
		CanPlay,		// どちらも再生できる状態
		NotPlayMaxSE,	// 最大まで締めたときのSEを再生できない状態
		NotPlayMinSE,	// 最大まで緩めたときのSEを再生できない状態
	};

public:

	// コンストラクタ
	TitleScrew(std::string name = "Name");

	// デストラクタ
	~TitleScrew();

	// 更新処理
	void Update();

	// セット関数
	void SetAnimationSpeed(DirectX::XMFLOAT2 speed);

	// ネジが締めたときに向かう位置を設定
	void SetTargetPos(DirectX::XMFLOAT3 pos);

private:
	// ネジを回す処理
	void ScrewSpin();

private:

	// 回転アニメーション中にやる処理
	void ApplyRotationSettings();

private:
	//----コンポーネント----

	// 2Dモデルレンダラー
	ModelRenderer2D* _modelRenderer2D;

	// 移動
	Move* _move;

	// 2Dアニメーション
	Move2DAnimation* _move2DAnimation;

	// 回転アニメーション
	SpinAnimation* _spinAnimation;

	// アニメーションスピード
	DirectX::XMFLOAT2 m_AnimationSpeed;

	// ターゲット座標
	float3 m_TargetPos;

	// SE再生フラグ
	SoundState m_SpinMaxPlayingSE;
};

#endif // __TITLE_SCREW_H__