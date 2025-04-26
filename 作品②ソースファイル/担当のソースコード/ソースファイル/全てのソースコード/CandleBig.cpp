// CandleBig.cpp

//=====�C���N���[�h=====
#include "CandleBig.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CandleBig::CandleBig(float posX, float posY, float posZ,
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
	m_nKind = Object::CANDLE;

	// �z�����ݎ��̎擾���z�ݒ�
	m_nMoney = 600;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = 3;

	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	m_modelKey = "�낤����";

	//�T�E���h
	m_pSoundMng = sound;
}

/********************
*@brief �f�X�g���N�^
*********************/
CandleBig::~CandleBig()	// �f�X�g���N�^
{

}