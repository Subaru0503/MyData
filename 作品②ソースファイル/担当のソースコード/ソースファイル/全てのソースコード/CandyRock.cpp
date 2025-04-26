// CandyRock.cpp

//=====�C���N���[�h=====
#include "CandyRock.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CandyRock::CandyRock(float posX, float posY, float posZ,
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
	m_nKind = Object::CANDYROCK;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;

	switch (m_nLevel)
	{
	case 1:
		break;
	case 2:
		m_nMoney = 300;		// �z�����ݎ��̎擾���z�ݒ�
		m_createNum = 3;	// �L�����f�B�[�̂�����̐������ݒ�
		break;
	case 3:
		m_nMoney = 600;
		m_createNum = 6;
		break;
	case 4:
		m_nMoney = 1200;
		m_createNum = 6;
		break;
	}

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	int random = (int)m_pos.x % 2;
	switch (random)
	{
	case 0:
		m_modelKey = "�L�����f�B�[�̊�";
		break;
	case 1:
	case -1:
		m_modelKey = "�ԃL�����f�B�[�̊�";
		break;
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
CandyRock::~CandyRock()	// �f�X�g���N�^
{

}