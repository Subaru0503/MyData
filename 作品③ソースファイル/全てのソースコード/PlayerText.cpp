//=================================================================
//
//	PlayerText.cpp
//	�z�����ݎ��̃v���C���[�e�L�X�g�֘A
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "PlayerText.h"

#define SIZE_RATIO		(0.3f)		// �摜�{��
#define POP_START_POS_X	(0.0f)	// �o���J�n���W
#define POP_START_POS_Y	(100.0f)
#define POS_X			(900.0f)	//�e�L�X�gBOX�\�����W
#define POS_Y			(135.0f)
#define ANIME_POS_Y		(130.0f)	// �A�j���[�V�������W
#define MOVE_FRAME		(10)		// �\���A�j���[�V�����Đ��X�s�[�h
#define WAIT_FRAME		(160)		// BOX�\���I���A�j���[�V�����Đ��܂ł̃t���[��(60/�b)

CPlayerText::CPlayerText()
	: m_animeNo(0)
	, m_animePhase(0)
	, m_waitFrame(0)
	, m_pos(440.0f, 95.0f)
	, m_size(0.0f, 0.0f)
	, m_sizeTexCoord(1.0f, 1.0f)
	, m_posTexCoord(0.0f, 0.0f)
	, m_tree1(0)
	, m_tree2(0)
	, m_tree3(0)
	, m_rock1(0)
	, m_rock2(0)
	, m_rock3(0)
	, m_fence(0)
	, m_signBord(0)
{
	// �e�N�X�`���ǂݍ���
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/PlayerText/testPlayerText.png"))) {	// �e�L�X�g
		MessageBox(NULL, "text.png", "Error", MB_OK);
	}
	// �e�N�X�`���T�C�Y�ݒ�
	m_TextureSize.x = 300.0f;	// �e�N�X�`���̖{���̉摜�T�C�Y���擾
	m_TextureSize.y = 350.0f;	// �c����͂��̂܂܂ŃT�C�Y����
}

CPlayerText::~CPlayerText()
{
	SAFE_DELETE(m_pTexture);
}

void CPlayerText::Update()
{
	// ----- ���� -----
	m_pObjList = *(m_pObjMng->GetObjectList());			// �I�u�W�F�N�g�̃��X�g�擾

	// =-=-= �q���g�e�L�X�g�`�攻�� =-=-=
	for (auto it = m_pObjList.begin(); it != m_pObjList.end(); it++) {	// �S�Č���
		if ((*it)->IsShake()) {							// �v���v�����Ă����
			switch ((*it)->GetKind())					// ��ނɂ���ăe�L�X�g�̎�ނ�ς���
			{
			case Object::Kind::TREE:	// ��
				if ((*it)->GetLevel() == 1) {
					if (!m_tree1)	SetDraw(barabara);
					m_tree1++;			// ��x�ƕ\�����Ȃ��悤�ɂ���B
				}
				if ((*it)->GetLevel() == 2) {
					if (!m_tree2)	SetDraw(barabara);
					m_tree2++;
				}
				if ((*it)->GetLevel() == 3) {
					if (!m_tree3)	SetDraw(barabara);
					m_tree3++;
				}
				break;
			case Object::Kind::ROCK:	// ��
				if ((*it)->GetLevel() == 1) {
					if (!m_rock1)	SetDraw(barabara);
					m_rock1++;
				}
				if ((*it)->GetLevel() == 2) {
					if (!m_rock2)	SetDraw(barabara);
					m_rock2++;
				}
				if ((*it)->GetLevel() == 3) {
					if (!m_rock3)	SetDraw(barabara);
					m_rock3++;
				}
				break;
			case Object::Kind::FENCE:	// ��
				if (!m_fence)	SetDraw(barabara);
				m_fence++;
			case Object::Kind::SIGNBOARD:// �Ŕ�
				if (!m_signBord)	SetDraw(barabara);
				m_signBord++;
				break;
			}
		}
	}

	// ----- �z�����߂��e�L�X�g�\�� -----�����폜�\��
	if (m_pObjMng->GetFirstSuctionFlg()->tree1 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree1++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->tree2 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree2++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->tree3 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->tree3++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock1 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->rock1++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock2 == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->rock2++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->rock3 == 1) {
		m_pObjMng->GetFirstSuctionFlg()->rock3++;
		SetDraw(suikometa);
	}
	if (m_pObjMng->GetFirstSuctionFlg()->fence == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->fence++;
	}
	if (m_pObjMng->GetFirstSuctionFlg()->signBoard == 1) {
		SetDraw(suikometa);
		m_pObjMng->GetFirstSuctionFlg()->signBoard++;
	}

	// ----- �A�j���[�V�����X�V -----
	//Animation();
}

void CPlayerText::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f/*��ʍ��[X*/, 1280.0f/*��ʉE�[*/, 0.0f/*��ʏ�[*/, 720.0f/*��ʉ��[*/, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


	// �X�v���C�g�̐ݒ�
	m_posTexCoord.x = m_sizeTexCoord.x * m_animeNo;
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_size.x, m_size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_posTexCoord.x, m_sizeTexCoord.y * m_animeNo));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_sizeTexCoord.x, m_sizeTexCoord.y));
	Sprite::SetTexture(m_pTexture);

	Sprite::Draw();
}

void CPlayerText::Animation()
{
	switch (m_animePhase)	// �A�j���[�V�����i�K�ɂ���ĕ���
	{
		// ----- �\���ҋ@�ҋ@ -----
	case 0:
		// ----- ������ -----
		m_pos = DirectX::XMFLOAT2(POP_START_POS_X, POP_START_POS_Y);
		m_size = DirectX::XMFLOAT2(0.0f, 0.0f);
		break;
		// ----- �o�� -----
	case 1:	// �g�債�Ȃ��珊��̈ʒu���傢����
		if (m_pos.y <= ANIME_POS_Y) {// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (ANIME_POS_Y - POP_START_POS_Y) / (MOVE_FRAME * 0.95f);	// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 1.02f / (MOVE_FRAME * 0.95f);		// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 1.02f / (MOVE_FRAME * 0.95f);

			// ----- �l�X�V -----
			m_pos.y += moveY;													// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);	// �g��
		}
		else {
			m_animePhase = 1;		// ���̃A�j���[�V������
		}
		break;
	case 2:	// �k�����Ȃ��珊��̈ʒu��
		if (m_pos.y <= POS_Y) {		// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 0.02f / (MOVE_FRAME * 0.05f);			// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 0.02f / (MOVE_FRAME * 0.05f);

			// ----- �l�X�V -----
			m_pos.y += moveY;														// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// �g��
		}
		else {
			m_animePhase = 3;		// ���̃A�j���[�V������
		}
		break;
	case 3:	//�ҋ@
		if (m_waitFrame >= WAIT_FRAME) {
			m_animePhase = 4;
			m_waitFrame = 0;
		}
		m_waitFrame++;
		break;
		// ----- �\���I�� -----
	case 4:	// �g�債�Ȃ��炿����Ɖ���
		if (m_pos.y >= ANIME_POS_Y) {		// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 0.03f / (MOVE_FRAME * 0.05f);			// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 0.03f / (MOVE_FRAME * 0.05f);

			// ----- �l�X�V -----
			m_pos.y -= moveY;														// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);		// �g��
		}
		else {
			m_animePhase = 5;		// ���̃A�j���[�V������
		}
		break;

	case 5:	// �k�����Ȃ����ʒ�����
		if (m_pos.y <= POP_START_POS_Y) {		// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (POP_START_POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.95f);		// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 1.01f / (MOVE_FRAME * 0.95f);			// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 1.01f / (MOVE_FRAME * 0.95f);

			// ----- �l�X�V -----
			m_pos.y += moveY;														// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// �k��
		}
		else {
			m_animePhase = 0;		// �A�j���[�V������~�E���Z�b�g
		}
		break;
	}
}

// ========== �����o���\���A�j���[�V���� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �w��̐����o����\������
// =================================
void CPlayerText::PopAnimation()
{
	switch (m_animePhase)
	{
		// ----- �o�� -----
	case 1:	// �g�債�Ȃ��珊��̈ʒu���傢����
		if (m_pos.y >= ANIME_POS_Y) {// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (POP_START_POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.95f);	// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 1.02f / (MOVE_FRAME * 0.95f);			// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 1.02f / (MOVE_FRAME * 0.95f);

			// ----- �l�X�V -----
			m_pos.y -= moveY;													// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x + sizeUpx, m_size.y + sizeUpy);	// �g��
		}
		else {
			m_animePhase = 2;		// ���̃A�j���[�V������
		}
		break;
	case 2:	// �k�����Ȃ��珊��̈ʒu��
		if (m_pos.y <= POS_Y) {		// ����ʒu�ɓ��B���Ă��Ȃ����
			// ----- ���� -----
			float moveY = (POS_Y - ANIME_POS_Y) / (MOVE_FRAME * 0.05f);				// �P�t���[��������̈ړ��ʎZ�o
			float sizeUpx = m_TextureSize.x * 0.02f / (MOVE_FRAME * 0.05f);			// �P�t���[��������̊g��ʎZ�o
			float sizeUpy = m_TextureSize.y * 0.02f / (MOVE_FRAME * 0.05f);

			// ----- �l�X�V -----
			m_pos.y += moveY;														// �ړ�
			m_size = DirectX::XMFLOAT2(m_size.x - sizeUpx, m_size.y - sizeUpy);		// �g��
		}
		else {
			m_animePhase = 3;		// ���̃A�j���[�V������
		}
		break;
		break;
	}

}



// ========== �e�L�X�g�\�� ==========
// ���@���F
// kind �q���g�̎��
// �߂�l�F�Ȃ�
// �w��̃e�L�X�g��\������(���łɕ\���̏ꍇ�͏㏑��)
// =================================
void CPlayerText::SetDraw(kind kind)
{
	// ----- ���ݕ\���̃E�B���h�E������ -----
	// ������
	m_pos = DirectX::XMFLOAT2(POP_START_POS_X, POP_START_POS_Y);
	m_size = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_waitFrame = 0;
	// ----- �V�����E�B���h�E��ݒ� -----
	m_animeNo = (int)kind;
	m_animePhase = 0;
}

void CPlayerText::SetObjMng(CObjectMng* pObjMng)
{
	m_pObjMng = pObjMng;
}