//=================================================================
//
//	SceneStageBase.cpp
//	ステージシーンの共通部分
//
//=================================================================

#include "SceneStageBase.h"

CSceneStageBase::CSceneStageBase(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, m_start(false)
	, m_count(false)
	, m_pause(false)
	, m_pauseSelect(0)
	, m_nItem{0}
	, time(0)
	, addtime(0)
	, Alpha(1.0f)
	, m_nCheck(0)
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// ----- データ作成 -----
	m_pUI = new CUI();
	
	m_pObjectMng = new CObjectMng;
	m_pPlayer = new CPlayer;
	m_pPlayer->SetObjectMng(m_pObjectMng);
	m_pPlayer->SetSoundMng(m_pSoundMng);
	m_pPlayer->SetUI(m_pUI);
	m_pCollisionAreaMng = new CCollisionAreaMng;
	m_pCollisionAreaMng->SetPlayer(m_pPlayer);
	m_pCollision = new CCollision;
	m_pCollision->SetPlayer(m_pPlayer);
	m_pCollision->SetObjectManager(m_pObjectMng);
	m_pObjectMng->SetSound(m_pSoundMng);
	m_pObjectMng->SetSuction(m_pPlayer->GetSuction());
	m_pCountDown = new CCountDown();
	m_pShopBG = new ShopBG();
	m_pPlayerText = new CPlayerText();
	m_pPlayerText->SetObjMng(m_pObjectMng);
	m_pEndUI = new GameEndUI(640.0f, 360.0f, 0.0f);
	m_pCustomEquipment = new CCustomEquipment();
	m_pPause = new Pause();
	m_pTutorial = new Tutorial();
	m_pTradeIcon = new TradeIcon();

}

CSceneStageBase::~CSceneStageBase()
{
	// ----- データが存在したら削除 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pObjectMng);
	SAFE_DELETE(m_pCollisionAreaMng);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pCustomEquipment);
	for (auto it = m_pTrade.begin(); it != m_pTrade.end();) {
		delete (*it);
		it = m_pTrade.erase(it);
	}
	SAFE_DELETE(m_pShopMenu);
	SAFE_DELETE(m_pProgress);
	SAFE_DELETE(m_pCountDown);
	SAFE_DELETE(m_pEndUI);
	SAFE_DELETE(m_pShopBG);
	SAFE_DELETE(m_pPlayerText);
	for (int i = 0; i < 3; i++) {
		SAFE_DELETE(m_pStageModel[i]);
	}
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pDust);
	SAFE_DELETE(m_pTutorial);
	SAFE_DELETE(m_pTradeIcon);
	SAFE_DELETE(m_pLeaf);
	SAFE_DELETE(m_pEBag);
}

void CSceneStageBase::Init()
{
	m_flg = true;
	m_zoomFlg = true;
	m_wait = 0;
	m_frame = 0;
	m_camRad = 0.0f;
	m_camPosY = 0.0f;
	m_horizon = 0.0f;
	m_horizonRad = 0.0f;
	m_vertical = 0.0f;
	m_factor = 0.0f;
	m_value = 0.0f;


	m_pPlayer->LoadEffect();

	m_pLeaf = new Leaf();
	m_pLeaf->SetObject(m_pObjectMng->GetObjectList());
	m_pLeaf->SetPlayer(m_pPlayer);
	m_pObjectMng->SetLeaf(m_pLeaf);
	m_pDust = new Dust();
	m_pDust->SetObject(m_pObjectMng->GetObjectList());
	m_pDust->SetPlayer(m_pPlayer);
	m_pObjectMng->SetDust(m_pDust);
	m_pEBag = new EBag();
	m_pEBag->SetPlayer(m_pPlayer);
	m_pObjectMng->SetBag(m_pEBag);
}


void CSceneStageBase::ItemCheck(int* item)		// アイテム使用の確認関数
{
	//----アイテムが使用情報受け渡し----
	m_pPlayer->SetItem(item[0], item[1]);
	m_pTimer->SetItem(item[2]);
	m_pShopMenu->SetItemUse(item[3]);
}

int CSceneStageBase::getMoney()
{
	return m_pUI->GetMoney();
}

int CSceneStageBase::getPer()
{
	return m_pProgress->GetProgressNum();
}

int CSceneStageBase::getTime()
{
	return m_pProgress->GetTime();
}


CPlayer * CSceneStageBase::GetPlayer()
{
	return m_pPlayer;
}