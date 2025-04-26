// ChocolateFence.cpp

//=====�C���N���[�h=====
#include "ChocolateFence.h"

//#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
ChocolateFence::ChocolateFence(float posX, float posY, float posZ,
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
	m_nKind = Object::CHOCOLATEFENCE;

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
		break;
	}

	//// ���f���̊g�k���ݒ�
	//m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	int random = (int)m_pos.z % 2;
	switch (random)
	{
	case 0:
		m_modelKey = "�`���R�̃t�F���X";
		break;
	case 1:
	case -1:
		m_modelKey = "䕃`���R�̃t�F���X";
		break;
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
ChocolateFence::~ChocolateFence()	// �f�X�g���N�^
{

}