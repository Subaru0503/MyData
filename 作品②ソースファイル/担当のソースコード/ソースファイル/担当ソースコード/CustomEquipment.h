// CustomEquipment

//----�C���N���[�h�K�[�h----
#ifndef ___CUSTOM_EQUIPMENT_H___
#define ___CUSTOM_EQUIPMENT_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Value.h"
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define ANIM_CUSTOM_EQUIPMENT_SPLIT_X	(3)		//�摜�������i���j
#define ANIM_CUSTOM_EQUIPMENT_SPLIT_Y	(6)		//�摜�������i�c�j

//----�萔�E�}�N����`----
class CCustomEquipment
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		frame;			//�A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_CUSTOM_EQUIPMENT_PARAM;		//�p�����[�^�̍\����

public:
	CCustomEquipment();
	~CCustomEquipment();
	void Update();
	void Draw();

	void SetCustom(int* Custom);
private:
	ST_CUSTOM_EQUIPMENT_PARAM m_Custom[MAX_CUSTOM];
	int m_nCustom[MAX_CUSTOM];
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	Texture* m_pTexture;

	DirectX::XMFLOAT3 m_pos[4];

};


#endif // !___CustomEquipment_H___