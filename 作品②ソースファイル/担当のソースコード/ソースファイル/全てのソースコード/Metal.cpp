// Metal.cpp

//=====インクルード=====
#include "Metal.h"

/************************************************
*@brief 座標設定引数付きコンストラクタ
*************************************************/
CMetal::CMetal(float posX, float posY, float posZ)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 削除フラグ初期化
	m_bDelete = false;

	// スケール設定
	m_scale = { 0.5f,0.5f,0.5f };

	// オブジェクトの種類の設定
	m_nKind = Object::METAL;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデル分類設定
	m_modelKey = "鋼材";
}

CMetal::CMetal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 削除フラグ初期化
	m_bDelete = false;

	// スケール設定
	m_scale = { 0.5f,0.5f,0.5f };

	// オブジェクトの種類の設定
	m_nKind = Object::METAL;

	// 吸い込み時の取得金額設定
	m_nMoney = 50;

	// オブジェクトレベル設定
	m_nLevel = 1;

	// モデル分類設定
	m_modelKey = "鋼材";

	// ドロップアニメーションフラグを立てる
	m_bDrop = true;
	m_EfkDestory = true;
	// ドロップ動作の移動方向設定
	m_dropDirection = dropDirection;

	// モデル設定
	m_pModelManager = pModelManager;
	SetModelData();
}

/********************
*@brief デストラクタ
*********************/
CMetal::~CMetal()	// デストラクタ
{

}