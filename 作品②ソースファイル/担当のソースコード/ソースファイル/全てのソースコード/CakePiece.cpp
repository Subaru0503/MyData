// CakePiece.cpp

//=====�C���N���[�h=====
#include "CakePiece.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CakePiece::CakePiece(float posX, float posY, float posZ,
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
	m_nKind = Object::CAKEPIECE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 600;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�P�[�L�s�[�X";
}

/********************
*@brief �f�X�g���N�^
*********************/
CakePiece::~CakePiece()	// �f�X�g���N�^
{

}