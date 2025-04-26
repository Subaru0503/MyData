// ChocolatePieceRoyal.cpp


//=====インクルード=====
#include "ChocolatePieceRoyal.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
ChocolatePieceRoyal::ChocolatePieceRoyal(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	DirectX::XMVECTOR dropDirection, ModelManager* pModelManager,
	int strawberry)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::CHOCOLATEPIECE;

	// 吸い込み時の取得金額設定
	m_nMoney = 200;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	if (strawberry)
	{
		m_modelKey = "苺チョコのかけら";
	}
	else
	{
		m_modelKey = "チョコのかけら";
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
ChocolatePieceRoyal::~ChocolatePieceRoyal()	// デストラクタ
{

}