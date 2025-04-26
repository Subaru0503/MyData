//=================================================================
//
//	SceneTitle.cpp
//	�^�C�g���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneTitle.h"
#include "Input.h"
#include  "XController.h"


// ========== �R���X�g���N�^ ==========
CSceneTitle::CSceneTitle(CSceneMng* pSceneMng, CSoundMng* pSoundMng)
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
	, animestart(false)
	, animefin(false)
	, m_startPush(false)
{
	m_pTitle = new TItle();
	m_pEscape = new EscapeUI();
	m_pTSuction = new TSuction();
	m_pSceneMng->SetTSuction(m_pTSuction);
}

// ========== �f�X�g���N�^ ==========
CSceneTitle::~CSceneTitle()
{
	SAFE_DELETE(m_pTitle);
	SAFE_DELETE(m_pEscape);
	SAFE_DELETE(m_pTSuction);
}

// ========== Update�֐� ==========
void CSceneTitle::Update()
{
	// =-=-= �Q�[���I���m�F��� =-=-=
	XINPUT_STATE state;
	XINPUT_KEYSTROKE stroke;
	XInputGetState(0, &state);
	XInputGetKeystroke(0, 0, &stroke);
	//�L�[�{�[�h�E�R���g���[���[����
	if (m_pushEsc) {
		// ----- �{�^���I���󋵁F�͂� -----
		if (m_select) {
			if (IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT) ||
				(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLX > 0 &&
					state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_RIGHT&&stroke.Flags == 0x0001))			// �������ɃJ�[�\���ړ�
			{
				m_select ^= 1;
				m_pEscape->SetNo();
				m_pSoundMng->playSound(CSoundMng::SystemSE::select);

			}
			else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE)
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// �Q�[���I��
			{
				m_pSceneMng->SetGameEnd();
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
		// ----- �{�^���I���󋵁F������ -----
		else {
			if (IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT) ||
				(state.dwPacketNumber != 3435973836 && state.Gamepad.sThumbLX < 0 &&
					state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && stroke.Flags == 0x0001
					|| state.Gamepad.wButtons&XINPUT_GAMEPAD_DPAD_LEFT&&stroke.Flags == 0x0001))				// �͂��ɃJ�[�\���ړ�
			{
				m_select ^= 1;
				m_pEscape->SetYes();
				m_pSoundMng->playSound(CSoundMng::SystemSE::select);
			}
			else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE)
				|| state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)	// �m�F��ʂ����
			{
				m_pushEsc = false;
				m_pEscape->SetWindowAnime();
				m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
			}
		}
	}

	// =-=-= �^�C�g����� =-=-=
	else {	// �I���m�F��ʂ��J���Ă��Ȃ�
		if (IsKeyTrigger(VK_ESCAPE) || state.Gamepad.wButtons&XINPUT_GAMEPAD_START)	m_pushEsc = true;		// ESC�Ŋm�F��ʊJ��

		// ----- �Q�[���X�^�[�g -----
		else if ((IsKeyTrigger(VK_RETURN) || state.Gamepad.wButtons&XINPUT_GAMEPAD_A&&stroke.Flags == 0x0001)) {
			if (!m_startPush) {
				m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
				//m_pTitle->Update();
				m_startPush = true;
				animestart = true;
			}
		}
	}

	if (animestart)
	{
		animefin = m_pTitle->AnimeButton();
		if (animefin)
		{
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
			animestart = false;
		}
	}
	
	// =-=-= �e��X�V =-=-=
	// ----- �{�^���A�j���[�V���� -----
	m_pTitle->Update();
	//m_pTSuction->Update();
	m_pEscape->Update();


	
}

// ========== Draw�֐� ==========
void CSceneTitle::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);

	m_pTitle->Draw();
	//if (!m_pTitle->GetPlayerAnime())//�L��������ʒu�ɂ�����G�t�F�N�g��`��
	//{
	//	m_pTSuction->Draw();
	//}
	if (m_pushEsc)	{	// �I���m�F��ʒ��̓E�B���h�E�\��
		m_pEscape->Draw();
	}

	
}