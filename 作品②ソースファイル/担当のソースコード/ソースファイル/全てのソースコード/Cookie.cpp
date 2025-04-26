// Cookie.cpp

//=====�C���N���[�h=====
#include "Cookie.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
Cookie::Cookie(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::COOKIE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 50;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	int random = (int)m_pos.z % 3;
	switch (random)
	{
	case 0:
		m_modelKey = "�N�b�L�[1";
		break;
	case 1:
	case -1:
		m_modelKey = "�N�b�L�[2";
		break;
	case 2:
	case -2:
		m_modelKey = "�N�b�L�[3";
		break;
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
Cookie::~Cookie()	// �f�X�g���N�^
{

}