//=================================================================
//
//	SceneStageBase.h
//	�X�e�[�W�V�[���̋��ʕ���
//
//=================================================================

#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__

// ========== �C���N���[�h�� ==========
#include <vector>
#include "Value.h"
// ----- �V�X�e�� -----
#include "SceneManager.h"
#include "SoundManager.h"
#include "Model.h"
#include "Shader.h"
// ----- �I�u�W�F�N�g -----
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
// ----�G�t�F�N�g----
#include "DustCloud.h"
#include "Leaf.h"
#include "Bag.h"
using namespace std;


//=====�萔�E�}�N����`=====
#define MAX_PAUSEMENU	(3)
// ----- �J�������[�N -----
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

// ========== �N���X ==========
class CSceneStageBase
{
public:
	CSceneStageBase(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	virtual ~CSceneStageBase();
	virtual void Init();
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

	virtual void ItemCheck(int* item);			// �A�C�e���g�p�̊m�F�֐�

	virtual int getMoney();						// ���z�n��
	virtual int getPer();						// �B���x�n��
	virtual int getTime();						// �N���A�^�C���n��
	virtual CPlayer* GetPlayer();
protected:
	virtual void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs) = 0;	// ���`��
	virtual void LoadMap(list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng) = 0;

	bool m_start, m_count;		// �Q�[���X�^�[�g�t���O
	bool m_pause;				// �|�[�Y��ʃt���O
	int  m_pauseSelect;			// �|�[�Y���j���[�I����
	int time;
	int addtime;
	float Alpha;
	bool m_flg, m_zoomFlg;
	int m_wait, m_frame;
	float m_camRad, m_camPosY, m_horizon, m_horizonRad, m_vertical, m_factor, m_value;
	// �m�F�p�t���O
	int m_nCheck;

	// ���V�[������󂯎��p
	int m_nItem[MAX_ITEM];

	// ���V�[���փf�[�^���p���p
	int* pMoney, pPer, pTime;

	// �e�Q�[���f�[�^�p
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

	Model* m_pStageModel[3];		// ���E�C�E�󃂃f��

	Pause* m_pPause;
	Dust* m_pDust;
	Leaf* m_pLeaf;
	EBag* m_pEBag;
	Tutorial* m_pTutorial;
	TradeIcon* m_pTradeIcon;
};

#endif // !__SCENE_STAGE_BASE_H__
