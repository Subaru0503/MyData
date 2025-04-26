// Tree.cpp

//=====インクルード=====
#include "TreeSmall.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CTreeSmall::CTreeSmall(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, CSoundMng* sound)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::TREE;

	// 吸い込み時の取得金額設定
	m_nMoney = 250;

	// 破壊時の木材生成個数
	m_createNum = 2;

	// オブジェクトレベル設定
	m_nLevel = 2;

	// モデルの拡縮率設定
	m_modelRatio = sizeX / BASE_SIZE_X;

	// モデル分類設定
	m_modelKey = "木";

	// モデルの拡縮率設定
	//m_modelRatio = 0.5f;

	m_pSoundMng = sound;

	//回転ランダム力技
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

/********************
*@brief デストラクタ
*********************/
CTreeSmall::~CTreeSmall()	// デストラクタ
{
}