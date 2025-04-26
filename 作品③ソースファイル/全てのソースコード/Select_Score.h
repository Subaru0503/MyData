#ifndef ___SELECT_SCORE_H___
#define ___SELECT_SCORE_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define ANIM_TIME_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_TIME_SPLIT_Y	(3)		//�摜������

class SelectScore
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_SELECT_TIME_PARAM;

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
		float radian;
	}ST_SELECT_PERCENT_PARAM;
public:
	SelectScore();
	~SelectScore();
	void Update(int* score, int* time, int select);
	void Draw();

private:
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture[4];
	DirectX::XMFLOAT3 m_starPos[3];
	DirectX::XMFLOAT2 m_starSize[3];
	DirectX::XMFLOAT2 m_hyphenPos;
	DirectX::XMFLOAT2 m_hyphenSize;
	ST_SELECT_TIME_PARAM m_time[4];
	ST_SELECT_PERCENT_PARAM m_per[3];
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	int m_cleartime;
	int m_starNum;
	int m_nper;
};




#endif // !___SELECT_SCORE_H___

