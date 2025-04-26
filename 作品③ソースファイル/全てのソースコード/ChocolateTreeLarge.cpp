// ChocolateTreeLarge.cpp

//=====�C���N���[�h=====
#include "ChocolateTreeLarge.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
ChocolateTreeLarge::ChocolateTreeLarge(float posX, float posY, float posZ,
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
	m_nKind = Object::CHOCOLATETREE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 1200;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 4;

	// �`���R�̂����琶�����ݒ�
	m_createNum = 8;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�`���R�̖�";
}

/********************
*@brief �f�X�g���N�^
*********************/
ChocolateTreeLarge::~ChocolateTreeLarge()	// �f�X�g���N�^
{

}