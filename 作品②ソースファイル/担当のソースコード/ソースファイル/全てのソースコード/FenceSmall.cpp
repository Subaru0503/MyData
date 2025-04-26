// Fence.cpp

//=====�C���N���[�h=====
#include "FenceSmall.h"

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CFenceSmall::CFenceSmall(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ, float rot, CSoundMng* sound)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// ���������]�ݒ�
	m_rotate.y = rot;

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::FENCE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 250;

	// �j�󎞂̖؍ސ�����
	m_createNum = 2;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 2;

	// ���f�����ސݒ�
	m_modelKey = "�t�F���X";

	//�T�E���h
	m_pSoundMng = sound;
}

/********************
*@brief �f�X�g���N�^
*********************/
CFenceSmall::~CFenceSmall()	// �f�X�g���N�^
{

}