//=================================================================
//
//	CountDown.h
//	カウントダウンUI
//
//=================================================================

#ifndef __COUNT_DOWN_H__
#define __COUNT_DOWN_H__
#include "Sprite.h"
#include <DirectXMath.h>

// ========== クラス ==========
class CCountDown
{
public:
	CCountDown();
	~CCountDown();
	void Update();
	void Draw();

private:
	typedef struct {
		int AnimeNo;						// UV指定
		DirectX::XMFLOAT2 pos;				// 座標
		DirectX::XMFLOAT2 size;				// 横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;		// テクスチャ座標
		DirectX::XMFLOAT2 sizeTexCoord;		// テクスチャサイズ
		Texture* pTexture;					// テクスチャ
		DirectX::XMFLOAT2 TextuerSize;		// テクスチャサイズ
		int phase;							// アニメーション段階
	}COUNT_UI;

private:
	COUNT_UI m_Count[2];					// UI
	int m_kind;								// テクスチャの種類
	int m_waitFrame;						// 待ち時間
	DirectX::XMFLOAT2 m_textureSize;		// テクスチャの本来サイズ
};

#endif // !__COUNT_DOWN_H__