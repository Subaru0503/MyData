// Fence.cpp

//=====�C���N���[�h=====
#include "Fence.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CFence::CFence(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, int level)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// ���������]�ݒ�
	m_rotate.y = rot;

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::FENCE;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;



	// ----- ���x�����Ƃɐݒ� -----
	switch (m_nLevel)
	{
	case 1:	// �Ȃ�
		break;
	case 2:	// ��
		m_nMoney = 200;		// �z�����ݎ��̎擾���z�ݒ�
		m_createNum = 2;	// �j�󎞂̖؍ސ�����
		m_modelKey = "�؃t�F���X";	// ���f�����ސݒ�
		break;
	case 3:	// ��
		m_nMoney = 600;
		m_createNum = 6;
		m_modelKey = "�΃t�F���X";	// ���f�����ސݒ�
		break;
	case 4:	// �S
		m_nMoney = 2400;
		m_createNum = 6;
		m_modelKey = "�S�t�F���X";	// ���f�����ސݒ�
		break;
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
CFence::~CFence()	// �f�X�g���N�^
{

}