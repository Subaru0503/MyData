// Rubbish.cpp

//=====�C���N���[�h=====
#include "Rubbish.h"

/************************************************
*@brief ���W�ݒ�����t���R���X�g���N�^
*************************************************/
CRubbish::CRubbish(float posX, float posY, float posZ)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��
{
	// ��{����������
	Init();

	// �폜�t���O������
	m_bDelete = false;

	// �X�P�[���ݒ�
	m_scale = { 0.5f,0.5f,0.5f };

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::RUBBISH;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 50;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 1;

	// ���f�����ސݒ�
	// m_modelKey = "�S�~����";
}

/********************
*@brief �f�X�g���N�^
*********************/
CRubbish::~CRubbish()	// �f�X�g���N�^
{
}
