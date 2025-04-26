// �C���N���[�h�K�[�h
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

// �C���N���[�h��
#include "SceneBase.hpp"

//---�t�@�C���ǂݍ��݂Ɏg�p----
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// �N���X��`
class SceneGame : public SceneBase
{
public:
	SceneGame() : SceneBase("Game") {}
	void Init();				// ����������
	void Uninit();				// �I������
	void Update(float tick);	// �X�V����
	void Draw();				// �`��

private:

	// �S�[�����ĂȂ��Ƃ��������鏈��
	bool ProcessNotGoal();

	//----�X�e�[�W�쐬�֌W�̊֐�----
	void Load();				// �t�@�C���ǂݍ���

	void PlayerCreate(ifstream& file, string cell);		// �v���C���[�쐬
	void GroundCreate(ifstream& file, string cell);		// �n�ʍ쐬
	void GoalCreate(ifstream& file, string cell);		// �S�[���쐬
	void ScrewCreate(ifstream& file, string cell);		// �l�W�쐬
	void GimmickCreate(ifstream& file, string cell);	// �M�~�b�N�쐬

	void SetTargetScrew(ifstream& file, string cell);	// �M�~�b�N�ɑΏۂ̃l�W��ݒ�

	// �C���Q�[��UI
	void TimeCreate(ifstream& file, string cell);		// ����UI�쐬
	void InGameNormalUICreate(ifstream& file, string cell);		// �ʏ�UI�쐬(���ɓ��L�̓������Ȃ�UI)
	void PauseMoziUICreate(ifstream& file, string cell);		// �|�[�YUI�쐬
	// �`���[�g���A��UI
	void MenuNormalUICreate(ifstream& file, string cell);	// �ʏ�UI�쐬(�`���[�g���A�����)
	void LeftUICreate(ifstream& file, string cell);		// �����UI�쐬
	void RightUICreate(ifstream& file, string cell);	// �E���UI�쐬
	void StartUICreate(ifstream& file, string cell);	// �Q�[���X�^�[�gUI�쐬

	//----�Q�[���I�[�o�[������ɂ���----
	void GameOverUICreate();			// �Q�[���I�[�o�[��ɕ\������UI���쐬

	//----�S�[��������ɂ���---
	void GoalUICreate();				// �S�[����ɕ\������UI���쐬
	void ClearTimeUICreate();			// �N���A�^�C����\������UI���쐬

private:
	int m_Total2DObjNo;			// ���v2D�I�u�W�F�N�g�ԍ�
	int m_Total3DObjNo;			// ���v3D�I�u�W�F�N�g�ԍ�
	int m_TotalTimeUINo;		// ���v����UI�ԍ�
	bool m_GameOver;			// �Q�[���I�[�o�[�t���O
};

#endif // __SCENE_GAME_H__