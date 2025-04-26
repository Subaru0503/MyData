// Fence.cpp

//=====インクルード=====
#include "FenceSmall.h"

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CFenceSmall::CFenceSmall(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, CSoundMng* sound)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 引数から回転設定
	m_rotate.y = rot;

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::FENCE;

	// 吸い込み時の取得金額設定
	m_nMoney = 250;

	// 破壊時の木材生成個数
	m_createNum = 2;

	// オブジェクトレベル設定
	m_nLevel = 2;

	// モデル分類設定
	m_modelKey = "フェンス";

	//サウンド
	m_pSoundMng = sound;
}

/********************
*@brief デストラクタ
*********************/
CFenceSmall::~CFenceSmall()	// デストラクタ
{

}