#ifndef ___PROGRESS_H___
#define ___PROGRESS_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
#include "XController.h"
#include "SoundManager.h"

#define MAX_TEXTURE (5)
#define DIGIT_PROGRESS (2)
#define DIGIT_NUMBER (3)
#define DIGIT_STAR (3)
#define ANIM_PROGRESS_SPLIT_X (2)
#define ANIM_PROGRESS_SPLIT_Y (1)
#define ANIM_NUMBER_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_NUMBER_SPLIT_Y	(3)		//�摜������


class CProgress
{
public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j

	}ST_PROGRESS_PARAM;		//�p�����[�^�̍\����


public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j

		int		frame;			//�A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_NUMBER_PARAM;		//�p�����[�^�̍\����

public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y

	}ST_STAR_PARAM;		//�p�����[�^�̍\����
public:
	CProgress(int TotalObjNum, CSoundMng* pSoundMng);
	~CProgress();
	void Update(int SuctionObjNum, int Time, int maxtime);
	void Draw();
	

	void SetSound(CSoundMng*);			// �T�E���h���̎󂯎��

	bool GetEndFlg();
	int  GetProgressNum();				// �B���x�󂯓n��
	int  GetTime();						// �N���A�^�C���󂯓n��

	void SetClear();					// �����I�ɂU�O���B��������

private:
	ST_PROGRESS_PARAM m_progress[DIGIT_PROGRESS];
	ST_NUMBER_PARAM m_number[DIGIT_NUMBER];
	ST_STAR_PARAM m_star[DIGIT_STAR];
	int m_nprogressNum;
	int m_nTotalObj;
	int m_nSuctionObj;
	int m_nTime;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX[4], m_basePosY[4];
	bool m_bGameEnd;
	float m_fsizeTimeUpX, m_fsizeTimeUpY;
	Texture* m_pTexture[MAX_TEXTURE];
	CSoundMng* m_pSoundMng;
	int m_nMAXRatio;
	float m_fRatio;
	DirectX::XMFLOAT2 numsize;
	DirectX::XMFLOAT2 numpos[3];
	DirectX::XMFLOAT2 m_fsizeStar[3];
	int m_nMaxtime;

};




#endif // !___PROGRESS_H___
