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
using namespace std;

// ========== �N���X ==========
class CSoundMng
{
public:	// �񋓌^ �O���ďo���p
	// =-=-= BGM =-=-=
	enum BGM {
		title,
		game,
		game2,
		game3,
		Select,
		Op,
		Ed
	};

	// =-=-= SE =-=-=
	// ----- �V�X�e���� -----
	enum SystemSE {
		decision,		// ����
		cancel,			// �L�����Z��
		select,			// �I��
		Tstrat,			//�Q�[���J�n(�^�C�g��)
		swap,			//�X�e�[�W�`�F���W
		Fpon,			//���U���gSE
	};

	// ----- �v���C���[ -----
	enum PlayerSE {
		walkGrass,		// ���F����
		ranGrass,		// ���F����
		walkGround,		// �y�F����
		ranGround,		// �y�F����
		walkCream,		//�N���[��:����
		runCream,		//�N���[��:����
		walkSponge,		//�X�|���W:����
		runSponge,		//�X�|���W:����

	};

	// ----- ���U���g -----
	enum ResultSE {
		gameOver,		// �Q�[���I�[�o�[
		gameClear,		// �Q�[���N���A
		stamp,			// �n���R
		star,			// ��
	};

	// ----- �z������ -----
	enum SuctionSE {
		wind,			// �z�����ݒ�
		wind2,			// �z�����ݒ�(��)
		wind3,			// �z�����ݒ�(��)
		suctionHigh,	// �z�����݊���(�|���b)�F������
		suctionLow,		// �z�����݊���(�|���b)�F�Ⴂ��
		money,			// �����`������
	};

	// ----- ���� -----
	enum TimeSE {
		countDown1,		// �ہE�ہE�ρ[�[(2�J�E���g)
		countDown1_pi,	// �ρ[�[
		countDown2,		// �ہE�ہE�ہE�ρ[�[(�R�J�E���g)
		timeUp1,		// ���v������
		timeUp2,		// �x��
		watchSlow,		// �b�j�F�������
		watchEaly,		// �b�j�F����
	};

	// ----- �j�� -----
	enum DestroySE
	{
		wood,			// �ؔj��
		woodBreak,		// �ؔj�󊮗�
		rock,			// ��j��
		rockBreak,		// ��j�󊮗�
		woodHouse,		// �؂̉Ɣj��
		woodHouseBreak,	// �؂̉Ɣj�󊮗�
		rocklHouse,		// �΂̉Ɣj��
		rocklHouseBreak,// �΂̉Ɣj�󊮗�
	};

	// ----- ������ -----
	enum ShopSE
	{
		buy,			// �w������(���W��)
		text,			// �e�L�X�g�̃v���v����
	};

	//------�M�~�b�N------
	enum GimmickSE
	{
		cookie,			//�N�b�L�[
		cookieBreak,	//�N�b�L�[�j��
		fire,			//����
		aokinoko		//�A�I�L�m�R
	};

public:	// �֐�
	CSoundMng();
	~CSoundMng();
	void DeleteSpeaker();							// �Đ��I������SE�X�s�[�J�[���폜
	void AllDeleteSpeaker();						// �Đ����̃X�s�[�J�[��S�폜

	// =-=-= �Đ� =-=-=
	// ----- BGM -----
	void playSound(BGM kind);						// BGM

	// ----- SE -----
	void playSound(SystemSE kind);					// �V�X�e����
	void playSound(PlayerSE kind);					// �v���C���[
	void playSound(ResultSE kind);					// ���U���g
	void playSound(SuctionSE kind);					// �z������
	void playSound(TimeSE kind);					// ����
	void playSound(DestroySE kind);					// �j��
	void playSound(ShopSE kind);					// ������
	void playSound(GimmickSE kind);					// �M�~�b�N

	// =-=-= �Đ��I���`�F�b�N =-=-=
	// ----- BGM -----
	bool CheckSoundEnd(BGM kind);

	// ----- SE -----
	bool CheckSoundEnd(SystemSE kind);				// �V�X�e���w���SE���Đ��I���������`�F�b�N
	bool CheckSoundEnd(PlayerSE kind);				// �v���C���[
	//bool CheckSoundEnd(ResultSE kind);			// ���U���g
	bool CheckSoundEnd(SuctionSE kind);				// �z������
	bool CheckSoundEnd(TimeSE kind);				// ����
	//bool CheckSoundEnd(DestroySE kind);			// �j��
	bool CheckSoundEnd(ShopSE kind);				// ������
	bool CheckSoundEnd(GimmickSE kind);				// �M�~�b�N

	// =-=-= �Đ���~ =-=-=
	// ----- BGM -----
	void StopSound(BGM kind);						// BGM

	// ----- SE -----
	void StopSound(SystemSE kind);				// �V�X�e����SE�Đ���~
	void StopSound(PlayerSE kind);					// �v���C���[
	//void StopSound(ResultSE kind);				// ���U���g
	void StopSound(SuctionSE kind);					// �z������
	//void StopSound(TimeSE kind);					// ����
	//void StopSound(DestroySE kind);				// �j��
	void StopSound(ShopSE kind);					// ������
	//void StopSound(GimmickSE kind);				// �M�~�b�N


private: // �񋓌^�@���������p
	enum SpeakerKind
	{
		bTitle,			// �^�C�g��BGM
		bGame,			// �Q�[��BGM
		bGame2,			// �Q�[��2BGM
		bGame3,			// �Q�[��3BGM
		bSelect,		//�X�e�[�W�Z���N�g
		bOp,
		bEd,
		sDecision,		// ����
		sCancel,		// �L�����Z��
		sSelect,		// �I��
		sTStrat,		//�Q�[���J�n(�^�C�g��)
		sSwap,			//�X�e�[�W�`�F���W
		sFpon,			//���U���gSE
		sWalkGrass,		// ���F����
		sRanGrass,		// ���F����
		sWalkGround,	// �y�F����
		sRanGround,		// �y�F����
		sWalkCream,		// �N���[��:����
		sRunCream,		// �N���[��:����
		sWalkSponge,	// �X�|���W:����
		sRunSponge,		// �X�|���W:����
		sGameOver,		// �Q�[���I�[�o�[
		sGameClear,		// �Q�[���N���A
		sStamp,			// �n���R
		sStar,			// ��
		sWind,			// �z�����ݒ�
		sWind2,			// �z�����ݒ�(��)
		sWind3,			// �z�����ݒ�(��)
		sSuctionHigh,	// �z�����݊���(�|���b)�F������
		sSuctionLow,	// �z�����݊���(�|���b)�F�Ⴂ��
		sMoney,			// �����`������
		sCountDown1,	// �X�^�[�g�J�E���g�_�E���P
		sCountDown1_pi,	// �X�^�[�g�J�E���g�_�E���E�X�^�[�g
		sCountDown2,	// �X�^�[�g�J�E���g�_�E���Q
		sTimeUp1,		// �^�C���A�b�v
		sTimeUp2,		// �x��
		sWatchSlow,		// �b�j�F�������
		sWatchEaly,		// �b�j�F����
		sWood,			// �ؔj��
		sWoodBreak,		// �ؔj�󊮗�
		sRock,			// ��j��
		sRockBreak,		// ��j�󊮗�
		sWoodHouse,		// �؂̉Ɣj��
		sWoodHouseBreak,// �؂̉Ɣj�󊮗�
		sRocklHouse,	// �΂̉Ɣj��
		sRocklHouseBreak,// �΂̉Ɣj�󊮗�
		sBuy,			// �w������(���W��)
		sText,			// �e�L�X�g�̃v���v����
		sCookie,		// �N�b�L�[
		sCookieBreak,	// �N�b�L�[�j��
		sFire,			// ����
		sAokinoko,		// �A�I�L�m�R
	};

	typedef struct		// �X�s�[�J�[
	{
		IXAudio2SourceVoice*	m_Speaker;		// �X�s�[�J�[
		SpeakerKind				m_Kind;				// �X�s�[�J�[�̎��
	}Speaker;

private:

	map<string, XAUDIO2_BUFFER*> m_pSoundMap;		// �����pmap
	list<Speaker*> m_pSpeakerList;					// �X�s�[�J�[�plist
};
#endif // !__SOUND_MANAGER_H__