//=================================================================
//
//	PlayerText.h
//	吸い込み時のプレイヤーテキスト関連
//
//=================================================================
#ifndef __PLAYER_TEXT_H__
#define __PLAYER_TEXT_H__

// ========== インクルード部 ==========
#include "Sprite.h"
#include <DirectXMath.h>
#include "ObjectManager.h"

// ========== クラス ==========
class CPlayerText
{
public:
	enum kind {
		barabara,
		suikometa
	};

public:
	CPlayerText();
	~CPlayerText();
	void Update();
	void Draw();

	void SetDraw(kind kind);
	void SetObjMng(CObjectMng* pObjMng);

private:
	void Animation();
	void PopAnimation();

private:
	// 一度だけ表示フラグ
	int m_tree1;
	int m_tree2;
	int m_tree3;
	int m_rock1;
	int m_rock2;
	int m_rock3;
	int m_fence;
	int m_signBord;

	// 画像情報
	DirectX::XMFLOAT2 m_pos;				// 座標
	DirectX::XMFLOAT2 m_size;				// 横縦サイズ
	DirectX::XMFLOAT2 m_posTexCoord;		// テクスチャ座標
	DirectX::XMFLOAT2 m_sizeTexCoord;		// テクスチャサイズ
	Texture* m_pTexture;					// テクスチャ
	DirectX::XMFLOAT2 m_TextureSize;		// テクスチャサイズ

	// アニメーション情報
	int m_animeNo;							// UV指定
	int m_animePhase;						// アニメーション段階
	int m_waitFrame;						// 表示終了までの待ち時間

	CObjectMng* m_pObjMng;					// 初吸い込みフラグ・ObjList取得用
	list<Object*> m_pObjList;				// オブジェクトリストポインタ
};

#endif // !__PLAYER_TEXT_H__


// 〇ふきだし
// 吹き出しが出現するアニメーション
// ┗今のやつみたいに、右端のプレイヤーからみょんって出てくる。ちょっと大きくなって戻る。ぷにぷに感演出
// 左に一定量移動するアニメーション
// ┗移動量を加速度的に増やす。ちょっと行き過ぎて戻る。ぷにぷに感。(できれば、戻る前に進行方向に傾く(慣性)アニメーション)
// 消滅するアニメーション
// ┗今のやつみたいに、ちょっと大きくなってそのままその場で小さくなり消滅。

// 〇テキスト内アニメーション
// 対象オブジェクトイラスト(木とか岩とか)ゆらゆらアニメーション
// ┗中心を原点として-45,45度ぐらい間を傾き続ける。