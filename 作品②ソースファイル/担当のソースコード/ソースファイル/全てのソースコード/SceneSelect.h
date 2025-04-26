//=================================================================
//
//	SceneSelect.h
//	�X�e�[�W�I���V�[��
//
//=================================================================
#ifndef __SCENE_SELECT_H__
#define __SCENE_SELECT_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"	// �V�[���J�ڏ����p
#include "SoundManager.h"	// �T�E���h�Đ��p
#include "CameraBase.h"
#include "CameraSelect.h"	// �Z���N�g�V�[���J����
#include "ShopMenu.h"
#include "Select.h"
#include "ShopBG.h"
#include "Planet.h"			// �f���N���X�Ǘ��p
#include "Select_Score.h"
#include "UI.h"
#include "Model.h"
#include "Shader.h"
#include "Value.h"
#include "Fade.h"

// ========== �N���X ==========
class CSceneSelect
{
public:
	CSceneSelect(CSceneMng* pSceneMng, CSoundMng* pSoundMng, Fade* pFade, int OldPlayStage);
	~CSceneSelect();
	void Update(float tick);
	void Draw();
	void DrawSelect(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// �F���`��
	int* GetItem();			// �A�C�e���g�p���Q�b�g
	Planet* GetPlanet(int num);

private:
	void StageSawpLeft();
	void StageSawpRight();

private:
	// ----- �V�[����ԊǗ� -----
	bool m_bShop;			// �V���b�v�t���O
	bool m_camMove;			// �J�����ړ����t���O
	int  m_select;			// �I����
	bool m_openStage;		// �X�e�[�W�J������
	int  m_openFrame;		// �X�e�[�W�J��UI�\���t���[��
	bool m_openUI;			// �u�V�����˗��vUI�\������
	int m_nMoney;			// ���������ϐ�
	bool m_sceneSwap;		// �V�[���J�ڊJ�n������

	// ���V�[���ֈ��p���p
	int m_nItem[MAX_ITEM];	// �A�C�e���g�p�i�[�ϐ�

	// ----- �V�[���f�[�^ -----
	CSceneMng* m_pSceneMng;
	CSoundMng* m_pSoundMng;
	CCameraSelect* m_pCamera;

	CShopMenu* m_pShopMenu;	// �V���b�v���j���[
	ShopBG* m_pShopBG;
	Planet* m_pPlanets[CSceneMng::SceneKind::MAX_STAGE];	// �f���܂Ƃ�
	Select* m_pSelect;
	SelectScore* m_pScore;
	CUI* m_pMoney;
	VertexShader* m_pVS;	// �V�F�[�_�[
	Model* m_pSelectModel;	// �w�i���f��
	Fade* m_pFade;
};

#endif // !__SCENE_SELECT_H__