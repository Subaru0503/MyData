// ChocolatePieceRoyal.cpp


//=====�C���N���[�h=====
#include "ChocolatePieceRoyal.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
ChocolatePieceRoyal::ChocolatePieceRoyal(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ,
	DirectX::XMVECTOR dropDirection, ModelManager* pModelManager,
	int strawberry)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::CHOCOLATEPIECE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 200;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	if (strawberry)
	{
		m_modelKey = "䕃`���R�̂�����";
	}
	else
	{
		m_modelKey = "�`���R�̂�����";
	}

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
ChocolatePieceRoyal::~ChocolatePieceRoyal()	// �f�X�g���N�^
{

}