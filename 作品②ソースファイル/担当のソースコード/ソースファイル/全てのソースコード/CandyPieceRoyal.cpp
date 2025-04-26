// CandyPieceRoyal.cpp


//=====�C���N���[�h=====
#include "CandyPieceRoyal.h"
#include <time.h>

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CandyPieceRoyal::CandyPieceRoyal(float posX, float posY, float posZ,
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
	m_nKind = Object::CANDYPIECE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 200;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	srand((unsigned int)time(NULL));
	int random = rand() % 6;
	switch (random)
	{
	case 0:
		m_modelKey = "�O���[�v�L�����f�B�[�̂�����";
		break;
	case 1:
		m_modelKey = "�O���[�v���L�����f�B�[�̂�����";
		break;
	case 2:
		m_modelKey = "�I�����W�L�����f�B�[�̂�����";
		break;
	case 3:
		m_modelKey = "�I�����W���L�����f�B�[�̂�����";
		break;
	case 4:
		m_modelKey = "�\�[�_�L�����f�B�[�̂�����";
		break;
	case 5:
		m_modelKey = "�\�[�_���L�����f�B�[�̂�����";
		break;
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
CandyPieceRoyal::~CandyPieceRoyal()	// �f�X�g���N�^
{

}