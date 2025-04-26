// BiscuitPiece.cpp

//=====�C���N���[�h=====
#include "BiscuitPiece.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CBiscuitPiece::CBiscuitPiece(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	DirectX::XMVECTOR dropDirection, ModelManager* pModelManager)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::BISCUITPIECE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 50;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�r�X�P�b�g�̂�����";

	if (pModelManager)
	{
		// �h���b�v�A�j���[�V�����t���O�𗧂Ă�
		m_bDrop = true;

		// �h���b�v����̈ړ������ݒ�
		m_dropDirection = dropDirection;

		// ���f���ݒ�
		m_pModelManager = pModelManager;
		SetModelData();

		//��]�����_���͋Z
		m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
CBiscuitPiece::~CBiscuitPiece()	// �f�X�g���N�^
{

}