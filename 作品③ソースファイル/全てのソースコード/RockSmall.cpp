// RockSmall.cpp

//=====�C���N���[�h=====
#include "RockSmall.h"
#define BASE_SIZE_X	(2)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CRockSmall::CRockSmall(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, CSoundMng* sound)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::ROCK;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 300;

	// �j�󎞂̖؍ސ�����
	m_createNum = 2;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 2;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "��";

	m_pSoundMng = sound;
}

/********************
*@brief �f�X�g���N�^
*********************/
CRockSmall::~CRockSmall()	// �f�X�g���N�^
{
}