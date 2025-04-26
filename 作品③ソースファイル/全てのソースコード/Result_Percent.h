#ifndef ___RESULT_PERCENT_H___
#define ___RESULT_PERCENT_H___

#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

#define DIGIT_NUMBER (4)
#define ANIM_NUMBER_SPLIT_X	(4)		//�摜�������i���j
#define ANIM_NUMBER_SPLIT_Y	(3)		//�摜������

class ResultPer
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
	}ST_RESULT_PERCENT_PARAM;

public:
	ResultPer(float PosX, float PosY, float PosZ, float radian, int Per);
	~ResultPer();
	void Update(int per);
	void Draw();

private:
	ST_RESULT_PERCENT_PARAM per[DIGIT_NUMBER];
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture;
	int m_nper;
	int m_ntemp;
};



#endif // !___RESULT_PERCENT_H___

