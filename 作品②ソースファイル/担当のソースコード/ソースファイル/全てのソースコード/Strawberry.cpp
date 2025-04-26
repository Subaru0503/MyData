// Strawberry.cpp

//=====�C���N���[�h=====
#include "Strawberry.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
Strawberry::Strawberry(float posX, float posY, float posZ,
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
	m_nKind = Object::STRAWBERRY;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 250;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 2;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "������";
}

/********************
*@brief �f�X�g���N�^
*********************/
Strawberry::~Strawberry()	// �f�X�g���N�^
{

}