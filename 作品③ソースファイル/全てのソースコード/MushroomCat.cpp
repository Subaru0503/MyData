// MushroomCat.cpp

//=====�C���N���[�h=====
#include "MushroomCat.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
MushroomCat::MushroomCat(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	m_nLevel = 3;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::MUSHROOMCAT;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�˂����̂�";
}

/********************
*@brief �f�X�g���N�^
*********************/
MushroomCat::~MushroomCat()	// �f�X�g���N�^
{

}