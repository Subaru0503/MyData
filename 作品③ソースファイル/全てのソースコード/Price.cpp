// Price.cpp

//----�C���N���[�h��----
#include "Price.h"
#include "SceneGame.h"

CPrice::CPrice(float PosX, float PosY, float PosZ, int Price)	// �R���X�g���N�^
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr,nullptr, }
{
	for (int i = 0; i < MAX_PRICE; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	//if (FAILED(m_pTexture[0]->Create("Assets/Texture/UI_numberPerple.png")))
	//{
	//	MessageBox(NULL, "UI_Money.png", "Error", MB_OK);
	//}
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/num.png")))
	{
		MessageBox(NULL, "Price.cpp num.png", "Error", MB_OK);
	}

	for (int i = 0; i < DIGIT_PRICE; ++i)
	{
		m_Price[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.0065
			, m_pTexture[0]->GetHeight() * 0.0065);
		m_Price[i].pos = DirectX::XMFLOAT3(PosX + i * m_Price[i].size.x, PosY, 0.0f);
		m_Price[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_Price[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_PRICE_SPLIT_X, 1.0f / (float)ANIM_PRICE_SPLIT_Y);

		m_Price[i].frame = 0;
		m_Price[i].currentAnimNo = 0;
	}



	m_nPrice = Price;

	UpdatePricetexCoord();	// �`�悷�鐔���ݒ�
}

CPrice::~CPrice()	// �f�X�g���N�^
{
	for (int i = 0; i < MAX_PRICE; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CPrice::Update()	// �X�V
{

}

void CPrice::Draw()	// �����`��
{
	DirectX::XMFLOAT4X4 mat[3][DIGIT_PRICE];

	DirectX::XMMATRIX world[DIGIT_PRICE];

	for (int i = 0; i < DIGIT_PRICE; ++i)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬

		world[i] = DirectX::XMMatrixTranslation(m_Price[i].pos.x - (i * 5.0f), m_Price[i].pos.y, m_Price[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�


	for (int i = 0; i < DIGIT_PRICE; ++i)
	{
		if (m_Price[0].currentAnimNo == 0 && m_Price[1].currentAnimNo == 0)
		{
			Sprite::SetWorld(mat[0][i + 2]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_Price[i + 2].size.x, -m_Price[i + 2].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_Price[i + 2].posTexCoord.x, m_Price[i + 2].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_Price[i + 2].sizeTexCoord.x, m_Price[i + 2].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(m_Price[i].color));				// �J���[�Z�b�g
			Sprite::SetTexture(m_pTexture[0]);
			Sprite::Draw();
		}
		else if (m_Price[0].currentAnimNo == 0)
		{
			Sprite::SetWorld(mat[0][i + 1]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_Price[i + 1].size.x, -m_Price[i + 1].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_Price[i + 1].posTexCoord.x, m_Price[i + 1].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_Price[i + 1].sizeTexCoord.x, m_Price[i + 1].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(m_Price[i].color));				// �J���[�Z�b�g
			Sprite::SetTexture(m_pTexture[0]);
			Sprite::Draw();
		}
		else
		{
			Sprite::SetWorld(mat[0][i]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_Price[i].size.x, -m_Price[i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_Price[i].posTexCoord.x, m_Price[i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_Price[i].sizeTexCoord.x, m_Price[i].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(m_Price[i].color));				// �J���[�Z�b�g
			Sprite::SetTexture(m_pTexture[0]);
			Sprite::Draw();
		}

	}


}

void CPrice::UpdatePricetexCoord()	// �`�悷�鐔���ݒ�
{
	int temp = m_nPrice;

	for (int i = DIGIT_PRICE - 1; 0 <= i; --i)
	{
		//temp = m_nPrice;
		m_Price[i].currentAnimNo = temp % 10;

		m_Price[i].posTexCoord.x = m_Price[i].sizeTexCoord.x * (m_Price[i].currentAnimNo % ANIM_PRICE_SPLIT_X);
		m_Price[i].posTexCoord.y = m_Price[i].sizeTexCoord.y * (m_Price[i].currentAnimNo / ANIM_PRICE_SPLIT_X);

		//m_BLUCKPrice[i].currentAnimNo = temp % 10;

		//m_BLUCKPrice[i].posTexCoord.x = m_BLUCKPrice[i].sizeTexCoord.x * (m_BLUCKPrice[i].currentAnimNo % ANIM_PRICE_SPLIT_X);
		//m_BLUCKPrice[i].posTexCoord.y = m_BLUCKPrice[i].sizeTexCoord.y * (m_BLUCKPrice[i].currentAnimNo / ANIM_PRICE_SPLIT_X);
		temp /= 10;
	}
}

void CPrice::SetColor(float r, float g, float b, float a)
{
	for (int i = 0; i < DIGIT_PRICE; ++i)
	{
		m_Price[i].color.x = r;
		m_Price[i].color.y = g;
		m_Price[i].color.z = b;
		m_Price[i].color.w = a;
	}
}

int CPrice::GetPrice()
{
	return m_nPrice;
}

void CPrice::PriceSale(float sale)			// ���i����
{
	m_nPrice *= sale;
	UpdatePricetexCoord();	// �`�悷�鐔���ݒ�
}
