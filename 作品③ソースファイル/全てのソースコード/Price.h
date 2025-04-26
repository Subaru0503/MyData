// Price.h

//----�C���N���[�h�K�[�h----
#ifndef ___PRICE_H___
#define ___PRICE_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_PRICE (6)
#define DIGIT_PRICE			(6)			// ���i�̌����i�z��̐��j
#define ANIM_PRICE_SPLIT_X	(4)			// �摜�������i���j
#define ANIM_PRICE_SPLIT_Y	(3)			// �摜�������i�c�j

//----�N���X��`----
class CPrice
{

public:
	typedef struct
	{

		DirectX::XMFLOAT3 pos;			// ���S���W
		DirectX::XMFLOAT2 size;			// ���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	// �e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	// �e�N�X�`���T�C�Y�i�E���j
		int		frame;					// �A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;			// �A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
		DirectX::XMFLOAT4 color;									// �J���[
	}ST_PRICE_PARAM;					// ���i���Ǘ�����p�����[�^�̍\����

public:
	CPrice(float PosX, float PosY, float PosZ, int Price);					// �R���X�g���N�^
	~CPrice();							// �f�X�g���N�^
	void Update();						// �X�V
	void Draw();						// �����`��
	void UpdatePricetexCoord();
	void SetColor(float r, float g, float b, float a);				// �J���[�ݒ�
	int GetPrice();						// ���i���Q�b�g�֐�
	void PriceSale(float sale);			// ���i����

private:
	ST_PRICE_PARAM m_Price[DIGIT_PRICE];
	int m_nPrice;						// ���i
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	Texture* m_pTexture[MAX_PRICE];



};


#endif									 // !___PRICE_H___

