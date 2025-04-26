//=================================================================
//
//	Fade.h
//	フェード関連
//
//=================================================================
#ifndef __FADE_H__
#define __FADE_H__

// ========== インクルード部 ==========
#include "Sprite.h"

// ========== クラス ==========
class Fade
{
public:
	enum kind {
		WHITE = 0,
		BLACK,
		TIPS,
		PLANET,

		MAX_FADE,
		NONE,
	};

public:
	Fade();
	~Fade();
	void Update();
	void Draw();

	void Start(bool isIn, float time, kind kind);	// fade開始
	bool IsPlay();						// fade実行中か否か
	float GetAlpha();					// Soundフェードのため

private:
	float m_alpha;						// 透明度(フェード進捗)
	bool  m_isIn;						// フェードイン　or　フェードアウト
	float m_time;						// 経過時間
	float m_totalTime;					// フェードにかかる合計時間
	kind  m_BGKind;						// 使用する背景の種類

	Texture* m_pTexture[MAX_FADE];		// テクスチャデータ
};

#endif // !__FADE_H__