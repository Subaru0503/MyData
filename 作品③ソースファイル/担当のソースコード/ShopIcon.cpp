// ShopIcon.cpp

//----�C���N���[�h��----
#include "ShopIcon.h"

CShopIcon::CShopIcon(float PosX, float PosY, float PosZ, int AnimNo, int Stage)	// �R���X�g���N�^
{
	ShopIcon.pos = DirectX::XMFLOAT3(PosX, PosY, PosZ);		// ���W�ݒ�
	ShopIcon.size = DirectX::XMFLOAT2(150.0f, 300.0f);		// �T�C�Y�ݒ�
	ShopIcon.Texturesize = DirectX::XMFLOAT2(150.0f, 300.0f);	// �T�C�Y�ݒ�
	if (Stage != 0)
	{
		// �e�N�X�`���T�C�Y�ݒ�
		ShopIcon.sizeTexCoord = DirectX::XMFLOAT2((1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_X),
			(1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_Y));
		// �e�N�X�`�����W�ݒ�
		ShopIcon.posTexCoord = DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x * (AnimNo % ICON_ANIM_SHOP_MENU_SPLIT_X),
			ShopIcon.sizeTexCoord.y * (AnimNo / ICON_ANIM_SHOP_MENU_SPLIT_X));
	}
	else
	{
		// �e�N�X�`���T�C�Y�ݒ�
		ShopIcon.sizeTexCoord = DirectX::XMFLOAT2((1.0f / (float)ICON_ANIM_SHOP_MENU_SPLIT_X),
			(1.0f / (float)SELECT_ICON_ANIM_SHOP_MENU_SPLIT_Y));
		// �e�N�X�`�����W�ݒ�
		ShopIcon.posTexCoord = DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x * (AnimNo % ICON_ANIM_SHOP_MENU_SPLIT_X),
			ShopIcon.sizeTexCoord.y * (AnimNo / ICON_ANIM_SHOP_MENU_SPLIT_X));
	}
	ShopIcon.color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	ShopIcon.pTexture = nullptr;							// �e�N�X�`��������
}

CShopIcon::~CShopIcon()	// �f�X�g���N�^
{
	if (ShopIcon.pTexture)
	{
		delete ShopIcon.pTexture;
		ShopIcon.pTexture = nullptr;
	}
}

void CShopIcon::Update()	// �X�V
{

}

void CShopIcon::Draw()	// �`��
{
	DirectX::XMFLOAT4X4 mat[3];	// �`��ɕK�v�ȏ��

	DirectX::XMMATRIX world;	// ���[���h�s��

	//���[���h�s���X,Y�݂̂��l�����č쐬
	world = DirectX::XMMatrixTranslation(ShopIcon.pos.x, ShopIcon.pos.y, ShopIcon.pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(ICON_LEFT, ICON_RIGHT, ICON_BOTTOM,
		ICON_TOP, ICON_NEAR, ICON_FAR);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	Sprite::SetWorld(mat[0]);											// ���[���h�Z�b�g
	Sprite::SetView(mat[1]);											// �r���[�Z�b�g
	Sprite::SetProjection(mat[2]);										// �v���W�F�N�V�����Z�b�g
	Sprite::SetSize(DirectX::XMFLOAT2(ShopIcon.size.x,					// �T�C�Y�Z�b�g
		-ShopIcon.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(ShopIcon.posTexCoord.x,			// UV���W�Z�b�g
		ShopIcon.posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(ShopIcon.sizeTexCoord.x,		// UV�T�C�Y�Z�b�g
		ShopIcon.sizeTexCoord.y));
	Sprite::SetColor(DirectX::XMFLOAT4(ShopIcon.color));				// �J���[�Z�b�g
	Sprite::SetTexture(ShopIcon.pTexture);								// �e�N�X�`���Z�b�g
	Sprite::Draw();
}

void CShopIcon::SetPos(float PosX, float PosY)
{
	ShopIcon.pos.x = PosX;
	ShopIcon.pos.y = PosY;
}

void CShopIcon::SetSizeRatio(float ratio)
{
	ShopIcon.size.x = ShopIcon.Texturesize.x * ratio;	// �T�C�Y�ݒ�
	ShopIcon.size.y = ShopIcon.Texturesize.y * ratio;	// �T�C�Y�ݒ�
}

void CShopIcon::SetSize(float sizex, float sizey)
{
	ShopIcon.size.x = ShopIcon.Texturesize.x = sizex;	// �T�C�Y�ݒ�
	ShopIcon.size.y = ShopIcon.Texturesize.y = sizey;	// �T�C�Y�ݒ�
}

void CShopIcon::ResetSize()
{
	ShopIcon.size.x = ShopIcon.Texturesize.x;	// �T�C�Y�ݒ� 
	ShopIcon.size.y = ShopIcon.Texturesize.y;	// �T�C�Y�ݒ� 
}

void CShopIcon::SetTexCoord(float Pos, float Size)
{
	// �e�N�X�`���T�C�Y�ݒ�
	ShopIcon.posTexCoord = DirectX::XMFLOAT2(Pos, Pos);
	ShopIcon.sizeTexCoord = DirectX::XMFLOAT2(Size, Size);
}

void CShopIcon::SetColor(float r, float g, float b, float a)
{
	ShopIcon.color.x = r;
	ShopIcon.color.y = g;
	ShopIcon.color.z = b;
	ShopIcon.color.w = a;
}

CShopIcon::ST_SHOP_ICON_PARAM* CShopIcon::GetIcon()
{
	return &ShopIcon;
}
