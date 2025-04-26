//=================================================================
//
//	PlayerText.cpp
//	吸い込み時のプレイヤーテキスト関連
//
//=================================================================

// ========== インクルード部 ==========
#include "PlayerText.h"

#define SIZE_RATIO		(0.3f)		// 画像倍率
#define POP_START_POS_X	(0.0f)	// 出現開始座標
#define POP_START_POS_Y	(100.0f)
#define POS_X			(900.0f)	//テキストBOX表示座標
#define POS_Y			(135.0f)
#define ANIME_POS_Y		(130.0f)	// アニメーション座標
#define MOVE_FRAME		(10)		// 表示アニメーション再生スピード
#define WAIT_FRAME		(160)		// BOX表示終了アニメーション再生までのフレーム(60/秒)

CPlayerText::CPlayerText()
	: m_animeNo(0)
	, m_animePhase(0)
	, m_waitFrame(0)
	, m_pos(440.0f, 95.0f)
	, m_size(0.0f, 0.0f)
	, m_sizeTexCoord(1.0f, 1.0f)
	, m_posTexCoord(0.0f, 0.0f)
	, m_tree1(0)
	, m_tree2(0)
	, m_tree3(0)
	, m_rock1(0)
	, m_rock2(0)
	, m_rock3(0)
	, m_fence(0)
	, m_signBord(0)
{
	// テクスチャ読み込み
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/PlayerText/testPlayerText.png"))) {	// テキスト
		MessageBox(NULL, "text.png", "Error", MB_OK);
	}
	// テクスチャサイズ設定
	m_TextureSize.x = 300.0f;	// テクスチャの本来の画像サイズを取得
	m_TextureSize.y = 350.0f;	// 縦横比はそのままでサイズ調整
}

CPlayerText::~CPlayerText()
{
	SAFE_DELETE(m_pTexture);
}

void CPlayerText::Update()
{
	// ----- 準備 -----
	m_pObjList = *(m_pObjMng->GetObjectList());			// オブジェクトのリスト取得

	// =-=-= ヒントテキスト描画判定 =-=-=
	for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++) {	// 全て見る
		if ((*it)->IsShake()) {							// プルプルしていれば
			switch ((*it)->GetKind())					// 種類によってテキストの種類を変える
			{
			case Object::Kind::TREE:	// 木
				if ((*it)->GetLevel() == 1) {
					if (!m_tree1)	SetDraw(barabara);
					m_tree1++;			// 二度と表示しないようにする。
				}
				if ((*it)->GetLevel() == 2) {
					if (!m_tree2)	SetDraw(barabara);
					m_tree2++;
				}
				if ((*it)->GetLevel() == 3) {
					if (!m_tree3)	SetDraw(barabara);
					m_tree3++;
				}
				break;
			case Object::Kind::ROCK:	// 岩
				if ((*it)->GetLevel() == 1) {
					if (!m_rock1)	SetDraw(barabara);
					m_rock1++;
				}
				if ((*it)->GetLevel() == 2) {
					if (!m_rock2)	SetDraw(barabara);
					m_rock2++;
				}
				if ((*it)->GetLevel() == 3) {
					if (!m_rock3)	SetDraw(barabara);
					m_rock3++;
				}
				break;
			case Object::Kind::FENCE:	// 柵
				if (!m_fence)	SetDraw(barabara);
				m_fence++;
			case Object::Kind::SIGNBOARD:// 看板
				if (!m_signBord)	SetDraw(barabara);
				m_signBord++;
				break;
			}
		}
	}

	// ----- 吸い込めたテキスト表示 -----＊＊削除予定
	if (m_pObjMng->GetFirstSuctionFlg()->tree1 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree1++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->tree2 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree2++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->tree3 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree3++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock1 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->rock1++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock2 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->rock2++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock3 == 1) {
		m_pObjMng->GetFirstSuctionFlg()->rock3++;
		SetDraw(suikometa);
	}
	if (m_pObjMng->GetFirstSuctionFlg()->fence == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->fence++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->signBoard == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->signBoard++;
	}

	// ----- アニメーション更新 -----
	//Animation();
}

void CPlayerText::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f/*画面左端X*/, 1280.0f/*画面右端*/, 0.0f/*画面上端*/, 720.0f/*画面下端*/, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	// スプライトの設定
	m_posTexCoord.x = m_sizeTexCoord.x * m_animeNo;
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_size.x, m_size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_posTexCoord.x, m_sizeTexCoord.y * m_animeNo));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_sizeTexCoord.x, m_sizeTexCoord.y));
	Sprite::SetTexture(m_pTexture);

	Sprite::Draw();
}

void CPlayerText::Animation()
{
	switch (m_animePhase)	// アニメーション段階によって分岐
	{
		// ----- 表示待機待機 -----
	case 0:
		// ----- 初期化 -----
		m_pos = DirectX::XMFLOAT2(POP_START_POS_X, POP_START_POS_Y);
		m_size = DirectX::XMFLOAT2(0.0f, 0.0f);
		break;
		// ----- 出現 -----
	case 1:	// 拡大しながら所定の位置ちょい下へ
		if (m_pos.y <= ANIME_POS_Y) {// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (ANIME_POS_Y - POP_START_POS_Y) / (MOVE_FRAME * 0.95f);	// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 1.02f / (MOVE_FRAME * 0.95f);		// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 1.02f / (MOVE_FRAME * 0.95f);

			// ----- 値更新 -----
			m_pos.y += moveY;													// 移動
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);	// 拡大
		}
		else {
			m_animePhase = 1;		// 次のアニメーションへ
		}
		break;
	case 2:	// 縮小しながら所定の位置へ
		if (m_pos.y <= POS_Y) {		// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 0.02f / (MOVE_FRAME * 0.05f);			// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 0.02f / (MOVE_FRAME * 0.05f);

			// ----- 値更新 -----
			m_pos.y += moveY;														// 移動
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// 拡大
		}
		else {
			m_animePhase = 3;		// 次のアニメーションへ
		}
		break;
	case 3:	//待機
		if (m_waitFrame >= WAIT_FRAME) {
			m_animePhase = 4;
			m_waitFrame = 0;
		}
		m_waitFrame++;
		break;
		// ----- 表示終了 -----
	case 4:	// 拡大しながらちょっと下へ
		if (m_pos.y >= ANIME_POS_Y) {		// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 0.03f / (MOVE_FRAME * 0.05f);			// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 0.03f / (MOVE_FRAME * 0.05f);

			// ----- 値更新 -----
			m_pos.y -= moveY;														// 移動
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);		// 拡大
		}
		else {
			m_animePhase = 5;		// 次のアニメーションへ
		}
		break;

	case 5:	// 縮小しながら画面中央へ
		if (m_pos.y <= POP_START_POS_Y) {		// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (POP_START_POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.95f);		// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 1.01f / (MOVE_FRAME * 0.95f);			// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 1.01f / (MOVE_FRAME * 0.95f);

			// ----- 値更新 -----
			m_pos.y += moveY;														// 移動
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// 縮小
		}
		else {
			m_animePhase = 0;		// アニメーション停止・リセット
		}
		break;
	}
}

// ========== 吹き出し表示アニメーション ==========
// 引　数：なし
// 戻り値：なし
// 指定の吹き出しを表示する
// =================================
void CPlayerText::PopAnimation()
{
	switch (m_animePhase)
	{
		// ----- 出現 -----
	case 1:	// 拡大しながら所定の位置ちょい下へ
		if (m_pos.y >= ANIME_POS_Y) {// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (POP_START_POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.95f);	// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 1.02f / (MOVE_FRAME * 0.95f);			// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 1.02f / (MOVE_FRAME * 0.95f);

			// ----- 値更新 -----
			m_pos.y -= moveY;													// 移動
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);	// 拡大
		}
		else {
			m_animePhase = 2;		// 次のアニメーションへ
		}
		break;
	case 2:	// 縮小しながら所定の位置へ
		if (m_pos.y <= POS_Y) {		// 所定位置に到達していなければ
			// ----- 準備 -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// １フレームあたりの移動量算出
			float sizeUpx = m_TextureSize.x * 0.02f / (MOVE_FRAME * 0.05f);			// １フレームあたりの拡大量算出
			float sizeUpy = m_TextureSize.y * 0.02f / (MOVE_FRAME * 0.05f);

			// ----- 値更新 -----
			m_pos.y += moveY;														// 移動
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// 拡大
		}
		else {
			m_animePhase = 3;		// 次のアニメーションへ
		}
		break;
		break;
	}

}



// ========== テキスト表示 ==========
// 引　数：
// kind ヒントの種類
// 戻り値：なし
// 指定のテキストを表示する(すでに表示の場合は上書き)
// =================================
void CPlayerText::SetDraw(kind kind)
{
	// ----- 現在表示のウィンドウを消す -----
	// 初期化
	m_pos = DirectX::XMFLOAT2(POP_START_POS_X, POP_START_POS_Y);
	m_size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_waitFrame = 0;
	// ----- 新しいウィンドウを設定 -----
	m_animeNo = (int)kind;
	m_animePhase = 0;
}

void CPlayerText::SetObjMng(CObjectMng* pObjMng)
{
	m_pObjMng = pObjMng;
}