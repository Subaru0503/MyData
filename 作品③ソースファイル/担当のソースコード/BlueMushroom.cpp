// BlueMushroom.cpp

//=====�C���N���[�h=====
#include "BlueMushroom.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
BlueMushroom::BlueMushroom(float posX, float posY, float posZ,
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
	m_nKind = Object::BLUE_MUSHROOM;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 1000;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�L�m�R";

	// �M�~�b�N�I�u�W�F�N�g�o�^
	m_bGimmick = true;
}

/********************
*@brief �f�X�g���N�^
*********************/
BlueMushroom::~BlueMushroom()	// �f�X�g���N�^
{

}