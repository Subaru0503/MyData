//SceneGame.h
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
//=====インクルード部=====
// ----- システム -----
#include "SceneManager.h"
#include "SoundManager.h"
#include "CameraBase.h"
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


//=====クラス=====
class SceneGame
{
public:
	SceneGame(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~SceneGame();
	void Update(float tick);
	void Draw();

	void DrawSky(DirectX::XMFLOAT4X4 *mat, VertexShader* vs);	// 空描画
	void DrawSea(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 海描画

	int* getMoney();					// 金額受け渡し
	int* getPer();						// 達成度受け渡し
	int* getTime();						// クリアタイム受け渡し

private:
	void LoadMap(/*enum crntStage, */list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);

	bool m_start, m_count;				// ゲームスタートフラグ・
	int time;
	int addtime;
	float Alpha;

	// 他シーンへデータ引継ぎ用
	int* pMoney, pPer, pTime;

	// 各ゲームデータ用
	VertexShader* m_pVS;
	CameraBase* m_pCamera;
	CPlayer* m_pPlayer;
	CObjectMng* m_pObjectMng;
	Object* m_pObject;
	CCollisionAreaMng* m_pCollisionAreaMng;
	CCollision* m_pCollision;
	CTimer* m_pTimer;
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

	Model* m_pSkyModel;		// 空モデル
	Model* m_pSeaModel;		// 海モデル
};

CUI* GetUI();

#endif // __SCENE_GAME_H__