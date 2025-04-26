//=================================================================
//
//	SoundManager.cpp
//	�T�E���h���ꌳ�Ǘ�����
//
//=================================================================

//----�C���N���[�h��----
#include "SoundManager.h"

//----�t�@�C���ǂݍ��݂Ɏg�p----
#include <iostream>
#include <fstream>
#include <string>

//----�萔�E�}�N����`-----
// BGM
#define TITLE_BGM_VOL			(0.15f)	// �^�C�g��BGM
#define GAEM_BGM_VOL			(0.15f)	// �Q�[��BGM
#define CLEAR_BGM_VOL			(0.15f)	// �N���ABGM

// SE
#define TSTRAT_VOL				(1.0f)	//�Q�[���J�n(�^�C�g��)
#define GSTRAT_VOL				(1.0f)	//�Q�[���X�^�[�g(�X�e�[�W)
#define PAUSE_VOL				(0.8f)	// �|�[�Y��ʂ��J��
#define PAUSE_CLOSE_VOL			(0.8f)	// �|�[�Y��ʂ����
#define TIME_OVER_VOL			(0.7f)	// ���Ԑ؂�
#define SELECT_VOL				(1.0f)	// �I��
#define DECSION_VOL				(0.5f)	// ����
#define SPIN_VOL				(1.0f)	// �l�W��]��
#define SPIN_MAX_VOL 			(0.4f)	// �l�W�ő�񂵂���

#define STR(var) #var   //�����ɂ����ϐ���ϐ���������������Ƃ��ĕԂ��}�N���֐�

using namespace std;

// �f�X�g���N�^
SoundManager::~SoundManager()
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

	UninitSound();
}


// �Đ��I���X�s�[�J�[�j��
void SoundManager::DeleteSpeaker()
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

// �Đ����X�s�[�J�[�S�j��
void SoundManager::AllDeleteSpeaker()
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

// BGM,SE�ǂݍ���
void SoundManager::SoundLoad()
{
	// BGM�ǂݍ���
	ifstream file("Assets/Sound/BGM/BGM.csv");	// �t�@�C���I�[�v��
	string cell;	// �Z�����Ƃ̓ǂݍ��ݐ�
	int MaxLine;	// �s���i�[�p
	string cellData;	// �Z���f�[�^�i�[�p
	string path;	// �ǂݍ��݃p�X

	if (!file)
	{
		MessageBox(NULL, "BGM.csv�t�@�C�����ǂݍ��߂܂���ł���", "SoundManager.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// �s�����o
	MaxLine = stoi(cell);		// �s���i�[

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// �Z�����o(1���)
		getline(file, cell, ',');	// �Z�����o(2���)

		// �p�X�ݒ�
		path = "Assets/Sound/BGM/" + cell + ".wav";

		if (cell == "Title")
		{
			m_pSoundMap[STR(SoundManager::BGM::Title)] = LoadSound(path.c_str(), true);
		}
		else if (cell == "Stage")
		{
			m_pSoundMap[STR(SoundManager::BGM::Stage)] = LoadSound(path.c_str(), true);
		}
		else if (cell == "Clear")
		{
			m_pSoundMap[STR(SoundManager::BGM::Clear)] = LoadSound(path.c_str(), true);
		}
		getline(file, cell);		// ���̍s��
	}
	file.close();	// �t�@�C�������



	// SE�ǂݍ���
	file.open("Assets/Sound/SE/SE.csv");	// �t�@�C���I�[�v��

	if (!file)
	{
		MessageBox(NULL, "SE.csv�t�@�C�����ǂݍ��߂܂���ł���", "SoundManager.cpp", MB_OK);
		return;
	}

	getline(file, cell, ',');	// �s�����o
	MaxLine = stoi(cell);		// �s���i�[

	// 3�s�ڂ܂ňړ�
	getline(file, cell);
	getline(file, cell);

	// �t�@�C������f�[�^��ǂݍ���
	for (int i = 0; i < MaxLine; i++)
	{
		getline(file, cell, ',');	// �Z�����o(1���)
		getline(file, cell, ',');	// �Z�����o(2���)

		// �p�X�ݒ�
		path = "Assets/Sound/SE/" + cell + ".wav";

		if (cell == "TitleTouch")
		{			
			m_pSoundMap[STR(SoundManager::SystemSE::Tstrat)] = LoadSound(path.c_str());
		}
		else if (cell == "GameStart")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Gstart)] = LoadSound(path.c_str());
		}
		else if (cell == "Pause")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Pause)] = LoadSound(path.c_str());
		}
		else if (cell == "PauseClose")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::PauseClose)] = LoadSound(path.c_str());
		}
		else if (cell == "TimeOver")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::TimeOver)] = LoadSound(path.c_str());
		}
		else if (cell == "Select")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Select)] = LoadSound(path.c_str());
		}
		else if (cell == "Decision")
		{
			m_pSoundMap[STR(SoundManager::SystemSE::Decision)] = LoadSound(path.c_str());
		}
		else if (cell == "ScrewSpin")
		{
			m_pSoundMap[STR(SoundManager::ScrewSE::Spin)] = LoadSound(path.c_str());
		}
		else if (cell == "ScrewMax")
		{
			m_pSoundMap[STR(SoundManager::ScrewSE::SpinMax)] = LoadSound(path.c_str());
		}
		getline(file, cell);		// ���̍s��
	}
	file.close();	// �t�@�C�������
}

// BGM�Đ�
void SoundManager::playSound(BGM kind)
{
	switch (kind)
	{
	case SoundManager::BGM::Title:	// �^�C�g��BGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case SoundManager::BGM::Stage:	// �Q�[��BGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Stage)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case SoundManager::BGM::Clear:	// �N���ABGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::BGM::Clear)]), SpeakerKind::bClear });
		m_pSpeakerList.back()->m_Speaker->SetVolume(CLEAR_BGM_VOL);
		break;
	}
}

// �V�X�e��SE�Đ�
void SoundManager::playSound(SystemSE kind)
{
	switch (kind)
	{
	case SoundManager::SystemSE::Tstrat:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Tstrat)]), SpeakerKind::bTitle });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::Gstart:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Gstart)]), SpeakerKind::bGstart });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(GSTRAT_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::Pause:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Pause)]), SpeakerKind::bPause });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(PAUSE_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::PauseClose:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::PauseClose)]), SpeakerKind::bPauseClose });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(PAUSE_CLOSE_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::TimeOver:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::TimeOver)]), SpeakerKind::bTimeOver });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(TIME_OVER_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::Select:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Select)]), SpeakerKind::bSelect });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);	// ���ʐݒ�
		break;
	case SoundManager::SystemSE::Decision:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::SystemSE::Decision)]), SpeakerKind::bDecision });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// ���ʐݒ�
		break;
	}
}


// �l�WSE�Đ�
void SoundManager::playSound(ScrewSE kind)
{
	switch (kind)
	{
	case SoundManager::ScrewSE::Spin:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::ScrewSE::Spin)]), SpeakerKind::bSpin });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(SPIN_VOL);	// ���ʐݒ�
		break;
	case SoundManager::ScrewSE::SpinMax:
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(SoundManager::ScrewSE::SpinMax)]), SpeakerKind::bSpinMax });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(SPIN_MAX_VOL);	// ���ʐݒ�
		break;
	}
}

// SE���Đ������m�F(�Đ����ĂȂ�������true)
bool SoundManager::CheckSoundEnd(ScrewSE kind)
{
	for (Speaker* pSpeaker : m_pSpeakerList)
	{
		switch (kind)
		{
		case SoundManager::ScrewSE::Spin:
			if (pSpeaker->m_Kind == bSpin) return false;
			break;
		case SoundManager::ScrewSE::SpinMax:
			if (pSpeaker->m_Kind == bSpinMax) return false;
			break;
		}
	}

	return true;
}

// �Đ�����Ă��邩��Ԃ�
//bool SoundManager::GetPlayingState(BGM kind)
//{
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
//	{
//		switch (kind)
//		{
//		case SoundManager::BGM::Clear:
//			if ((*it)->m_Kind == BGM::Clear)
//			{
//				// �Đ���
//				return true;
//			}
//			break;
//		}
//	}
//	// �Đ����ĂȂ�
//	return false;
//}


//bool SoundManager::CheckSoundEnd(GetSE kind)
//{
//	for (Speaker* pSpeaker : m_pSpeakerList)
//	{
//		switch (kind)
//		{
//		case SoundManager::GetSE::fruits:
//			if (pSpeaker->m_Kind == bFruits) return false;
//			break;
//		}
//	}
//
//	return true;
//}


//// ========== BGM�Đ���~ ==========
//// ���@���F
//// BGM ��~������BGM�ԍ�
//// �߂�l�F�Ȃ�
//// �w���BGM�̍Đ����~���A�X�s�[�J�[��j������
//// ==========================================
//void SoundManager::StopSound(BGM kind)
//{
//	bool flg = false;	// �Đ���
//
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// �S�Đ���SE�̒�����w���SE��T��
//	{
//		switch (kind)
//		{
//		case SoundManager::BGM::title:
//			if ((*it)->m_Kind == bTitle) flg = true;
//			break;
//		case SoundManager::BGM::game:
//			if ((*it)->m_Kind == bGame) flg = true;
//			break;
//		case SoundManager::clear:
//			if ((*it)->m_Kind == bClear) flg = true;
//			break;
//		}
//
//		if (flg)	// �Đ����̎w��SE���������炻���j��
//		{
//			(*it)->m_Speaker->Stop();
//			(*it)->m_Speaker->DestroyVoice();
//			delete (*it);
//			m_pSpeakerList.erase(it);
//			break;
//		}
//	}
//}
//
//void SoundManager::StopSound(SystemSE kind)
//{
//	bool flg = false;	// �Đ���
//	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
//	{
//		//switch (kind)
//		//{
//		//case SoundManager::SystemSE::Fpon:
//		//	if ((*it)->m_Kind == sFpon) flg = true;
//		//	break;
//		//}
//		if (flg)	// �Đ����̎w��SE���������炻���j��
//		{
//			(*it)->m_Speaker->Stop();
//			(*it)->m_Speaker->DestroyVoice();
//			delete (*it);
//			m_pSpeakerList.erase(it);
//			break;
//		}
//	}
//}