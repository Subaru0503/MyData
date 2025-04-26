// ShopText[0].cpp

//----�C���N���[�h��----
#include "ShopText.h"

//----�萔�E�}�N����`----
#define TEXT_LEFT (0.0f)												// ��ʍ��̍��W
#define TEXT_RIGHT (1280.0f)												// ��ʉE�̍��W
#define TEXT_BOTTOM (720.0f)											// ��ʉ��̍��W
#define TEXT_TOP (0.0f)													// ��ʏ�̍��W
#define TEXT_NEAR (1.0f)												// �J�����̌����n�߂鋗��
#define TEXT_FAR (10.0f)												// �J�����̌����鋗��
#define TEXT_ANIM_SHOP_MENU_SPLIT_X	(1.0f / 19.0f)						//�摜�������i���j
#define SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X	(1.0f / 19.0f)				//�摜�������i���j(�Z���N�g�V���b�v)
#define TEXT_ANIM_SHOP_MENU_SPLIT_Y	(1.0f / 29.0f)						//�摜�������i�c�j
#define SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y	(1.0f / 23.0f)				//�摜�������i�c�j(�Z���N�g�V���b�v)
//#define TEXT_ANIM_SHOP_MENU_SPLIT_Y2 (1.0f / 28.5f)						// �����p
#define TEXT_RATIO (0.02f)												// �e�L�X�g�T�C�Y

CShopText::CShopText(int text, CSoundMng *sound)	// �R���X�g���N�^
	: m_nLineNum(0)
	, m_nLineNumElement(0)
{
	m_nShopText = text;

	for (int i = 0; i < MAX_LINE; i++)
	{
		ShopText[i].pos = DirectX::XMFLOAT3(0.0f, 590.0f + i * 30.0f, 0.0f);	// ���W�ݒ�
		ShopText[i].size = DirectX::XMFLOAT2(0.0f, 60.0f);		// �T�C�Y�ݒ�
		if (!m_nShopText)
		{
			ShopText[i].posTexCoord = DirectX::XMFLOAT2(0.0f, SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// �e�N�X�`�����W�ݒ�
			ShopText[i].sizeTexCoord = DirectX::XMFLOAT2(SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X,
				SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// �e�N�X�`���T�C�Y�ݒ�
		}
		else
		{
			ShopText[i].posTexCoord = DirectX::XMFLOAT2(0.0f, TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// �e�N�X�`�����W�ݒ�
			ShopText[i].sizeTexCoord = DirectX::XMFLOAT2(TEXT_ANIM_SHOP_MENU_SPLIT_X,
				TEXT_ANIM_SHOP_MENU_SPLIT_Y);	// �e�N�X�`���T�C�Y�ݒ�
		}
		ShopText[i].frame = 0;										// �A�j���[�V�����Ǘ��t���[���ݒ�
		ShopText[i].currentAnimNo = -1;								// �A�j���[�V�����R�}�ݒ�
		ShopText[i].textNo = 0;									// �e�L�X�g�i���o�[�ݒ�
		ShopText[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// �J���[�ݒ�
		ShopText[i].pTexture = nullptr;							// �e�N�X�`��������
	}
	m_pSoundMng = sound;
}

CShopText::~CShopText()	// �f�X�g���N�^
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		if (ShopText[i].pTexture)
		{
			delete ShopText[i].pTexture;
			ShopText[i].pTexture = nullptr;
		}
	}
}

void CShopText::Update()	// �X�V
{
	//---- �A�j���[�V����----
	//---- �R�}�v�Z----
	ShopText[m_nLineNumElement].posTexCoord.x = 0.0f;
	if (!m_nShopText)
	{
		ShopText[m_nLineNumElement].posTexCoord.y = SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_Y * (float)(ShopText[m_nLineNumElement].textNo - 1);
		ShopText[m_nLineNumElement].sizeTexCoord.x = SELECT_TEXT_ANIM_SHOP_MENU_SPLIT_X * (float)ShopText[m_nLineNumElement].currentAnimNo;
	}
	else
	{
		ShopText[m_nLineNumElement].posTexCoord.y = TEXT_ANIM_SHOP_MENU_SPLIT_Y * (float)(ShopText[m_nLineNumElement].textNo - 1);
		ShopText[m_nLineNumElement].sizeTexCoord.x = TEXT_ANIM_SHOP_MENU_SPLIT_X * (float)ShopText[m_nLineNumElement].currentAnimNo;
	}
	ShopText[m_nLineNumElement].size.x = 28.0f * (float)ShopText[m_nLineNumElement].currentAnimNo;
	ShopText[m_nLineNumElement].pos.x = 715 + 14.0f * (float)ShopText[m_nLineNumElement].currentAnimNo;

	if (ShopText[m_nLineNumElement].frame >= 7)
	{
		ShopText[m_nLineNumElement].frame = 0;
		ShopText[m_nLineNumElement].currentAnimNo++;
		//m_pSoundMng->playSound(CSoundMng::ShopSE::text);//�e�L�X�gse

	}

	// �������o����܂�(�Q�[�����V���b�v)
	if (m_nShopText && (ShopText[m_nLineNumElement].currentAnimNo < 19 || ShopText[m_nLineNumElement].textNo - 1 == 5))
	{
		ShopText[m_nLineNumElement].frame++;
	}
	// �������ł���܂�(�Z���N�g�V���b�v)
	else if (!m_nShopText && ShopText[m_nLineNumElement].currentAnimNo <= 18)
	{
		ShopText[m_nLineNumElement].frame++;
	}
	else if (!m_nShopText && (ShopText[m_nLineNumElement].textNo - 1 == 6 || ShopText[m_nLineNumElement].textNo - 1 == 9 || ShopText[m_nLineNumElement].textNo - 1 == 14))
	{
		ShopText[m_nLineNumElement].frame++;
	}
}

void CShopText::Draw()	// �`��
{
	for (int i = 0; i < MAX_LINE; i++)
	{
		// �A�j���[�V�����R�}�ԍ���0��菬�����Ȃ����
		if (ShopText[i].currentAnimNo < 0) return;

		if (ShopText[i].textNo)
		{
			DirectX::XMFLOAT4X4 mat[3];	// �`��ɕK�v�ȏ��

			DirectX::XMMATRIX world;	// ���[���h�s��

			//���[���h�s���X,Y�݂̂��l�����č쐬
			world = DirectX::XMMatrixTranslation(ShopText[i].pos.x, ShopText[i].pos.y, ShopText[i].pos.z);
			DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

			//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
			DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

			//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
			//���̍s���2d�X�N���[���̑傫�������܂�
			DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(TEXT_LEFT, TEXT_RIGHT, TEXT_BOTTOM,
				TEXT_TOP, TEXT_NEAR, TEXT_FAR);
			DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

			Sprite::SetWorld(mat[0]);											// ���[���h�Z�b�g
			Sprite::SetView(mat[1]);											// �r���[�Z�b�g
			Sprite::SetProjection(mat[2]);										// �v���W�F�N�V�����Z�b�g
			Sprite::SetSize(DirectX::XMFLOAT2(ShopText[i].size.x,					// �T�C�Y�Z�b�g
				-ShopText[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(ShopText[i].posTexCoord.x,			// UV���W�Z�b�g
				ShopText[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(ShopText[i].sizeTexCoord.x,		// UV�T�C�Y�Z�b�g
				ShopText[i].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(ShopText[i].color));				// �J���[�Z�b�g
			Sprite::SetTexture(ShopText[0].pTexture);								// �e�N�X�`���Z�b�g
			Sprite::Draw();
		}
	}
}

void CShopText::SetSize(float sizex, float sizey)
{
	for (int i = 0; i < 3; i++)
	{
		ShopText[i].size.x = sizex * TEXT_RATIO;	// �T�C�Y�ݒ�
		ShopText[i].size.y = sizey * TEXT_RATIO;	// �T�C�Y�ݒ�
	}
}

void CShopText::SetColor(float r, float g, float b, float a)
{
	for (int i = 0; i < 3; i++)
	{
		ShopText[i].color.x = r;
		ShopText[i].color.y = g;
		ShopText[i].color.z = b;
		ShopText[i].color.w = a;
	}
}

void CShopText::SetTextNo(int next, int element, int line)				// �e�L�X�g�i���o�[�Z�b�g
{
	m_nLineNum = line;	// ���s�ڂ��i�[
	m_nLineNumElement = element - 1;	// ���s�ڂ��i�[(�z��p)
	ShopText[element - 1].textNo = next;
	ShopText[element - 1].currentAnimNo = 0;
	if (element == 1)
	{
		ShopText[1].currentAnimNo = -1;
		ShopText[2].currentAnimNo = -1;
	}
}

CShopText::ST_SHOP_TEXT_PARAM* CShopText::GetText()
{
	return &ShopText[0];
}

void CShopText::SetSound(CSoundMng * sound)
{
	m_pSoundMng = sound;
}

int CShopText::GetTextNo(int No)
{
	return ShopText[No - 1].textNo;
}

int CShopText::GetAnimeNo(int No)
{
	return ShopText[No - 1].currentAnimNo;
}

int CShopText::GetLineNum()
{
	return m_nLineNum;
}
