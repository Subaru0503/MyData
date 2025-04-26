//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "SceneStageBase.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneResult.h"
#include "SceneOpening.h"
#include "SceneEnding.h"

#include <thread>

// ========== �萔�E�}�N����` ==========
#define FADE_IN			(true)
#define FADE_OUT		(false)
#define FADE_IN_TIME	(1.0f)
#define FADE_OUT_TIME	(1.0f)

// ========== �R���X�g���N�^ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_OPENING)
	, m_nextScene(SCENE_OPENING)
	, m_GameEnd(false)
	, m_oldPlayStage(SCENE_STAGE1)
	, m_money(0)
	, m_clearTime{ 999, 999, 999 }
	, m_score{ 0 }
	, m_clearCount{ 0 }
	, m_openStageNum(0)
	, m_openStage(false)
	, m_loadEnd(false)
	, m_isViewEnding(false)
{
	// =-=-= �f�[�^�쐬 =-=-=
	m_pSoundMng = new CSoundMng();		// �T�E���h
	m_pFade = new Fade();				// �t�F�[�h
	m_pRoad = new Road();
	m_pOpening = new SceneOpening(this, m_pSoundMng);
}

// ========== �f�X�g���N�^ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= �V�[���ɉ������f�[�^�폜 =-=-=
	// ���݂��Ă���΍폜
	switch (m_scene)
	{
	case SCENE_OPENING: SAFE_DELETE(m_pOpening); break;
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_SELECT:	SAFE_DELETE(m_pSelect); break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	SAFE_DELETE(m_pStage);  break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	case SCENE_ENDING:	SAFE_DELETE(m_pEnding); break;
	default: break;
	}
	SAFE_DELETE(m_pSoundMng);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pRoad);
}

// ========== �X�V ==========
void CSceneMng::Update(float tick)
{
	if (!m_pFade->IsPlay()) {			//�����ȏ����̓t�F�[�h�������I����Ă���B
		if (m_scene != m_nextScene) {	// �V�[���`�F���W���s���Ă���ΑJ��
			if (m_nextScene != SCENE_RESTART) SceneSwap();
			else RestartSwap();
		}
	}

	// =-=-= �V�[���ɉ������X�V =-=-=
	switch (m_scene)
	{
	case SCENE_OPENING: m_pOpening->Update();		break;
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_SELECT:	m_pSelect->Update(tick);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	m_pStage->Update(tick); 	break;
	case SCENE_RESULT:	m_pResult->Update(tick);	break;
	case SCENE_ENDING:  m_pEnding->Update();		break;
	default: break;
	}

	// ----- �e��X�V -----
	m_pSoundMng->DeleteSpeaker();	// �Đ��I�������X�s�[�J�[��j��
	m_pFade->Update();
}

// ========== �`�� ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_OPENING: m_pOpening->Draw(); break;
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_SELECT:	m_pSelect->Draw();	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	m_pStage->Draw();	break;
	case SCENE_RESULT:	m_pResult->Draw();	break;
	case SCENE_ENDING:  m_pEnding->Draw();  break;
	default: break;
	}
	m_pFade->Draw();
}

// ========== �V�[���؂�ւ��ݒ� ==========
// ���@���FSceneKind �J�ڐ�V�[��
// �߂�l�F�Ȃ�
// �w��̃V�[����J�ڐ�ɐݒ�B
// ======================================
void CSceneMng::SetNextScene(SceneKind scene)
{
	// �t�F�[�h���͎��̃V�[����\�񂵂Ȃ�
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = scene;	// ���V�[���\��

	// ----- �t�F�[�h -----
	// �G���f�B���Oor�I�[�v�j���O���^�C�g���̏ꍇ�̂ݔ��t�F�[�h
	if (m_nextScene == SCENE_TITLE && (m_scene == SCENE_ENDING || m_scene == SCENE_OPENING)) {
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);
		return;
	}

	switch (m_nextScene)
	{
	case SCENE_TITLE:
	case SCENE_SELECT:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::PLANET);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);	break;
	case SCENE_RESULT:
	case SCENE_ENDING:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	break;
	default:	break;
	}

}

// ========== �V�[���؂�ւ� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �w��̃V�[���ɐ؂�ւ��A�K�v���������p��
// ==================================
void CSceneMng::SceneSwap()
{
	switch (m_scene)	// �V�񂾃X�e�[�W�̏����i�[
	{
	case SCENE_STAGE1:	m_oldPlayStage = SCENE_STAGE1;	break;
	case SCENE_STAGE2:	m_oldPlayStage = SCENE_STAGE2;	break;
	case SCENE_STAGE3:	m_oldPlayStage = SCENE_STAGE3;	break;
	}

	// =-=-= �V�����V�[���̓ǂݍ��� =-=-=
	m_pSoundMng->AllDeleteSpeaker();
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this, m_pSoundMng);	// �V�[���J�ڏ����Ăяo���̂���SceneMng*�󂯓n��
		m_pSoundMng->playSound(CSoundMng::BGM::title);	// ���̃V�[����BGM���Đ�
		m_pSoundMng->StopSound(CSoundMng::BGM::Op);
		m_pSoundMng->StopSound(CSoundMng::BGM::Ed);
		break;
	case SCENE_SELECT:
		m_pSelect = new CSceneSelect(this, m_pSoundMng, m_pFade, m_oldPlayStage);
		m_pSoundMng->playSound(CSoundMng::BGM::Select);
		break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3: LoadGameScene();	m_pStage->Init(); break;
	case SCENE_RESULT:
		m_pResult = new SceneResult(this, m_pSoundMng);
		break;
	case SCENE_ENDING: m_pEnding = new SceneEnding(this, m_pSoundMng);
	}

	// =-=-= �K�v�����p�� =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	break;
	case SCENE_SELECT:	if (m_nextScene != SCENE_TITLE) PassData(m_pSelect, m_pStage); break;	// �Q�[���X�e�[�W��
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	if (m_nextScene == SCENE_RESULT)PassData(m_pStage, m_pResult);	break;	// ���U���g��
	case SCENE_RESULT:	break;
	}

	// =-=-= ���݂̃V�[���폜 =-=-=
	switch (m_scene)
	{
	case SCENE_OPENING: SAFE_DELETE(m_pOpening); break;
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_SELECT:	SAFE_DELETE(m_pSelect);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:	SAFE_DELETE(m_pStage);	break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	break;
	case SCENE_ENDING:  SAFE_DELETE(m_pEnding); break;
	default: break;
	}

	switch (m_nextScene)
	{
	case SCENE_TITLE:
		if (m_scene == SCENE_ENDING || m_scene == SCENE_OPENING) {
			m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);	break;
		}
	case SCENE_SELECT:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::PLANET);	break;
	case SCENE_STAGE1:
	case SCENE_STAGE2:
	case SCENE_STAGE3:
	case SCENE_RESULT:
	case SCENE_ENDING:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);	break;
	default: break;
	}

	m_scene = m_nextScene;	// �V�[�����㏑��
}

// ========== �Q�[�����[�f�B���O ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Q�[���V�[�����쐬���A���̊ԃ��[�h��ʂ�\��
// ======================================
void CSceneMng::LoadGameScene()
{
	// =-=-= ���[�h�J�n =-=-=
	std::thread LoadThread(&CSceneMng::Load, this);	// �V�[�����[�h�X���b�h���쐬
	m_pRoad->SetRatio();
	m_loadEnd = false;
	// =-=-= ���[�h�� =-=-=
	while (1)
	{
		// ----- ��ʍX�V���� -----


		//�����Ƀ��[�f�B���O��ʂ�Update
		m_pFade->Update();
		m_pRoad->Update(m_nextScene);


		//Draw����
		BeginDrawDirectX();

		m_pFade->Draw();
		m_pRoad->Draw();

		EndDrawDirectX();



		// =-=-= ���[�h�I�� =-=-=
		if (m_loadEnd) {
			LoadThread.join();	// �X���b�h�̏I����҂�
			m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	// tips�������Ȃ����邽��
			while (m_pFade->GetAlpha() < 1.0f)
			{
				// ���������������������ɂ�Update
				m_pRoad->Update(m_nextScene);
				m_pFade->Update();

				// ���������������������ɂ�Draw
				BeginDrawDirectX();

				m_pRoad->Draw();
				m_pFade->Draw();

				EndDrawDirectX();
			}


			break;
		}
	}
}

// ========== �Q�[���V�[�����[�h ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Q�[���V�[�����쐬
// ======================================
void CSceneMng::Load()
{
	switch (m_nextScene)
	{
	case SCENE_STAGE1:
		m_pStage = new CSceneStage1(this, m_pSoundMng);
		break;
	case SCENE_STAGE2:
		m_pStage = new CSceneStage2(this, m_pSoundMng);
		break;
	case SCENE_STAGE3:
		m_pStage = new CSceneStage3(this, m_pSoundMng);
		break;
	}
	m_loadEnd = true;

	return;
}

// ========== �Q�[�����X�^�[�g ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���X�^�[�g�̐ݒ������
// ==================================
void CSceneMng::GameRestart()
{
	// �t�F�[�h���͎��̃V�[����\�񂵂Ȃ�
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = SCENE_RESTART;	// ���V�[���\��

	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);
}

// ========== �Q�[�����X�^�[�g�p�V�[���J�� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// ���݂̃V�[���Ɠ����Q�[���V�[����ǂݍ���
// ==================================
void CSceneMng::RestartSwap()
{
	m_nextScene = m_scene;
	m_pSoundMng->AllDeleteSpeaker();
	SAFE_DELETE(m_pStage);

	LoadGameScene();
	m_pStage->Init();

	m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);
}

// ========== �V�[���ԃf�[�^���p��:Select �� Stage==========
// ���@���F
// CSceneSelect* 
// CSceneStageBase* 
// �߂�l�F�Ȃ�
// �`�֐��T�v�`
// �Z���N�g����X�e�[�W�V�[���֕K�v�ȃf�[�^�������p��
// ========================================================
void CSceneMng::PassData(CSceneSelect * select, CSceneStageBase * stage)	// Select �� Stage
{
	// ----- �󂯓n�� -----
	stage->ItemCheck(select->GetItem());	// �A�C�e���g�p���
}

// ========== �V�[���ԃf�[�^���p��:Stage �� ���U���g==========
// ���@���F
// SceneStage* 
// SceneResult* 
// �߂�l�F�Ȃ�
// �`�֐��T�v�`
// �X�e�[�W���烊�U���g�V�[���֕K�v�ȃf�[�^�������p��
// ========================================================
void CSceneMng::PassData(CSceneStageBase * stage, SceneResult * result)
{
	// =-=-= �J�ڐ�փf�[�^�󂯓n�� =-=-=
	int per;	// �B���x�̒l�����p

	// ----- �l���� -----
	per = stage->getPer();
	if (per >= 100)	per = 100;						// ���ӂ�Ă�����P�O�O���ɂ��낦��

	// ----- �󂯓n�� -----
	result->SetMoney(stage->getMoney());			// ������
	result->SetTime(stage->getTime());				// �N���A�^�C��
	result->SetPer(per);							// �B���x
	result->SetOldPlayStage(m_scene);				// �v���C�����X�e�[�W�ԍ�(���X�^�[�g�����̂���)

	// =-=-= �Z���N�g��ʗp�̒l�ۑ� =-=-=
	// ----- �v���C�f�[�^�X�V -----
	if (stage->getPer() >= 60) {
		m_clearCount[m_scene]++;						// �N���A�񐔉��Z
	}
	m_money += stage->getMoney();					// ���������Z
	if (m_clearTime[m_scene] > stage->getTime()) {	// �ő��Ȃ�
		m_clearTime[m_scene] = stage->getTime();	// �ő��N���A�^�C���X�V
	}
	if (m_score[m_scene] < stage->getPer()) {		// �ō��Ȃ�
		m_score[m_scene] = stage->getPer();			// �n�C�X�R�A�X�V
	}

	// ----- �X�e�[�W�J���󋵍X�V -----
	if ((m_scene == m_openStageNum) && (m_scene < MAX_STAGE - 1)) {				// �v���C�����̂��ŐV�}�b�v�ł��邩
		if (m_score[m_scene] >= 60) {				// �m���}�B�����Ă����
			m_openStageNum++;						// �X�e�[�W�J�������Z
			m_openStage = true;						// �X�e�[�W�J��
		}
	}
}

// ========== Get ==========

// �Q�[���I����
bool CSceneMng::GetGameEnd()
{
	return m_GameEnd;
}

// ���݂̏������z
int CSceneMng::GetMoney()
{
	return m_money;
}

// �e�X�e�[�W�̍ő��N���A�^�C�����z��
int * CSceneMng::GetClearTime()
{
	return m_clearTime;
}

// �e�X�e�[�W�̍ō��X�R�A���z��
int * CSceneMng::GetScore()
{
	return m_score;
}

// �e�X�e�[�W�̃N���A�񐔏��z��
int* CSceneMng::GetClearCnt()
{
	return m_clearCount;
}

// �X�e�[�W�J����
int CSceneMng::GetOpenStageNum()
{
	return m_openStageNum;
}

// �X�e�[�W�J�������𖞂�������
bool CSceneMng::GetOpenStage()
{
	if (m_openStage) {
		m_openStage = false;	// �f���J���͊e�f����x����̏����̂��߃t���O����
		return true;
	}
	else {
		return false;
	}

	// **�t���O�̊Ǘ���SceneMng�Ŋ����������������̂ŁA�ǂ݂ɂ����ł��������Ńt���O���������Ă��܂��B
}

bool CSceneMng::isVewEnd()
{
	return m_isViewEnding;
}

void CSceneMng::SetVewEnd()
{
	m_isViewEnding = true;
}

// ========== Set ==========

// �Q�[���I���t���O�𗧂Ă�
void CSceneMng::SetGameEnd()
{
	m_GameEnd = true;
}

void CSceneMng::SetTSuction(TSuction * pTSuction)
{
	m_pTSuction = pTSuction;
}