// BurningObject.cpp

//=====�C���N���[�h=====
#include "BurningObject.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CBurningObject::CBurningObject(float posX, float posY, float posZ,
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
	m_nKind = Object::BURNINGOBJECT;

	// �j�󎞂̐����I�u�W�F�N�g���ݒ�
	m_createNum = 2;
}

/********************
*@brief �f�X�g���N�^
*********************/
CBurningObject::~CBurningObject()
{
}