//=================================================================
//
//	SceneStageBase.h
//	ステージシーンの共通部分
//
//=================================================================

#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__

// ========== インクルード部 ==========
#include <vector>
#include "Value.h"
// ----- システム -----
#include "SceneManager.h"
#include "SoundManager.h"
#include "Model.h"
#include "Shader.h"
// ----- オブジェクト -----
#include "Player.h"
#include "ObjectManager.h"
#include "Object.h"
#include "CollisionAreaManager.h"
#include "Collision.h"
#include "Trade.h"
// ----- UI -----
#include "UI.h"
#include "Timer.h"
#include "ShopMenu.h"
#include "ShopText.h"
#include "Progress.h"
#include "CustomEquipment.h"
#include "CountDown.h"
#include "GameEndUI.h"
#include "ShopBG.h"
#include "PlayerText.h"
#include "Pause.h"
#include "Tutorial.h"
#include "TradeIcon.h"
// ----エフェクト----
#include "DustCloud.h"
#include "Leaf.h"
#include "Bag.h"
using namespace std;


//=====定数・マクロ定義=====
#define MAX_PAUSEMENU	(3)
// ----- カメラワーク -----
#define MAX_FRAME		(53)
#define WAIT_FRAME		(53)
#define CAL_CAMERA		(0.79f)
#define CAM_RAD_BEFORE	(10.0f)
#define START_CAM_RAD	(2.0f)
#define CAMERA_RAD		(20.0f)
#define START_CAM_POS_Y (1.5f)
#define CAMERA_POS_Y	(6.0f)
#define HORIZON			(50.0f)
#define VERTICAL		(45.0f)
#define START_HORIZON	(-270.0f)
#define START_VERTICAL	(45.0f)

// ========== クラス ==========
class CSceneStageBase
{
public:
	CSceneStageBase(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	virtual ~CSceneStageBase();
	virtual void Init();
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

	virtual void ItemCheck(int* item);			// アイテム使用の確認関数

	virtual int getMoney();						// 金額渡し
	virtual int getPer();						// 達成度渡し
	virtual int getTime();						// クリアタイム渡し
	virtual CPlayer* GetPlayer();
protected:
	virtual void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs) = 0;	// 陸描画
	virtual void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng) = 0;

	bool m_start, m_count;		// ゲームスタートフラグ
	bool m_pause;				// ポーズ画面フラグ
	int  m_pauseSelect;			// ポーズメニュー選択状況
	int time;
	int addtime;
	float Alpha;
	bool m_flg, m_zoomFlg;
	int m_wait, m_frame;
	float m_camRad, m_camPosY, m_horizon, m_horizonRad, m_vertical, m_factor, m_value;
	// 確認用フラグ
	int m_nCheck;

	// 他シーンから受け取り用
	int m_nItem[MAX_ITEM];

	// 他シーンへデータ引継ぎ用
	int* pMoney, pPer, pTime;

	// 各ゲームデータ用
	VertexShader* m_pVS;
	CPlayer* m_pPlayer;
	CObjectMng* m_pObjectMng;
	Object* m_pObject;
	CCollisionAreaMng* m_pCollisionAreaMng;
	CCollision* m_pCollision;
	vector<CTrade*> m_pTrade;
	CTimer* m_pTimer;
	CUI* m_pUI;
	CShopMenu* m_pShopMenu;
	CShopText* m_pShopText;
	CProgress* m_pProgress;
	CCustomEquipment* m_pCustomEquipment;
	CCountDown* m_pCountDown;
	CSoundMng* m_pSoundMng;
	ShopBG* m_pShopBG;
	CPlayerText* m_pPlayerText;
	GameEndUI* m_pEndUI;

	CSceneMng* m_pSceneMng;

	Model* m_pStageModel[3];		// 陸・海・空モデル

	Pause* m_pPause;
	Dust* m_pDust;
	Leaf* m_pLeaf;
	EBag* m_pEBag;
	Tutorial* m_pTutorial;
	TradeIcon* m_pTradeIcon;
};

#endif // !__SCENE_STAGE_BASE_H__
