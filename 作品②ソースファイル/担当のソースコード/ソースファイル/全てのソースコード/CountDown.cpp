//=================================================================
//
//	CountDown.cpp
//	�J�E���g�_�E��UI��`�悷��
//
//=================================================================

#include "CountDown.h"

#define NUM_MAX_SIZE_X		(270.0f)	// �����̃T�C�Y
#define NUM_MAX_SIZE_Y		(250.0f)
#define MOJI_SIZE_RATIO		(0.35f)		// �����̃T�C�Y�{��
#define SIZE_UP_FRAME		(12)		// �e�N�X�`���g�k���x
#define WAIT				(53)		// �g�k���n�܂��Ă��玟�̐������o��܂ł̃t���[����

CCountDown::CCountDown()
	: m_kind(0)
	, m_waitFrame(0)
{
	// �����e�N�X�`���ǂݍ���
	m_Count[0].pTexture = new Texture();
	if (FAILED(m_Count[0].pTexture->Create("Assets/Texture/UI_ResultNumber.png"))) {	// ����
		MessageBox(NULL, "ItemUI UI_ResultNumber.png", "Error", MB_OK);
	}
	// �X�^�[�g�e�N�X�`���ǂݍ���
	m_Count[1].pTexture = new Texture();
	if (FAILED(m_Count[1].pTexture->Create("Assets/Texture/UI_start.png"))) {	// �X�^�[�g
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}
	m_textureSize.x = m_Count[1].pTexture->GetWidth() * MOJI_SIZE_RATIO;	// �e�N�X�`���̖{���̉摜�T�C�Y���擾���A���傤�ǂ����T�C�Y�ɂ���
	m_textureSize.y = m_Count[1].pTexture->GetHeight() * MOJI_SIZE_RATIO;	// �i�c����͂��̂܂܁j

	m_Count[0].AnimeNo = 3;
	m_Count[0].pos = DirectX::XMFLOAT2(640.0f, 360.0f);
	m_Count[0].size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[0].sizeTexCoord = DirectX::XMFLOAT2(1.0f / 4, 1.0f / 3);
	m_Count[0].posTexCoord = DirectX::XMFLOAT2(m_Count[0].sizeTexCoord.x * 2, 0.0f);
	m_Count[0].phase = 0;

	m_Count[1].AnimeNo = 0;
	m_Count[1].pos = DirectX::XMFLOAT2(640.0f, 360.0f);
	m_Count[1].size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[1].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
	m_Count[1].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_Count[1].phase = 0;
}

CCountDown::~CCountDown()
{
	SAFE_DELETE(m_Count[0].pTexture);
	SAFE_DELETE(m_Count[1].pTexture);
}

void CCountDown::Update()
{
	// ----- �J�E���g�_�E�� -----
	if (m_Count[0].AnimeNo > 0) {										// �J�E���g���Ȃ�
		if (m_Count[0].size.x >= NUM_MAX_SIZE_X && m_waitFrame > WAIT) {// �g�債��������
		// ----- �����؂�ւ� -----
			m_Count[0].size = DirectX::XMFLOAT2(0.0f, 0.0f);			// �T�C�Y���ŏ���
			m_Count[0].AnimeNo--;										// ���̐�����
			m_waitFrame = 0;											// �ăJ�E���g
		}
		else if (m_Count[0].size.x < NUM_MAX_SIZE_X) {					// �g�債�����Ă��Ȃ����
		// ----- �e�N�X�`���g�� -----
			float sizeUPx = NUM_MAX_SIZE_X / SIZE_UP_FRAME;	// �g�嗦
			float sizeUPy = NUM_MAX_SIZE_Y / SIZE_UP_FRAME;
			m_Count[0].size = DirectX::XMFLOAT2(m_Count[0].size.x + sizeUPx, m_Count[0].size.y + sizeUPy);
		}
	}
	else {	// �J�E���g���I�������X�^�[�g��\��
		switch (m_Count[1].phase)
		{
		case 0:	// �g��
			m_kind = 1;	// �`����u�����[�Ɓv��
			if (m_Count[1].size.x < m_textureSize.x) {
				float sizeUPx = m_textureSize.x / SIZE_UP_FRAME;		// �g�嗦
				float sizeUPy = m_textureSize.y / SIZE_UP_FRAME;
				m_Count[1].size = DirectX::XMFLOAT2(m_Count[1].size.x + sizeUPx, m_Count[1].size.y + sizeUPy);
			}
			else if (m_waitFrame > WAIT) { m_Count[1].phase = 1; }
			break;
		case 1:	// �k��
			if (m_Count[1].size.x > 0.0f) {
				float sizeUPx = m_textureSize.x / SIZE_UP_FRAME;		// �g�嗦
				float sizeUPy = m_textureSize.y / SIZE_UP_FRAME;
				m_Count[1].size = DirectX::XMFLOAT2(m_Count[1].size.x - sizeUPx, m_Count[1].size.y - sizeUPy);
			}
			break;
		}
	}
	m_waitFrame++;
}

void CCountDown::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_Count[m_kind].pos.x, m_Count[m_kind].pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f/*��ʍ��[X*/, 1280.0f/*��ʉE�[*/, 0.0f/*��ʏ�[*/, 720.0f/*��ʉ��[*/, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	// �X�v���C�g�̐ݒ�
	m_Count[m_kind].posTexCoord.x = m_Count[m_kind].sizeTexCoord.x * m_Count[m_kind].AnimeNo;
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_Count[m_kind].size.x, m_Count[m_kind].size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_Count[m_kind].posTexCoord.x, m_Count[m_kind].posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_Count[m_kind].sizeTexCoord.x, m_Count[m_kind].sizeTexCoord.y));
	Sprite::SetTexture(m_Count[m_kind].pTexture);

	Sprite::Draw();
}
