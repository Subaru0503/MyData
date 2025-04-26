//=================================================================
//
//	SoundManager.h
//	�T�E���h���ꌳ�Ǘ�����
//
//=================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

// ========== �C���N���[�h�� ==========
#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
#include <string>

// ========== �N���X ==========
class SoundManager
{
public:	// �񋓌^ �O���ďo���p
	// BGM���
	enum BGM {
		Title,
		Stage,
		Clear,
	};

	//----SE----
	// �V�X�e����
	enum SystemSE {
		Tstrat,			// �Q�[���J�n(�^�C�g��)
		Gstart,			// �Q�[���X�^�[�g
		Pause,			// �|�[�Y��ʂ��J��
		PauseClose,		// �|�[�Y��ʂ����
		TimeOver,		// ���Ԑ؂�
		Select,			// �I��
		Decision,		// ����
	};

	// �l�W��
	enum ScrewSE {
		Spin,			// �l�W��]
		SpinMax,		// �l�W���ő�܂ŉ񂵂�
	};
public:	// �֐�
	inline static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}
	void DeleteSpeaker();							// �Đ��I������SE�X�s�[�J�[���폜
	void AllDeleteSpeaker();						// �Đ����̃X�s�[�J�[��S�폜

	// BGM,SE�ǂݍ���
	void SoundLoad();

	//----�Đ�----
	// BGM�Đ�
	void playSound(BGM kind);						// BGM

	// SE�Đ�
	void playSound(SystemSE kind);					// �V�X�e����
	void playSound(ScrewSE kind);					// �l�W��
	//----�Đ���~----
	// BGM��~
	//void StopSound(BGM kind);						// BGM

	// SE��~
	//void StopSound(SystemSE kind);				// �V�X�e����SE�Đ���~

	// SE���Đ������m�F
	bool CheckSoundEnd(ScrewSE kind);

private: // �񋓌^�@���������p

	SoundManager()
	{
		InitSound();
	};
	~SoundManager();

	// ���̎��
	enum SpeakerKind
	{
		//----BGM----
		bTitle,			// �^�C�g��
		bGame,			// �Q�[��
		bClear,			// �Q�[���N���A
		//----SE----
		bTstrat,		// �Q�[���J�n(�^�C�g��)
		bGstart,		// �Q�[���X�^�[�g
		bPause,			// �|�[�Y��ʂ��J��
		bPauseClose,	// �|�[�Y��ʂ����
		bTimeOver,		// ���Ԑ؂�
		bSelect,		// �I��
		bDecision,		// ����
		bSpin,			// �l�W��]
		bSpinMax,		// �l�W���ő�܂ŉ񂵂�
	};

	typedef struct		// �X�s�[�J�[
	{
		IXAudio2SourceVoice*	m_Speaker;		// �X�s�[�J�[
		SpeakerKind				m_Kind;			// �X�s�[�J�[�̎��
	}Speaker;

private:

	std::map<std::string, XAUDIO2_BUFFER*> m_pSoundMap;	// �����pmap
	std::list<Speaker*> m_pSpeakerList;					// �X�s�[�J�[�plist
};
#endif // !__SOUND_MANAGER_H__