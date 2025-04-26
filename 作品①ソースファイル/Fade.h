// フェードクラス

// インクルードガード
#ifndef __FADE_H__
#define __FADE_H__

// インクルード部
#include "GameObject.hpp"
#include "ModelRenderer2D.h"

// 定数・マクロ定義
#define FADE_IN (true)
#define FADE_IN_TIME (1.0f)		// フェードイン時間
#define FADE_OUT (false)
#define FADE_OUT_TIME (2.0f)	// フェードアウト時間

// クラス定義
class Fade : public GameObject
{
public:

	// フェードカラー
	enum FadeColor
	{
		White,	// 白色
		Black,	// 黒色
	};

public:

	// コンストラクタ
	Fade(std::string name = "Fade");

	// デストラクタ
	~Fade();

	// 更新処理
	void Update();

	// フェード開始
	void Start(bool isIn, float time, FadeColor fadeColor);

	// フェード実行中か否か
	bool GetPlay();

	// フェードインかどうかを返す
	bool GetFadeIn();

private:

	// コンポーネント
	ModelRenderer2D* _modelRenderer2D;

	// モデルレンダラー2D描画パラメータ
	ModelRenderer2D::Param* _modelRenderer2D_param;

	// フェードカラー
	FadeColor m_FadeColor;

	// フェードイン　or　フェードアウト
	bool  m_FadeIn;

	// 経過時間
	float m_Time;

	// フェードにかかる合計時間
	float m_TotalTime;

	// アルファ値
	float m_Alpha;
};

#endif // __GAME_OVER_H__