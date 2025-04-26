// ShopIcon.h

//----�C���N���[�h�K�[�h----
#ifndef ___SHOP_ICON_H___
#define ___SHOP_ICON_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define ICON_LEFT (0.0f)												// ��ʍ��̍��W
#define ICON_RIGHT (1280.0f)												// ��ʉE�̍��W
#define ICON_BOTTOM (720.0f)											// ��ʉ��̍��W
#define ICON_TOP (0.0f)													// ��ʏ�̍��W
#define ICON_NEAR (1.0f)												// �J�����̌����n�߂鋗��
#define ICON_FAR (10.0f)												// �J�����̌����鋗��
//#define ICON_ANIM_SHOP_MENU_FRAME	(2)									//�A�j���[�V������R�}�t���[����
#define ICON_ANIM_SHOP_MENU_SPLIT_X	(3)									//�摜�������i���j
#define ICON_ANIM_SHOP_MENU_SPLIT_Y	(6)									//�摜�������i�c�j
#define SELECT_ICON_ANIM_SHOP_MENU_SPLIT_Y (4)							//�摜�������i�c�j

//----�N���X��`----
class CShopIcon
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;										// ���S���W
		DirectX::XMFLOAT2 size;										// ���c�T�C�Y
		DirectX::XMFLOAT2 Texturesize;										// ���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;								// �e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;								// �e�N�X�`���T�C�Y�i�E���j
		DirectX::XMFLOAT4 color;									// �J���[
		Texture* pTexture;											// �e�N�X�`��
	}ST_SHOP_ICON_PARAM;											// �V���b�v�̉�ʂ��Ǘ�����p�����[�^�̍\����

public:
	CShopIcon(float PosX, float PosY, float PosZ, int AnimNo, int Stage);		// �R���X�g���N�^
	~CShopIcon();													// �f�X�g���N�^
	void Update();													// �X�V
	void Draw();													// �`��
	void SetPos(float PosX, float PosY);							// ���W�Z�b�g
	void SetSizeRatio(float ratio);									// �T�C�Y�{���Z�b�g
	void SetSize(float sizex, float sizey);							// �T�C�Y�Z�b�g
	void ResetSize();												// �T�C�Y���Z�b�g
	void SetTexCoord(float Pos, float Size);						// �e�N�X�`���ݒ�
	void SetColor(float r, float g, float b, float a);				// �J���[�ݒ�
	ST_SHOP_ICON_PARAM* GetIcon();									// �A�C�R���p�����[�^�Q�b�g�֐�

private:
	ST_SHOP_ICON_PARAM ShopIcon;
};


#endif // ___SHOP_ICON_H___

