///////////////////////////////////////
//
// �X�e�[�W2�V�[���N���X
//
// �V�[���̓ǂݍ��ށA�Ǘ�������
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __SCENE_STAGE2_H__
#define __SCENE_STAGE2_H__

//----�C���N���[�h��----
#include "SceneBase.hpp"

//---�t�@�C���ǂݍ��݂Ɏg�p----
#include <iostream>
#include <fstream>
#include <string>

#include "float3.h"

using namespace std;

// �N���X��`
class SceneStage2 : public SceneBase
{
public:

	// �R���X�g���N�^
	SceneStage2() : SceneBase("Stage2") {}

	// ����������
	void Init();

	// �I������
	void Uninit();

	// �X�V����
	void Update(float tick);

	// �`��
	void Draw();

private:

	// �S�[�����ĂȂ��Ƃ��������鏈��
	bool ProcessNotGoal();


	//----�X�e�[�W�쐬�֌W�̊֐�----

	// �t�@�C���ǂݍ���
	void Load();

	// �v���C���[�쐬
	void PlayerCreate(ifstream& file, string cell);

	// �n�ʍ쐬
	void GroundCreate(ifstream& file, string cell);

	// �S�[���쐬
	void GoalCreate(ifstream& file, string cell);

	// �l�W�쐬
	void ScrewCreate(ifstream& file, string cell);

	// �M�~�b�N�쐬
	void GimmickCreate(ifstream& file, string cell);

	// �v���C���[�`�F�b�N�|�C���g�쐬
	void PlayerCheckPointCreate(ifstream& file, string cell);


	//----�M�~�b�N�̐ݒ�----

	// �M�~�b�N�ɑΏۂ̃l�W��ݒ�
	void SetTargetScrew(ifstream& file, string cell);

	// �M�~�b�N�̃`�F�b�N�|�C���g�ݒ�
	void SetCheckPoint(ifstream& file, string cell, vector<float3> checkPoint);

	// �ꎞ�I�ɏo�����鏰�ɕK�v�ȏ���ݒ�
	void SetTemporaryInfo(ifstream& file, string cell);


	//----�C���Q�[��UI----

	// ����UI�쐬
	void TimeCreate(ifstream& file, string cell);

	// �ʏ�UI�쐬(���ɓ��L�̓������Ȃ�UI)
	void InGameNormalUICreate(ifstream& file, string cell);

	// �|�[�YUI�쐬
	void PauseMoziUICreate(ifstream& file, string cell);


	//----�`���[�g���A��UI----

	// �ʏ�UI�쐬(�`���[�g���A�����)
	void MenuNormalUICreate(ifstream& file, string cell);

	// �����UI�쐬
	void LeftUICreate(ifstream& file, string cell);

	// �E���UI�쐬
	void RightUICreate(ifstream& file, string cell);

	// �Q�[���X�^�[�gUI�쐬
	void StartUICreate(ifstream& file, string cell);


	//----�Q�[���I�[�o�[������ɂ���----

	// �Q�[���I�[�o�[��ɕ\������UI���쐬
	void GameOverUICreate();


	//----�S�[��������ɂ���---

	// �S�[����ɕ\������UI���쐬
	void GoalUICreate();

	// �N���A�^�C����\������UI���쐬
	void ClearTimeUICreate();

private:

	// ���v2D�I�u�W�F�N�g�ԍ�
	int m_Total2DObjNo;

	// ���v3D�I�u�W�F�N�g�ԍ�
	int m_Total3DObjNo;

	// ���v����UI�ԍ�
	int m_TotalTimeUINo;

	// �Q�[���I�[�o�[�t���O
	bool m_GameOver;
};

#endif // __SCENE_STAGE2_H__