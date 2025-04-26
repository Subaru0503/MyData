// WoodRoyal.cpp


//=====�C���N���[�h=====
#include "WoodRoyal.h"

/************************************************
*@brief ���W�ݒ�����t���R���X�g���N�^
*************************************************/
CWoodRoyal::CWoodRoyal(float posX, float posY, float posZ)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// �폜�t���O������
	m_bDelete = false;

	// �X�P�[���ݒ�
	m_scale = { 0.5f,0.5f,0.5f };

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::WOOD;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 400;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f�����ސݒ�
	m_modelKey = "�؍�";


	// �h���b�v�A�j���[�V�����t���O�𗧂Ă�
	m_bDrop = false;

	//��]�����_���͋Z
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

CWoodRoyal::CWoodRoyal(float posX, float posY, float posZ, DirectX::XMVECTOR dropDirection, ModelManager* pModelManager)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// �폜�t���O������
	m_bDelete = false;

	// �X�P�[���ݒ�
	m_scale = { 0.5f,0.5f,0.5f };

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::WOOD;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 100;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f�����ސݒ�
	m_modelKey = "�؍�";

	// �h���b�v�A�j���[�V�����t���O�𗧂Ă�
	m_bDrop = true;
	m_EfkDestory = true;
	// �h���b�v����̈ړ������ݒ�
	m_dropDirection = dropDirection;

	// ���f���ݒ�
	m_pModelManager = pModelManager;
	SetModelData();

	//��]�����_���͋Z
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

/********************
*@brief �f�X�g���N�^
*********************/
CWoodRoyal::~CWoodRoyal()	// �f�X�g���N�^
{

}