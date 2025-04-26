//SceneGame.h
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
//=====�C���N���[�h��=====
// ----- �V�X�e�� -----
#include "SceneManager.h"
#include "SoundManager.h"
#include "CameraBase.h"
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


//=====�N���X=====
class SceneGame
{
public:
	SceneGame(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~SceneGame();
	void Update(float tick);
	void Draw();

	void DrawSky(DirectX::XMFLOAT4X4 *mat, VertexShader* vs);	// ��`��
	void DrawSea(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// �C�`��

	int* getMoney();					// ���z�󂯓n��
	int* getPer();						// �B���x�󂯓n��
	int* getTime();						// �N���A�^�C���󂯓n��

private:
	void LoadMap(/*enum crntStage, */list<Object*>* pObjList, list<CCollisionArea*>* pAreaList, CPlayer* pPlayer, CObjectMng* pObjMng);

	bool m_start, m_count;				// �Q�[���X�^�[�g�t���O�E
	int time;
	int addtime;
	float Alpha;

	// ���V�[���փf�[�^���p���p
	int* pMoney, pPer, pTime;

	// �e�Q�[���f�[�^�p
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

	Model* m_pSkyModel;		// �󃂃f��
	Model* m_pSeaModel;		// �C���f��
};

CUI* GetUI();

#endif // __SCENE_GAME_H__