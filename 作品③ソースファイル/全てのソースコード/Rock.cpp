// Rock.cpp

//=====�C���N���[�h=====
#include "Rock.h"

#define BASE_SIZE_X	(2)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CRock::CRock(float posX, float posY, float posZ,
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
	m_nKind = Object::ROCK;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;

	// ���x���ʐݒ�
	switch (m_nLevel)
	{
	case 2:
		m_createNum = 2;	// �j�󎞂̏��ΐ�����
		m_nMoney = 200;		// �z�����ݎ��̎擾���z�ݒ�
		break;
	case 3:
		m_createNum = 6;
		m_nMoney = 600;
		break;
	case 4:
		m_createNum = 6;
		m_nMoney = 2400;
		break;
	}

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "��";
}

/********************
*@brief �f�X�g���N�^
*********************/
CRock::~CRock()	// �f�X�g���N�^
{

}
