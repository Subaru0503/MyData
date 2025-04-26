// Candle.cpp

//=====�C���N���[�h=====
#include "Candle.h"

#define BASE_SIZE_X	(0.5)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
Candle::Candle(float posX, float posY, float posZ,
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
	m_nKind = Object::CANDLE;

	// �I�u�W�F�N�g���x���ݒ�
	m_nLevel = level;

	switch (m_nLevel)
	{
	case 1:
		break;
	case 2:
		m_nMoney = 250;	// �z�����ݎ��̎擾���z�ݒ�
		break;
	case 3:
		m_nMoney = 600;	// �z�����ݎ��̎擾���z�ݒ�
		break;
	}



	// ���f���̊g�k���ݒ�
	m_modelRatio = sizeX / BASE_SIZE_X;

	// ���f�����ސݒ�
	//srand((unsigned int)time(NULL));
	//int random = rand() % 2;
	//switch (random)
	//{
	//case 0:
	m_modelKey = "�傫���낤����";
	//break;
	//case 1:
	//	m_modelKey = "�傫���낤����";
	//	break;
	//}
}

/********************
*@brief �f�X�g���N�^
*********************/
Candle::~Candle()	// �f�X�g���N�^
{

}