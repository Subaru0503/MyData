// CandyPieceRoyal.cpp


//=====インクルード=====
#include "CandyPieceRoyal.h"
#include <time.h>

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CandyPieceRoyal::CandyPieceRoyal(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	DirectX::XMVECTOR dropDirection, ModelManager* pModelManager)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::CANDYPIECE;

	// 吸い込み時の取得金額設定
	m_nMoney = 200;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	srand((unsigned int)time(NULL));
	int random = rand() % 6;
	switch (random)
	{
	case 0:
		m_modelKey = "グレープキャンディーのかけら";
		break;
	case 1:
		m_modelKey = "グレープ魚キャンディーのかけら";
		break;
	case 2:
		m_modelKey = "オレンジキャンディーのかけら";
		break;
	case 3:
		m_modelKey = "オレンジ魚キャンディーのかけら";
		break;
	case 4:
		m_modelKey = "ソーダキャンディーのかけら";
		break;
	case 5:
		m_modelKey = "ソーダ魚キャンディーのかけら";
		break;
	}

	if (pModelManager)
	{
		// ドロップアニメーションフラグを立てる
		m_bDrop = true;

		// ドロップ動作の移動方向設定
		m_dropDirection = dropDirection;

		// モデル設定
		m_pModelManager = pModelManager;
		SetModelData();

		//回転ランダム力技
		m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
	}
}

/********************
*@brief デストラクタ
*********************/
CandyPieceRoyal::~CandyPieceRoyal()	// デストラクタ
{

}