// Tree.cpp

//=====�C���N���[�h=====
#include "Tree.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CTree::CTree(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, int level)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::TREE;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;

	switch (m_nLevel)
	{
	case 1:
		break;
	case 2:
		m_nMoney = 200;		// �z�����ݎ��̎擾���z�ݒ�
		m_createNum = 2;	// �j�󎞂̖؍ސ�����
		break;
	case 3:
		m_nMoney = 600;		// �z�����ݎ��̎擾���z�ݒ�
		m_createNum = 6;	// �j�󎞂̖؍ސ�����
		break;
	case 4:
		m_nMoney = 2400;		// �z�����ݎ��̎擾���z�ݒ�
		m_createNum = 6;	// �j�󎞂̖؍ސ�����
		break;
	}

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "��";

	//��]�����_���͋Z
	m_rotate.y = (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ) * (posX + posY + posZ);
}

/********************
*@brief �f�X�g���N�^
*********************/
CTree::~CTree()	// �f�X�g���N�^
{

}