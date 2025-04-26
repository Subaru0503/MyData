// House.cpp

//=====�C���N���[�h=====
#include "House.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CHouse::CHouse(float posX, float posY, float posZ,
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
	m_nKind = Object::HOUSE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 1500;

	// �j�󎞂̖؍ސ�����
	m_createNum = 15;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;

	// ���f�����ސݒ�
	// m_modelKey = "��";
}

/********************
*@brief �f�X�g���N�^
*********************/
CHouse::~CHouse()	// �f�X�g���N�^
{

}