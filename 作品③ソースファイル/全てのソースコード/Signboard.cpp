// Signboard.cpp

//=====�C���N���[�h=====
#include "Signboard.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CSignboard::CSignboard(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot)
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
	m_nKind = Object::SIGNBOARD;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 200;

	// �j�󎞂̖؍ސ�����
	m_createNum = 2;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	// ���f�����ސݒ�
	m_modelKey = "�Ŕ�";
}

/********************
*@brief �f�X�g���N�^
*********************/
CSignboard::~CSignboard()	// �f�X�g���N�^
{
}