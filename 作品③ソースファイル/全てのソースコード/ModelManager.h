// ModelManager.h
#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include <map>		// map�p
#include "Model.h"	// ���f���ǂݍ��ݗp

/**
*@brief	�����̃I�u�W�F�N�g�̃��f���f�[�^�������Ǘ�����N���X
*/
class ModelManager
{
public:
	ModelManager();			// �R���X�g���N�^
	~ModelManager();		// �f�X�g���N�^
	void LoadModelList();	// �S�Ẵ��f�������[�h
	Model* FindModel(std::string modelTag);		// �^�O�ɉ��������f���f�[�^�̃|�C���^��Ԃ�

private:
	std::map<std::string, Model*> m_models;		// ���[�h�������f���f�[�^�̃}�b�v

	// Stage01,02
	Model* mushroom;	// ���̂�
	Model* mushroomCat;	// �˂����̂�	
	Model* rock;		// ��
	Model* tree;		// ��
	Model* fenceWood;	// �؃t�F���X
	Model* fenceStone;	// �΃t�F���X
	Model* fenceIron;	// �S�t�F���X
	Model* wood;        // �؍�
	Model* koisi;       // ����
	Model* board;       // �Ŕ�
	Model* metal;		// �|��
	Model* tutorialSignboard;	// �`���[�g���A���Ŕ�
	// Stage03
	Model* ChocolateDonuts;		// �`���R�h�[�i�c
	Model* StrawberryChocolateDonuts;		// 䕃`���R�h�[�i�c
	Model* cakePiece;	// �P�[�L1�s�[�X
	Model* strawberry;	// ������
	Model* apolo;		// �A�|��
	Model* cookie1;		// �N�b�L�[1
	Model* cookie2;		// �N�b�L�[2
	Model* cookie3;		// �N�b�L�[3
	Model* chocolateTree;// �`���R�̖�
	Model* BlueCandyRock;				// �L�����f�B�[�̊�
	Model* RedCandyRock;				// �ԃL�����f�B�[�̊�
	Model* chocolateFence;				// �`���R�̃t�F���X
	Model* StrawberryChocolateFence;	// 䕃`���R�̃t�F���X
	Model* chocolatePiece;				// �`���R�̂�����
	Model* StrawberryChocolatePiece;	// 䕃`���R�̂�����
	Model* GreapCandyPiece;				// �O���[�v�L�����f�B�[�̂�����
	Model* GreapFishCandyPiece;			// �O���[�v���L�����f�B�[�̂�����
	Model* OrangeCandyPiece;			// �I�����W�L�����f�B�[�̂�����
	Model* OrangeFishCandyPiece;		// �I�����W���L�����f�B�[�̂�����
	Model* SodaCandyPiece;				// �\�[�_�L�����f�B�[�̂�����
	Model* SodaFishCandyPiece;			// �\�[�_���L�����f�B�[�̂�����
	Model* BigCandle;			// �傫���낤����
	Model* MiddleCandle;		// �������낤����
	Model* sweetsHouse;	// ���َq�̉�
	// �M�~�b�N
	Model* blueMushroom;// �L�m�R
	Model* blueMushroomNemoto;// �L�m�R�̍��{
	Model* biscuit;		// �r�X�P�b�g
	Model* biscuitPiece;// �r�X�P�b�g�̂�����
};

#endif

