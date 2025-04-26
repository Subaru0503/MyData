//=================================================================
//
//	SoundManager.cpp
//	SE���ꌳ�Ǘ�����
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SoundManager.h"

// ========== �萔�E�}�N����` ==========
// ----- �萔 -----
#define TITLE_BGM_VOL			(0.1f)	// �^�C�g��BGM
#define GAEM_BGM_VOL			(0.5f)	// �Q�[��BGM
#define GAEM2_BGM_VOL			(0.2f)	// �Q�[��2BGM
#define GAEM3_BGM_VOL			(0.2f)	// �Q�[��3BGM
#define SELECT_BGM_VOL			(1.0f)	//�X�e�[�W�Z���N�gBGM
#define DECSION_VOL				(0.2f)	// ���� 
#define CANCEL_VOL				(1.0f)	// �L�����Z�� 
#define SELECT_VOL				(1.0f)	// �I�� 
#define TSTRAT_VOL				(1.0f)	//�Q�[���J�n(�^�C�g��)
#define SWAP_VOL				(0.5f)	//�X�e�[�W�`�F���W
#define OP_BGM_VOL				(1.0f)	//�I�[�v�j���O
#define ED_BGM_VOL				(1.0f)	//�G���f�B���O
#define RPON_VOL				(1.0f)	// ���U���gSE
#define WALK_GRASS_VOL			(1.0f)	// ���F���� 
#define RAN_GRASS_VOL			(1.0f)	// ���F���� 
#define WALK_GROUND_VOL			(1.0f)	// �y�F���� 
#define RAN_GROUND_VOL			(1.0f)	// �y�F���� 
#define WALK_CREAM_VOL			(1.0f)	// �N���[���F���� 
#define RAN_CREAM_VOL			(0.7f)	// �N���[���F���� 
#define WALK_SPONGE_VOL			(1.0f)	// �X�|���W�F���� 
#define RAN_SPONGE_VOL			(1.0f)	// �X�|���W�F���� 
#define GAMEOVER_VOL			(1.0f)	// �Q�[���I�[�o�[ 
#define GAMECLEAR_VOL			(1.0f)	// �Q�[���N���A 
#define STAMP_VOL				(1.0f)	// �n���R 
#define STAR_VOL				(1.0f)	// �� 
#define WIND_VOL				(0.8f)	// �z�����ݒ� 
#define WIND2_VOL				(0.8f)	// �z�����ݒ�(��)
#define WIND3_VOL				(0.8f)	// �z�����ݒ�(��)
#define SUCTION_HIGH_VOL		(1.0f)	// �z�����݊���(�|���b)�F������ 
#define SUCTION_LOW_VOL			(1.0f)	// �z�����݊���(�|���b)�F�Ⴂ�� 
#define MONEY_VOL				(1.0f)	// �����`������ 
#define COUNTDOWN_1_VOL			(1.0f)	// �X�^�[�g�J�E���g�_�E���P 
#define COUNTDOWN_1_PI_VOL		(1.0f)	// �X�^�[�g�J�E���g�_�E���P �ҁ[
#define COUNTDOWN_2_VOL			(1.0f)	// �X�^�[�g�J�E���g�_�E���Q 
#define TIMEUP_1_VOL			(1.0f)	// �^�C���A�b�v 
#define TIMEUP_2_VOL			(1.0f)	// �x�� 
#define WATCH_SLOW_VOL			(1.0f)	// �b�j�F������� 
#define WATCH_EALY_VOL			(1.0f)	// �b�j�F���� 
#define WOOD_VOL				(1.0f)	// �ؔj�� 
#define WOOD_BREAK_VOL			(1.0f)	// �ؔj�󊮗� 
#define ROCK_VOL				(1.0f)	// ��j�� 
#define ROCK_BREAK_VOL			(1.0f)	// ��j�󊮗� 
#define WOOD_HOUSE_VOL			(1.0f)	// �؂̉Ɣj�� 
#define WOOD_HOUSE_BREAK_VOL	(0.1f)	// �؂̉Ɣj�󊮗� 
#define ROCK_HOUSE_VOL			(1.0f)	// �΂̉Ɣj�� 
#define ROCK_HOUSE_BREAK_VOL	(0.5f)	// �΂̉Ɣj�󊮗� 
#define BUY_VOL					(1.0f)	// �w������(���W��) 
#define TEXT_VOL				(1.0f)	// �e�L�X�g�̃v���v���� 
#define COOKIE_VOL				(1.0f)	// �N�b�L�[
#define COOKIEBREAK_VOL				(1.0f)	// �N�b�L�[�j��
#define FIRE_VOL				(1.0f)	// ����
#define AOKINOKO_VOL			(1.0f)	// �A�I�L�m�R

// ----- �}�N�� -----
#define STR(var) #var   //�����ɂ����ϐ���ϐ���������������Ƃ��ĕԂ��}�N���֐�

// ========== �R���X�g���N�^ ==========
CSoundMng::CSoundMng()
{
	// =-=-= �eBGM�ǂݍ��� =-=-=
	m_pSoundMap[STR(CSoundMng::BGM::title)] = LoadSound("Assets/BGM/�^�C�g��.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game)] = LoadSound("Assets/BGM/�X�e�[�W�P.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Select)] = LoadSound("Assets/BGM/�X�e�[�W�Z���N�g.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game2)] = LoadSound("Assets/BGM/�X�e�[�W2.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game3)] = LoadSound("Assets/BGM/�X�e�[�W3.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Op)] = LoadSound("Assets/BGM/op.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::Ed)] = LoadSound("Assets/BGM/ed.mp3", true);

	// =-=-= �eSE��ǂݍ��� =-=-=
	// ----- �V�X�e�� -----
	m_pSoundMap[STR(CSoundMng::SystemSE::decision)] = LoadSound("Assets/SE/�V�X�e����/����.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::cancel)] = LoadSound("Assets/SE/�V�X�e����/�L�����Z��.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::select)] = LoadSound("Assets/SE/�V�X�e����/�I��.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)] = LoadSound("Assets/SE/�V�X�e����/�Q�[���J�n(�^�C�g��).mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::swap)] = LoadSound("Assets/SE/�V�X�e����/�X�e�[�W�`�F���W.mp3");
	m_pSoundMap[STR(CSoundMng::SystemSE::Fpon)] = LoadSound("Assets/SE/�V�X�e����/Fileopen.mp3");
	// ----- �v���C���[ -----
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkGrass)] = LoadSound("Assets/SE/�v���C���[/�Ő������.mp3"); // ���F����
	m_pSoundMap[STR(CSoundMng::PlayerSE::ranGrass)] = LoadSound("Assets/SE/�v���C���[/�Ő��𑖂�.mp3"); // ��:����
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkGround)] = LoadSound("Assets/SE/�v���C���[/�y�����.mp3"); // �y�F����
	m_pSoundMap[STR(CSoundMng::PlayerSE::ranGround)] = LoadSound("Assets/SE/�v���C���[/�y�𑖂�.mp3"); // �y:����
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkCream)] = LoadSound("Assets/SE/�v���C���[/�N���[�������.mp3"); // �N���[���F����
	m_pSoundMap[STR(CSoundMng::PlayerSE::runCream)] = LoadSound("Assets/SE/�v���C���[/�N���[������.mp3"); // �N���[��:����
	m_pSoundMap[STR(CSoundMng::PlayerSE::walkSponge)] = LoadSound("Assets/SE/�v���C���[/�X�|���W�����.mp3"); // �X�|���W�F����
	m_pSoundMap[STR(CSoundMng::PlayerSE::runSponge)] = LoadSound("Assets/SE/�v���C���[/�X�|���W�𑖂�.mp3"); // �X�|���W:����

	// ------���U���g--------
	m_pSoundMap[STR(CSoundMng::ResultSE::gameClear)] = LoadSound("Assets/BGM/�Q�[���N���A.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::gameOver)] = LoadSound("Assets/BGM/�Q�[���I�[�o�[.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::stamp)] = LoadSound("Assets/SE/���U���g/���U���g�n���R��.mp3");
	m_pSoundMap[STR(CSoundMng::ResultSE::star)] = LoadSound("Assets/SE/���U���g/���U���g��.mp3");

	//-------�z������--------
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind)] = LoadSound("Assets/SE/�z������/Suction1.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::suctionLow)] = LoadSound("Assets/SE/�z������/pon1.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::suctionHigh)] = LoadSound("Assets/SE/�z������/pon2.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::money)] = LoadSound("Assets/SE/�z������/coin_03.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind2)] = LoadSound("Assets/SE/�z������/Suction2.mp3");
	m_pSoundMap[STR(CSoundMng::SuctionSE::wind3)] = LoadSound("Assets/SE/�z������/Suction3.mp3");

	//------����-------
	m_pSoundMap[STR(CSoundMng::TimeSE::countDown1)] = LoadSound("Assets/SE/����/�J�E���g�_�E��2.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::countDown1_pi)] = LoadSound("Assets/SE/����/�J�E���g�_�E��1_��.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::timeUp1)] = LoadSound("Assets/SE/����/�^�C�}�[�X�g�b�v.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::timeUp2)] = LoadSound("Assets/SE/����/�^�C�}�[�X�g�b�v2.mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::watchSlow)] = LoadSound("Assets/SE/����/�������ԂP(�x��).mp3");
	m_pSoundMap[STR(CSoundMng::TimeSE::watchEaly)] = LoadSound("Assets/SE/����/�������ԂQ(����).mp3");

	//------�j��--------
	m_pSoundMap[STR(CSoundMng::DestroySE::woodBreak)] = LoadSound("Assets/SE/�j��/�ؔj��.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::wood)] = LoadSound("Assets/SE/�j��/�`���R��.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rockBreak)] = LoadSound("Assets/SE/�j��/�Δj��.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rock)] = LoadSound("Assets/SE/�j��/�Δj��.mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::woodHouseBreak)] = LoadSound("Assets/SE/�j��/���z���j��(��).mp3");
	m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouseBreak)] = LoadSound("Assets/SE/�j��/�S�j��.mp3");
	//------������------
	m_pSoundMap[STR(CSoundMng::ShopSE::buy)] = LoadSound("Assets/SE/������/���W��.mp3");
	m_pSoundMap[STR(CSoundMng::ShopSE::text)] = LoadSound("Assets/SE/������/�e�L�X�g.mp3");

	//------�M�~�b�N----
	m_pSoundMap[STR(CSoundMng::GimmickSE::cookie)] = LoadSound("Assets/SE/�M�~�b�N/�N�b�L�[.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::cookieBreak)] = LoadSound("Assets/SE/�M�~�b�N/�N�b�L�[�j��.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::fire)] = LoadSound("Assets/SE/�M�~�b�N/����.mp3");
	m_pSoundMap[STR(CSoundMng::GimmickSE::aokinoko)] = LoadSound("Assets/SE/�M�~�b�N/�A�I�L�m�R.mp3");

}

// ========== �f�X�g���N�^ ==========
CSoundMng::~CSoundMng()
{
	// =-=-= ��� =-=-=
	// ----- ����map -----
	for (auto it = m_pSoundMap.begin(); it != m_pSoundMap.end();) {	// �S�T�E���h�f�[�^�����
		//delete it->second->pAudioData;						// �T�E���h�f�[�^����� Sound.h������Ă����̂ŏȗ�
		it = m_pSoundMap.erase(it);								// �|�C���^���J��
	}

	// ----- �X�s�[�J�[list -----
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();) {	// �S�X�s�[�J�[�f�[�^�����
		if ((*it)) {
			(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
			(*it)->m_Speaker->DestroyVoice();				// ����j��
			delete (*it);									// �K�v�H�s�v�H�H���ꏑ���ƎQ�ƃG���[�o��B	Destroy�œ��I�f�[�^�����Ă�H
			it = m_pSpeakerList.erase(it);				// �|�C���^���J��
		}
	}
}


// ========== �Đ��I���X�s�[�J�[�j�� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Đ����I�����SE�X�s�[�J�[��j������
// ==========================================
void CSoundMng::DeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// �S�Ă�SE�X�s�[�J�[���݂�
	{
		XAUDIO2_VOICE_STATE state{ 0 };
		(*it)->m_Speaker->GetState(&state);					// �Đ��󋵎擾
		if (state.BuffersQueued == 0)						// �Đ����I����Ă�����j��
		{
			// ----- �X�s�[�J�[�폜 -----
			(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
			(*it)->m_Speaker->DestroyVoice();				// ����j��
			delete (*it);									// �X�s�[�J�[�\���̂̎��̉��
			it = m_pSpeakerList.erase(it);				// �|�C���^���J��
		}
		else
		{
			it++;								// ���̗v�f��
		}
	}
}

// ========== �Đ����X�s�[�J�[�S�j�� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Đ����̑S�ẴX�s�[�J�[��j������
// ==========================================
void CSoundMng::AllDeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// �S�Ă�SE�X�s�[�J�[���݂�
	{
		// ----- �X�s�[�J�[�폜 -----
		(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
		(*it)->m_Speaker->DestroyVoice();				// ����j��
		delete (*it);									// �X�s�[�J�[�\���̂̎��̉��
		it = m_pSpeakerList.erase(it);					// �|�C���^���J��
	}
}

// ========== BGM�Đ� ==========
// ���@���F
// BGM �炵����BGM�ԍ�
// �߂�l�F�Ȃ�
// �w���BGM��炷
// =====================================
void CSoundMng::playSound(BGM kind)
{
	switch (kind)
	{
	case CSoundMng::BGM::title:	// �^�C�g��BGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case CSoundMng::BGM::game:	// �e�L�X�g�\��(�v���v��)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case CSoundMng::BGM::game2:	// �Q�[��2
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game2)]), SpeakerKind::bGame2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM2_BGM_VOL);
		break;
	case CSoundMng::BGM::game3:	// �Q�[��3
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game3)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM3_BGM_VOL);
		break;
	case CSoundMng::BGM::Select:	// �X�e�[�W�Z���N�g
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Select)]), SpeakerKind::bSelect });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_BGM_VOL);
		break;
	case CSoundMng::BGM::Op:	// �I�[�v�j���O
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Op)]), SpeakerKind::bOp });
		m_pSpeakerList.back()->m_Speaker->SetVolume(OP_BGM_VOL);
		break;
	case CSoundMng::BGM::Ed:	// �G���f�B���O
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::Ed)]), SpeakerKind::bEd });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ED_BGM_VOL);
		break;
	}
}

// ========== �V�X�e��SE�Đ� ==========
// ���@���F
// SystemSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃V�X�e��SE��炷
// ===================================
void CSoundMng::playSound(SystemSE kind)
{
	switch (kind)
	{
	case CSoundMng::decision:	// ����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::decision)]), SpeakerKind::sDecision });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
		break;
	case CSoundMng::cancel:		// �L�����Z��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::cancel)]), SpeakerKind::sCancel });
		m_pSpeakerList.back()->m_Speaker->SetVolume(CANCEL_VOL);
		break;
	case CSoundMng::select:		// �I��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::select)]), SpeakerKind::sSelect });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);
		break;
	case CSoundMng::Tstrat:		// �Q�[���J�n
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)]), SpeakerKind::sTStrat });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);
		break;
	case CSoundMng::swap:		// �X�e�[�W�`�F���W
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::swap)]), SpeakerKind::sSwap });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SWAP_VOL);
	case CSoundMng::Fpon:		// ���U���g
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Fpon)]), SpeakerKind::sFpon });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RPON_VOL);
		break;
		break;
	}
}

// ========== �v���C���[SE�Đ� ==========
// ���@���F
// PlayerSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃v���C���[SE��炷
// =====================================
void CSoundMng::playSound(PlayerSE kind)
{
	switch (kind)
	{
	case CSoundMng::walkGrass:	// ���F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkGrass)]), SpeakerKind::sWalkGrass });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_GRASS_VOL);
		break;
	case CSoundMng::ranGrass:	// ���F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::ranGrass)]), SpeakerKind::sRanGrass });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_GRASS_VOL);
		break;
	case CSoundMng::walkGround:	// �y�F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkGround)]), SpeakerKind::sWalkGround });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_GROUND_VOL);
		break;
	case CSoundMng::ranGround:	// �y�F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::ranGround)]), SpeakerKind::sRanGround });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_GROUND_VOL);
		break;
	case CSoundMng::walkCream:	// �N���[���F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkCream)]), SpeakerKind::sWalkCream });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_CREAM_VOL);
		break;
	case CSoundMng::runCream:	//	�N���[���F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::runCream)]), SpeakerKind::sRunCream });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_CREAM_VOL);
		break;
	case CSoundMng::walkSponge:	// �X�|���W�F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::walkSponge)]), SpeakerKind::sWalkSponge });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WALK_SPONGE_VOL);
		break;
	case CSoundMng::runSponge:	// �X�|���W�F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::PlayerSE::runSponge)]), SpeakerKind::sRunSponge });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RAN_SPONGE_VOL);
		break;
	}
}

// ========== ���U���gSE�Đ� ==========
// ���@���F
// ResultSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃��U���gSE��炷
// =====================================
void CSoundMng::playSound(ResultSE kind)
{
	switch (kind)
	{
	case CSoundMng::gameOver:	// �Q�[���I�[�o�[
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::gameOver)]), SpeakerKind::sGameOver });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAMEOVER_VOL);
		break;
	case CSoundMng::gameClear:	// �Q�[���N���A
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::gameClear)]), SpeakerKind::sGameClear });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAMECLEAR_VOL);
		break;
	case CSoundMng::stamp:		// �n���R
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::stamp)]), SpeakerKind::sStamp });
		m_pSpeakerList.back()->m_Speaker->SetVolume(STAMP_VOL);
		break;
	case CSoundMng::star:		// ��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ResultSE::star)]), SpeakerKind::sStar });
		m_pSpeakerList.back()->m_Speaker->SetVolume(STAR_VOL);
		break;
	}
}

// ========== �z������SE�Đ� ==========
// ���@���F
// SuctionSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̋z������SE��炷
// =====================================
void CSoundMng::playSound(SuctionSE kind)
{
	switch (kind)
	{
	case CSoundMng::wind:		// �z�����ݒ�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind)]), SpeakerKind::sWind });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND_VOL);
		break;
	case CSoundMng::wind2:		// �z�����ݒ�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind2)]), SpeakerKind::sWind2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND2_VOL);
		break;
	case CSoundMng::wind3:		// �z�����ݒ�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::wind3)]), SpeakerKind::sWind3 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WIND3_VOL);
		break;
	case CSoundMng::suctionHigh:// �z�����݊����F������
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::suctionHigh)]), SpeakerKind::sSuctionHigh });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SUCTION_HIGH_VOL);
		break;
	case CSoundMng::suctionLow:	// �z�����݊����F�Ⴂ��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::suctionLow)]), SpeakerKind::sSuctionLow });
		m_pSpeakerList.back()->m_Speaker->SetVolume(SUCTION_LOW_VOL);
		break;
	case CSoundMng::money:		// �����l��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SuctionSE::money)]), SpeakerKind::sMoney });
		m_pSpeakerList.back()->m_Speaker->SetVolume(MONEY_VOL);
		break;
	}
}

// ========== ����SE�Đ� ==========
// ���@���F
// TimeSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̎���SE��炷
// =====================================
void CSoundMng::playSound(TimeSE kind)
{
	switch (kind)
	{
	case CSoundMng::countDown1:	// �J�E���g�_�E���P
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown1)]), SpeakerKind::sCountDown1 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_1_VOL);
		break;
	case CSoundMng::countDown1_pi:	// �J�E���g�_�E���P�E�ҁ[
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown1_pi)]), SpeakerKind::sCountDown1_pi });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_1_PI_VOL);
		break;
	case CSoundMng::countDown2:	// �J�E���g�_�E���Q
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::countDown2)]), SpeakerKind::sCountDown2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COUNTDOWN_2_VOL);
		break;
	case CSoundMng::timeUp1:	// ���Ԑ؂�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::timeUp1)]), SpeakerKind::sTimeUp1 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIMEUP_1_VOL);
		break;
	case CSoundMng::timeUp2:	// �P�O�O�ρ[�B���i�x���j
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::timeUp2)]), SpeakerKind::sTimeUp2 });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIMEUP_2_VOL);
		break;
	case CSoundMng::watchSlow:	// �b�j�F�x��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::watchSlow)]), SpeakerKind::sWatchSlow });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WATCH_SLOW_VOL);
		break;
	case CSoundMng::watchEaly:	// �b�j�F����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::TimeSE::watchEaly)]), SpeakerKind::sWatchEaly });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WATCH_EALY_VOL);
		break;
	}
}

// ========== �j��SE�Đ� ==========
// ���@���F
// DestroySE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̔j��SE��炷
// =====================================
void CSoundMng::playSound(DestroySE kind)
{
	switch (kind)
	{
	case CSoundMng::wood:			// �ؔj��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::wood)]), SpeakerKind::sWood });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_VOL);
		break;
	case CSoundMng::woodBreak:		// �ؔj�󊮗�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodBreak)]), SpeakerKind::sWoodBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_BREAK_VOL);
		break;
	case CSoundMng::rock:			// ��j��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rock)]), SpeakerKind::sRock });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_VOL);
		break;
	case CSoundMng::rockBreak:		// ��j�󊮗�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rockBreak)]), SpeakerKind::sRockBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_BREAK_VOL);
		break;
	case CSoundMng::woodHouse:		// �ؐ��̉Ɣj��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodHouse)]), SpeakerKind::sWoodHouse });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_HOUSE_VOL);
		break;
	case CSoundMng::woodHouseBreak:	// �ؐ��̉Ɣj�󊮗�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::woodHouseBreak)]), SpeakerKind::sWoodHouseBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(WOOD_HOUSE_BREAK_VOL);
		break;
	case CSoundMng::rocklHouse:		// �ΐ��̉Ɣj��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouse)]), SpeakerKind::sRocklHouse });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_HOUSE_VOL);
		break;
	case CSoundMng::rocklHouseBreak:// �ΐ��̉Ɣj�󊮗�
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::DestroySE::rocklHouseBreak)]), SpeakerKind::sRocklHouseBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(ROCK_HOUSE_BREAK_VOL);
		break;
	}
}

// ========== ������SE�Đ� ==========
// ���@���F
// ShopSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̔�����SE��炷
// =====================================
void CSoundMng::playSound(ShopSE kind)
{
	switch (kind)
	{
	case CSoundMng::buy:		// �w��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ShopSE::buy)]), SpeakerKind::sBuy });
		m_pSpeakerList.back()->m_Speaker->SetVolume(BUY_VOL);
		break;
	case CSoundMng::text:		// �e�L�X�g�\��(�v���v��)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::ShopSE::text)]), SpeakerKind::sText });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TEXT_VOL);
		break;
	}
}
// ========== �M�~�b�NSE�Đ� ==========
// ���@���F
// ShopSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃M�~�b�NSE��炷
// =====================================
void CSoundMng::playSound(GimmickSE kind)
{
	switch (kind)
	{
	case CSoundMng::cookie:		// �w��
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::cookie)]), SpeakerKind::sCookie });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COOKIE_VOL);
		break;
	case CSoundMng::cookieBreak:		// �e�L�X�g�\��(�v���v��)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::cookieBreak)]), SpeakerKind::sCookieBreak });
		m_pSpeakerList.back()->m_Speaker->SetVolume(COOKIEBREAK_VOL);
		break;
	case CSoundMng::fire:		// �e�L�X�g�\��(�v���v��)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::fire)]), SpeakerKind::sFire });
		m_pSpeakerList.back()->m_Speaker->SetVolume(FIRE_VOL);
		break;
	case CSoundMng::aokinoko:		// �e�L�X�g�\��(�v���v��)
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GimmickSE::aokinoko)]), SpeakerKind::sAokinoko });
		m_pSpeakerList.back()->m_Speaker->SetVolume(AOKINOKO_VOL);
		break;
	}
}

// ========== BGM�Đ��`�F�b�N ===============
// ���@���F
// BGM ���ׂ���BGM�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w���BGM���Đ������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(BGM kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if (pSpeaker->m_Kind == bTitle) return false;
			break;
		case CSoundMng::BGM::game:
			if (pSpeaker->m_Kind == bGame) return false;
			break;
		case CSoundMng::BGM::game2:
			if (pSpeaker->m_Kind == bGame2) return false;
			break;
		case CSoundMng::BGM::game3:
			if (pSpeaker->m_Kind == bGame3) return false;
			break;
		case CSoundMng::BGM::Select:
			if (pSpeaker->m_Kind == bSelect) return false;
			break;
		case CSoundMng::BGM::Op:
			if (pSpeaker->m_Kind == bOp) return false;
			break;
		case CSoundMng::BGM::Ed:
			if (pSpeaker->m_Kind == bEd) return false;
			break;
		}
	}

	return true;
}


// ========== �V�X�e��SE�Đ��I���`�F�b�N ===============
// ���@���F
// SystemSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̃V�X�e��SE���Đ��I���������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(SystemSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::SystemSE::decision:
			if (pSpeaker->m_Kind == sDecision) return false;
			break;
		case CSoundMng::SystemSE::cancel:
			if (pSpeaker->m_Kind == sCancel) return false;
			break;
		case CSoundMng::SystemSE::select:
			if (pSpeaker->m_Kind == sSelect) return false;
			break;
		case CSoundMng::SystemSE::swap:
			if (pSpeaker->m_Kind == sSwap) return false;
			break;
		case CSoundMng::SystemSE::Fpon:
			if (pSpeaker->m_Kind == sFpon) return false;
			break;
		}
	}

	return true;
}

// ========== �v���C���[SE�Đ��I���`�F�b�N ===============
// ���@���F
// PlayerSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̃v���C���[SE���Đ��I���������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(PlayerSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::PlayerSE::walkGrass:
			if (pSpeaker->m_Kind == sWalkGrass) return false;
			break;
		case CSoundMng::PlayerSE::ranGrass:
			if (pSpeaker->m_Kind == sRanGrass) return false;
			break;
		case CSoundMng::PlayerSE::walkGround:
			if (pSpeaker->m_Kind == sWalkGround) return false;
			break;
		case CSoundMng::PlayerSE::ranGround:
			if (pSpeaker->m_Kind == sRanGround) return false;
			break;
		case CSoundMng::PlayerSE::walkCream:
			if (pSpeaker->m_Kind == sWalkCream) return false;
			break;
		case CSoundMng::PlayerSE::runCream:
			if (pSpeaker->m_Kind == sRunCream) return false;
			break;
		case CSoundMng::PlayerSE::walkSponge:
			if (pSpeaker->m_Kind == sWalkSponge) return false;
			break;
		case CSoundMng::PlayerSE::runSponge:
			if (pSpeaker->m_Kind == sRunSponge) return false;
			break;
		}
	}

	return true;
}



// ========== �z�����ݍĐ��I���`�F�b�N ===============
// ���@���F
// SuctionSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̋z������SE���Đ��I���������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(SuctionSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::SuctionSE::wind:
			if (pSpeaker->m_Kind == sWind) return false;
			break;
		case CSoundMng::SuctionSE::wind2:
			if (pSpeaker->m_Kind == sWind2) return false;
			break;
		case CSoundMng::SuctionSE::wind3:
			if (pSpeaker->m_Kind == sWind3) return false;
			break;
		}
	}

	return true;
}

// ========== ���ԍĐ��I���`�F�b�N ===============
// ���@���F
// TimeSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̎���SE���Đ��I���������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(TimeSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::TimeSE::countDown1:
			if (pSpeaker->m_Kind == sCountDown1) return false;
			break;
		case CSoundMng::TimeSE::countDown1_pi:
			if (pSpeaker->m_Kind == sCountDown1_pi) return false;
			break;
		case CSoundMng::TimeSE::countDown2:
			if (pSpeaker->m_Kind == sCountDown2) return false;
			break;
		case CSoundMng::TimeSE::timeUp1:
			if (pSpeaker->m_Kind == sTimeUp1) return false;
			break;
		case CSoundMng::TimeSE::timeUp2:
			if (pSpeaker->m_Kind == sTimeUp2) return false;
			break;
		}
	}

	return true;
}
// ========== ���ԍĐ��I���`�F�b�N ===============
// ���@���F
// TimeSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̎���SE���Đ��I���������`�F�b�N
// ==========================================
bool CSoundMng::CheckSoundEnd(ShopSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::ShopSE::buy:
			if (pSpeaker->m_Kind == sBuy) return false;
			break;
		case CSoundMng::ShopSE::text:
			if (pSpeaker->m_Kind == sText) return false;
			break;
		}
	}

	return true;
}

bool CSoundMng::CheckSoundEnd(GimmickSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case CSoundMng::GimmickSE::cookie:
			if (pSpeaker->m_Kind == sCookie) return false;
			break;
		case CSoundMng::GimmickSE::cookieBreak:
			if (pSpeaker->m_Kind == sCookieBreak) return false;
			break;
		case CSoundMng::GimmickSE::fire:
			if (pSpeaker->m_Kind == sFire) return false;
			break;
		case CSoundMng::GimmickSE::aokinoko:
			if (pSpeaker->m_Kind == sAokinoko) return false;
			break;
		}
	}

	return true;
}

// ========== BGM�Đ���~ ==========
// ���@���F
// BGM ��~������BGM�ԍ�
// �߂�l�F�Ȃ�
// �w���BGM�̍Đ����~���A�X�s�[�J�[��j������
// ==========================================
void CSoundMng::StopSound(BGM kind)
{
	bool flg = false;	// �Đ���

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// �S�Đ���SE�̒�����w���SE��T��
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if ((*it)->m_Kind == bTitle) flg = true;
			break;
		case CSoundMng::BGM::game:
			if ((*it)->m_Kind == bGame) flg = true;
			break;
		case CSoundMng::BGM::game2:
			if ((*it)->m_Kind == bGame2) flg = true;
			break;
		case CSoundMng::BGM::game3:
			if ((*it)->m_Kind == bGame3) flg = true;
			break;
		case CSoundMng::BGM::Select:
			if ((*it)->m_Kind == bSelect) flg = true;
			break;
		}

		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

void CSoundMng::StopSound(SystemSE kind)
{
	bool flg = false;	// �Đ���
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		switch (kind)
		{
		case CSoundMng::SystemSE::Fpon:
			if ((*it)->m_Kind == sFpon) flg = true;
			break;
		}
		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
// ========== �v���C���[SE�Đ���~ ==========
// ���@���F
// PlayerSE ��~������
// �߂�l�F�Ȃ�
// �w��̃V�X�e��SE�̍Đ����~���A�X�s�[�J�[��j������
// ==========================================
void CSoundMng::StopSound(PlayerSE kind)
{
	bool flg = false;	// �Đ���
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		switch (kind)
		{
		case CSoundMng::PlayerSE::walkGrass:
			if ((*it)->m_Kind == sWalkGrass) flg = true;
			break;
		case CSoundMng::PlayerSE::ranGrass:
			if ((*it)->m_Kind == sRanGrass) flg = true;
			break;
		case CSoundMng::PlayerSE::walkGround:
			if ((*it)->m_Kind == sWalkGround) flg = true;
			break;
		case CSoundMng::PlayerSE::ranGround:
			if ((*it)->m_Kind == sRanGround) flg = true;
			break;
		case CSoundMng::PlayerSE::walkCream:
			if ((*it)->m_Kind == sWalkCream) flg = true;
			break;
		case CSoundMng::PlayerSE::runCream:
			if ((*it)->m_Kind == sRunCream) flg = true;
			break;
		case CSoundMng::PlayerSE::walkSponge:
			if ((*it)->m_Kind == sWalkSponge) flg = true;
			break;
		case CSoundMng::PlayerSE::runSponge:
			if ((*it)->m_Kind == sRunSponge) flg = true;
			break;
		}

		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

// ========== �z������SE�Đ���~ ==========
// ���@���F
// SuctionSE ��~������
// �߂�l�F�Ȃ�
// �w��̋z������SE�̍Đ����~���A�X�s�[�J�[��j������
// ==========================================
void CSoundMng::StopSound(SuctionSE kind)
{
	bool flg = false;	// �Đ���

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// �S�Đ���SE�̒�����w���SE��T��
	{
		switch (kind)
		{
		case CSoundMng::SuctionSE::wind:
			if ((*it)->m_Kind == sWind) flg = true;
			break;
		case CSoundMng::SuctionSE::wind2:
				if ((*it)->m_Kind == sWind2) flg = true;
				break;
		case CSoundMng::SuctionSE::wind3:
				if ((*it)->m_Kind == sWind3) flg = true;
				break;


		}

		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
	
}

void CSoundMng::StopSound(ShopSE kind)
{
	bool flg = false;	// �Đ���

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// �S�Đ���SE�̒�����w���SE��T��
	{
		switch (kind)
		{
		case CSoundMng::ShopSE::text:
			if ((*it)->m_Kind == sWind) flg = true;
			break;
		}

		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
