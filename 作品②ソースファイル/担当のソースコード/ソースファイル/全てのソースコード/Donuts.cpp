// Donuts.cpp

//=====�C���N���[�h=====
#include "Donuts.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
Donuts::Donuts(float posX, float posY, float posZ,
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
	m_nKind = Object::DONUTS;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 250;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 2;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	int random = (int)m_pos.x % 2;
	switch (random)
	{
	case 0:
		m_modelKey = "�`���R�h�[�i�c";
		break;
	case 1:
	case -1:
		m_modelKey = "䕃`���R�h�[�i�c";
		break;
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
Donuts::~Donuts()	// �f�X�g���N�^
{

}