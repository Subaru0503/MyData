///////////////////////////////////////
//
// �V�[���Ǘ��N���X
//
// �V�[���̊Ǘ�������
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __SCENE_ROOT_H__
#define __SCENE_ROOT_H__

//----�C���N���[�h��----
#include "SceneBase.hpp"
#include <DirectXMath.h>

// �N���X��`
class SceneRoot : public SceneBase
{
public:
	// �R���X�g���N�^
	SceneRoot() : SceneBase("Root") {}

	// ������
	void Init();

	// �I������
	void Uninit();

	// �X�V����
	void Update(float tick);

	// �`�揈��
	void Draw();

	// �V�[���؂�ւ�
	void SceneChange();


	//----�Z�b�g�֐�----

	// �V�[������֐�
	static void SetNextScene(SceneBase::Scene next);


	//----�Q�b�g�֐�----

	// ���̃V�[�����擾
	static SceneBase::Scene GetNextScene();

	// ���݂̃V�[�����擾
	static SceneBase::Scene GetCurrentScene();

private:
	//----�V�[���Ɋւ������----

	// ���̃V�[�����
	static Scene m_NextScene;

	// ���݂̃V�[�����
	static Scene m_CurrentScene;

#ifdef _DEBUG
	DirectX::XMFLOAT3 m_camPos;
	DirectX::XMFLOAT3 m_camLook;
	DirectX::XMFLOAT3 m_camUp;
#endif
};

#endif // __SCENE_ROOT_H__

