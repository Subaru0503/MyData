// Biscuit.cpp

//=====�C���N���[�h=====
#include "Biscuit.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
Biscuit::Biscuit(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float height)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::BISCUIT;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 1000;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 2;

	// �j�󎞂̃r�X�P�b�g�̂����琶�����ݒ�
	m_createNum = 4;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�r�X�P�b�g";

	// �ϋv��
	m_nDefCnt = 2;

	// ����
	m_randHeight = height;
}

/********************
*@brief �f�X�g���N�^
*********************/
Biscuit::~Biscuit()	// �f�X�g���N�^
{

}

