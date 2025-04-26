//=================================================================
//
//	Fade.cpp
//	�t�F�[�h�֘A
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "Fade.h"

// ========== �R���X�g���N�^ ==========
Fade::Fade()
	: m_alpha(0.0f)
	, m_isIn(false)
	, m_time(0.0f)
	, m_totalTime(0.0f)
	, m_BGKind(NONE)
{
	// ----- �e�N�X�`���ǂݍ��� -----
	for (int i = 0; i < MAX_FADE; i++) {
		m_pTexture[i] = new Texture();
	}
	// �^�����t�F�[�h
	if (FAILED(m_pTexture[kind::WHITE]->Create("Assets/Texture/whiteFade.png"))) {
		MessageBox(NULL, "whiteFade.png", "Error", MB_OK);
	}
	// �^�����t�F�[�h
	if (FAILED(m_pTexture[kind::BLACK]->Create("Assets/Texture/Shop_BG.png"))) {
		MessageBox(NULL, "blackFade.png", "Error", MB_OK);
	}
	// tips
	if (FAILED(m_pTexture[kind::TIPS]->Create("Assets/Texture/TIPS�@�w�i.png"))) {
		MessageBox(NULL, "tipsFade.png", "Error", MB_OK);
	}
	// �f���t�F�[�h
	if (FAILED(m_pTexture[kind::PLANET]->Create("Assets/Texture/PlanetFade.png"))) {
		MessageBox(NULL, "PlanetFade.png", "Error", MB_OK);
	}

}

// ========== �f�X�g���N�^ ==========
Fade::~Fade()
{
	for (int i = 0; i < MAX_FADE; i++) {
		delete m_pTexture[i];
		m_pTexture[i] = nullptr;
	}
}

// ========== Update�֐� ==========
void Fade::Update()
{
	// �t�F�[�h�����s����K�v�����邩
	if (!IsPlay())
	{
		return;
	}

	// �J�E���g�_�E��
	m_time -= 1.0f / 60.0f;// 60�t���[���łP

	// �t�F�[�h�̌o�ߎ��Ԃ̊������瓧���x�����߂�
	float rate = m_time / m_totalTime;

	// �t�F�[�h�C���̏ꍇ�����A�����x�𔽓]������
	if (!m_isIn)
	{
		rate = 1.0f - rate;
	}

	m_alpha = rate;
}

// ========== Draw�֐� ==========
void Fade::Draw()
{
	// ----- �v�f���� -----
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(1280.0f / 2.0f, 720.0f / 2, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	switch (m_BGKind) {	// �ݒ肳�ꂽ��ނɂ���ăe�N�X�`����I��
	case Fade::NONE:	return;
	case Fade::WHITE:	Sprite::SetTexture(m_pTexture[WHITE]);	break;
	case Fade::BLACK:	Sprite::SetTexture(m_pTexture[BLACK]);	break;
	case Fade::TIPS:	Sprite::SetTexture(m_pTexture[TIPS]);	break;
	case Fade::PLANET:	Sprite::SetTexture(m_pTexture[PLANET]);	break;
	}

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(1280.0f, -720.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha));
	Sprite::Draw();
}

// �t�F�[�h�J�n�̂��ߕK�v����ݒ肷��
void Fade::Start(bool isIn, float time, kind kind)
{
	// �t�F�[�h�Đ����͐ݒ�ł��Ȃ�
	if (IsPlay())
	{
		return;
	}

	if (isIn)	m_alpha = 1.0f;
	else		m_alpha = 0.0f;
	m_isIn = isIn;
	m_time = time;
	m_totalTime = time;	// time�̎��Ԃ����ăt�F�[�h��������
	m_BGKind = kind;	// �w�i��ސݒ�
}

// �t�F�[�h����
bool Fade::IsPlay()
{
	if (m_time == 0.0f)
		m_BGKind = NONE;

	return m_time > 0.0f;
}

// �t�F�[�h�̓����x(�i��)
float Fade::GetAlpha()
{
	return m_alpha;
}
