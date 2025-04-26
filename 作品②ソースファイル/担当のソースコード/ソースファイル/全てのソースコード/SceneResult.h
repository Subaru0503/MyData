//SceneResult.h
//=====�C���N���[�h�K�[�h=====
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__
//=====�C���N���[�h��=====
#include "Shader.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Result_BG.h"
#include "Result_Star.h"
#include "Result_Percent.h"
#include "Result_Message.h"
#include "Result_Time.h"
#include "UI.h"
#include "Result_Stamp.h"
#include "Result_Player.h"
#include "Result_Window.h"

//=====�N���X=====
class SceneResult
{
public:
	SceneResult(CSceneMng* pSceneMng, CSoundMng* pSoundMng);
	~SceneResult();
	void Update(float tick);
	void Draw();
	void SetMoney(int money);				//���z�󂯎��
	void SetPer(int per);					//�B���x�󂯎��
	void SetTime(int time);					//�N���A�^�C���󂯎��
	void SetOldPlayStage(int stage);		// �O��v���C�X�e�[�W�ԍ��擾

private:
	VertexShader* m_pVS;
	ResultBG* m_pBG;
	ResultStar* m_pStar[3];
	ResultPer* m_pPer;
	ResultMsg* m_pMsg;
	ResultTime* m_pTime;
	CUI* m_pUI;
	ResultStamp* m_pStamp;
	ResultPlayer* m_pPlayerUI;
	ResultWindow* m_pWindow;
	CSoundMng* m_pSoundMng;		// �T�E���h
	CSceneMng* m_pSceneMng;		// �V�[���}�l�[�W���[
	bool m_select;
	bool m_SoundOne;
	bool m_SoundStop;
	int m_nMoney;				//�҂������z
	int m_nPer;					//�B���x
	int m_nTime;				//�N���A�^�C��	
	int m_oldPlayStage;			// �O��v���C�X�e�[�W
	int m_EndingCountDown;		// �G���f�B���O�����Đ��܂ł̃J�E���g�_�E��
};

#endif