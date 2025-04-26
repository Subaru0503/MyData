#ifndef ___RESULT_TIME_H___
#define ___RESULT_TIME_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_TIME (4)
#define ANIM_TIME_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_TIME_SPLIT_Y	(3)		//�摜������

class ResultTime
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
		float radian;
	}ST_RESULT_TIME_PARAM;

public:
	ResultTime(float PosX, float PosY, float PosZ, float radian);
	~ResultTime();
	void Update(int time);
	void Draw();
	void DrawTimeUp();

private:
	ST_RESULT_TIME_PARAM time[DIGIT_TIME];
	int m_ntemp;//�������ԑޔ�p
	int m_nTimeMinutes;
	int m_nTimeSeconds;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture[2];
};


#endif // !___RESULT_TIME_H___

