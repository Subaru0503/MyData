//////////////////////////////
//
// タイトル名
//
//////////////////////////////

//----インクルードガード----
#ifndef __TITLE_H__
#define __TITLE_H__

//----インクルード部----
#include "GameObject.hpp"
// コンポーネント
#include "ModelRenderer2D.h"

// アニメーション用
#include "Move2DAnimation.h"
#include "SpinAnimation.h"

// クラス定義
class Title : public GameObject
{
public:

	// コンストラクタ
	Title(std::string name = "Name");

	// デストラクタ
	~Title();

	// 更新処理
	void Update();

	// セット関数
	void SetAnimationSpeed(DirectX::XMFLOAT2 speed);

private:

	// 回転アニメーション中にやる処理
	void ApplyRotationSettings();

private:
	//----コンポーネント----

	// 2Dモデルレンダラー
	ModelRenderer2D* _modelRenderer2D;

	// 2Dアニメーション
	Move2DAnimation* _move2DAnimation;

	// 回転アニメーション
	SpinAnimation* _spinAnimation;

	// アニメーションスピード
	DirectX::XMFLOAT2 m_AnimationSpeed;
};

#endif // __TITLE_H__