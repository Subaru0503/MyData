// Signboard.cpp

//=====�C���N���[�h=====
#include "TutorialSignboard.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CTutorialSignboard::CTutorialSignboard(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, int kind)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// ������������ݒ�
	m_rotate.y = rot;

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::TUTORIALSIGNBOARD;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 250;

	// �j�󎞂̖؍ސ�����
	m_createNum = 2;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	switch (kind)
	{
	case textureKind::suction:
		m_nTuturoalKind = textureKind::suction;
		break;
	case textureKind::custom:
		m_nTuturoalKind = textureKind::custom;
		break;
	case textureKind::shop:
		m_nTuturoalKind = textureKind::shop;
		break;
	}

	// ���f�����ސݒ�
	m_modelKey = "�`���[�g���A���Ŕ�";


}

/********************
*@brief �f�X�g���N�^
*********************/
CTutorialSignboard::~CTutorialSignboard()	// �f�X�g���N�^
{
}

