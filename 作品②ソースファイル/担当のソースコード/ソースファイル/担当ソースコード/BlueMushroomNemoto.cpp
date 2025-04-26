// BlueMushroomNemoto.cpp

//=====�C���N���[�h=====
#include "BlueMushroomNemoto.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
BlueMushroomNemoto::BlueMushroomNemoto(float posX, float posY, float posZ,
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
	m_nKind = Object::BLUE_MUSHROOM_NEMOTO;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 0;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�L�m�R�̍��{";

	// �M�~�b�N�I�u�W�F�N�g�o�^
	m_bGimmick = true;

	// �M�~�b�N�`��t���O
	m_draw = true;
}

/********************
*@brief �f�X�g���N�^
*********************/
BlueMushroomNemoto::~BlueMushroomNemoto()	// �f�X�g���N�^
{

}