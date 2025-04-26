#ifndef ___TIMER_H___
#define ___TIMER_H___

#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_TIME			(4)	//�G�t�F�N�g�̐��i�z��̐��j
#define ANIM_TIME_FRAME	(2)		//�A�j���[�V������R�}�t���[����
#define ANIM_TIME_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_TIME_SPLIT_Y	(4)		//�摜�������i�c�j

class CTimer
{
public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		//Float4	color;			//�J���[
		//float	angle;			//��]�p�x
		//bool	use;			//�g�p���t���O
		int		frame;			//�A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_TIME_PARAM;		//�������Ǘ�����p�����[�^�̍\����

public:
	CTimer(int TimeLimit);
	~CTimer();
	void Update();
	void Draw();
	int GetTime();
	void SetItem(int item);		// �A�C�e�����g�p���ꂽ��
	int GetMaxTime();

private:
	//----�A�C�e���g�p�m�F�p----
	int m_nTimer;				// ���ԉ����A�C�e���t���O

	ST_TIME_PARAM m_time[DIGIT_TIME];//�^�C�}�[�i�����j
	ST_TIME_PARAM m_timer;
	unsigned int m_TextureTime;
	int m_nTime;
	int m_nTimeLimit;
	float m_ftemp;//�������ԑޔ�p
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX[2], m_basePosY[2];
	float m_fRadian;
	bool m_bResult;
	Texture* m_pTexture[2];
	int m_nMaxTime;

};





#endif // !___TIMER_H___

