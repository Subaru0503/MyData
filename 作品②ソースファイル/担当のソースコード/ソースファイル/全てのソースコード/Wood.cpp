// Wood.cpp

//=====インクルード=====
#include "Wood.h"

/************************************************
*@brief 座標設定引数付きコンストラクタ
*************************************************/
CWood::CWood(float posX, float posY, float posZ)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 削除フラグ初期化
	m_bDelete = false;

	// スケール設定
	m_scale = { 0.5f,0.5f,0.5f };

	// オブジェクトの種類の設定
	m_nKind = Object::WOOD;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデル分類設定
	m_modelKey = "木材";


	// ドロップアニメーションフラグを立てる
	m_bDrop = false;

	//回転ランダム力技
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

CWood::CWood(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 削除フラグ初期化
	m_bDelete = false;

	// スケール設定
	m_scale = { 0.5f,0.5f,0.5f };

	// オブジェクトの種類の設定
	m_nKind = Object::WOOD;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデル分類設定
	m_modelKey = "木材";

	// ドロップアニメーションフラグを立てる
	m_bDrop = true;
	m_EfkDestory = true;
	// ドロップ動作の移動方向設定
	m_dropDirection = dropDirection;

	// モデル設定
	m_pModelManager = pModelManager;
	SetModelData();

	//回転ランダム力技
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

/********************
*@brief デストラクタ
*********************/
CWood::~CWood()	// デストラクタ
{

}