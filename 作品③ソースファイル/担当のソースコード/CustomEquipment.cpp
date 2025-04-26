// CustomEquipment.cpp

//----�C���N���[�h��----
#include "CustomEquipment.h"
#include "Shop.h"

//----�萔�E�}�N����`----
#define AnimeNo (MAX_CUSTOM)	// �R�}�ԍ�

CCustomEquipment::CCustomEquipment()	// �R���X�g���N�^
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture(nullptr)
	, m_pos{{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f} ,{0.0f, 0.0f, 0.0f} ,{0.0f, 0.0f, 0.0f} }
{
	m_basePosX = 260.0f;
	m_basePosY = 640.0f;

	//----�e�N�X�`���m��----
	m_pTexture = new Texture();

	//----�e�N�X�`���ǂݍ���----
	if (FAILED(m_pTexture->Create("Assets/Texture/Custom.png")))
	{
		MessageBox(NULL, "CustomEquipment Custom.png", "Error", MB_OK);
	}

	//----�ݒ�----
	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		m_Custom[i].size = DirectX::XMFLOAT2(200.0f, 100.0f);
		m_Custom[i].pos = DirectX::XMFLOAT3(m_basePosX + i * 140.0f, m_basePosY, 0.0f);
		m_Custom[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_CUSTOM_EQUIPMENT_SPLIT_X,
			1.0f / (float)ANIM_CUSTOM_EQUIPMENT_SPLIT_Y);
		m_Custom[i].posTexCoord = DirectX::XMFLOAT2(0.0f,
			m_Custom[i].sizeTexCoord.y * (i % ANIM_CUSTOM_EQUIPMENT_SPLIT_Y));
		m_Custom[i].frame = 0;
		m_Custom[i].currentAnimNo = 0;
	}
}

CCustomEquipment::~CCustomEquipment()	// �f�X�g���N�^
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void CCustomEquipment::Update()
{

}

void CCustomEquipment::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][MAX_CUSTOM];

	DirectX::XMMATRIX world[MAX_CUSTOM];

	for (int i = 0; i < MAX_CUSTOM; ++i)
	{
		// �������ĂȂ������玟��
		if (!m_nCustom[i]) continue;

		//----�������Ă���UV���W����----
		switch (m_nCustom[i])
		{
		case 1:	// ���x��1
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (0 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);
			//m_pos[0] =  m_Custom[i].pos;
			break;
		case 2:	// ���x��2
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (1 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);
			break;
		case 3:	// ���x��3
			m_Custom[i].posTexCoord.x = m_Custom[i].sizeTexCoord.x * (2 % ANIM_CUSTOM_EQUIPMENT_SPLIT_X);

			break;
		}
		//���[���h�s���X,Y�݂̂��l�����č쐬

		world[i] = DirectX::XMMatrixTranslation(m_Custom[i].pos.x, m_Custom[i].pos.y, m_Custom[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�
	for (int i = 0; i < MAX_CUSTOM; i++)
	{
		//----�������ĂȂ������玟��----
		if (m_nCustom[i] == 0) continue;

		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_Custom[i].size.x, -m_Custom[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_Custom[i].posTexCoord.x, m_Custom[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_Custom[i].sizeTexCoord.x, m_Custom[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}

}

void CCustomEquipment::SetCustom(int * Custom)
{
	for (int i = 0; i < MAX_CUSTOM; i++)
	{
		m_nCustom[i] = Custom[i];
	}
}