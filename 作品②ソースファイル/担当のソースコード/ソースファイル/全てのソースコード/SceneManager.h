//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== �C���N���[�h�� ==========
#include "SoundManager.h"
#include "Fade.h"
#include "RoadUI.h"
#include "TSuction.h"
// ���݃C���N���[�h�h�~
class CSceneTitle;
class CSceneSelect;
class CSceneStageBase;
class SceneResult;
class SceneOpening;
class SceneEnding;

// ========== �N���X ==========
class CSceneMng
{
public:
	enum SceneKind		// �X�e�[�W�̎�ށA����
	{
		SCENE_STAGE1,
		SCENE_STAGE2,
		SCENE_STAGE3,
		MAX_STAGE,

		SCENE_TITLE = 3,
		SCENE_SELECT,
		SCENE_RESULT,
		SCENE_RESTART,
		SCENE_OPENING,
		SCENE_ENDING,
		SCENE_MAX,
	};

public:
	CSceneMng();
	~CSceneMng();
	void Update(float tick);
	void Draw();

	void SetNextScene(SceneKind scene);	// ���̃V�[����ݒ肵�A�J�ڂ���
	void GameRestart();					// �Q�[�������X�^�[�g����(�����[�h)
	void SetGameEnd();					// �Q�[���I��������

	bool GetGameEnd();					// �Q�[���I���󋵂��擾
	int* GetClearCnt();					// �e�X�e�[�W�N���A��
	int  GetMoney();					// ���݂̏������擾
	int* GetClearTime();				// �e�X�e�[�W�ő��N���A�^�C���擾
	int* GetScore();					// �e�X�e�[�W�ō��X�R�A�擾
	int  GetOpenStageNum();				// �X�e�[�W�J����
	bool GetOpenStage();				// �X�e�[�W�J�����邩
	bool isVewEnd();					// �G���f�B���O�����ς݂�
	void SetVewEnd();					// �G���f�B���O�����ς݂ɐݒ�
	void SetTSuction(TSuction* pTSuction);
private:
	void SceneSwap();					// �V�[����؂�ւ���
	void RestartSwap();					// ���X�^�[�g�V�[���J��
	void LoadGameScene();				// �Q�[���V�[����ǂݍ��݁A���̊ԃ��[�h��ʂ�\��
	void Load();						// �Q�[���V�[�����쐬����

	// ----- ���̃V�[���ŕK�v�ȏ��������p�� -----
	void PassData(CSceneSelect* select, CSceneStageBase* stage);	// Select �� Stage
	void PassData(CSceneStageBase* stage, SceneResult* result);		// Stage  �� Result

private:
	// ----- �V�[���Ǘ� -----
	bool m_GameEnd;			// �Q�[�����[�v������
	int	 m_scene;			// ���ݎ��s���̃V�[��
	int	 m_nextScene;		// ���̃V�[��
	int	 m_oldPlayStage;	// �O��V�񂾃X�e�[�W
	bool m_loadEnd;			// ���[�h�I��������
	bool m_isViewEnding;	// �G���f�B���O���������Ƃ��邩

	// ----- �V�[���f�[�^ -----
	SceneOpening*		m_pOpening;		// �I�[�v�j���O
	CSceneTitle*		m_pTitle;		// �^�C�g��
	CSceneSelect*		m_pSelect;		// �Z���N�g
	CSceneStageBase*	m_pStage;		// �X�e�[�W
	SceneResult*		m_pResult;		// ���U���g
	SceneEnding*		m_pEnding;		// �G���f�B���O

	// ----- �Q�[���S�̂ŕێ�����f�[�^ -----
	CSoundMng*	m_pSoundMng;			// �T�E���h
	Fade*		m_pFade;				// �t�F�[�h
	Road* m_pRoad;						// ���[�h
	//�G�t�F�N�g
	TSuction* m_pTSuction;
	int m_money;						// �������z
	int m_clearTime[MAX_STAGE];			// �e�X�e�[�W�ő��N���A�^�C��
	int m_score[MAX_STAGE];				// �e�X�e�[�W�ō����|����
	int m_clearCount[MAX_STAGE];		// �e�X�e�[�W�N���A��
	int m_openStageNum;					// �X�e�[�W�J����
	bool m_openStage;					// �X�e�[�W�J�����邩
};

#endif // !__SCENE_MANAGER_H__