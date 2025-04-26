//----�C���N���[�h�K�[�h----
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

//----�C���N���[�h��----
#include "SceneBase.hpp"

//---�t�@�C���ǂݍ��݂Ɏg�p----
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// �N���X��`
class SceneTitle : public SceneBase
{
public:
	SceneTitle() : SceneBase("Title") {}
	void Init();					// ������
	void Uninit();					// �I������
	void Update(float tick);		// �X�V
	void Draw();					// �`��

private:
	//----UI�쐬�֌W�̊֐�----
	void Load();					// �t�@�C���ǂݍ���

	// �^�C�g����UI�쐬
	void TitleNameCreate(ifstream& file, string cell);

	// �l�WUI�쐬
	void TitleScrewCreate(ifstream& file, string cell);

	// �Q�[���X�^�[�gUI�쐬
	void GameStartCreate(ifstream& file, string cell);

	// �^�C�g����UI�쐬
	void BirdCreate(ifstream& file, string cell);

	// �ʏ�UI�쐬
	void NormalUICreate(ifstream& file, string cell);


private:
	int m_Total2DObjNo;			// ���v2D�I�u�W�F�N�g�ԍ�
	int m_Total3DObjNo;			// ���v3D�I�u�W�F�N�g�ԍ�
	bool m_Change;
};

#endif // __SCENE_TITLE_H__