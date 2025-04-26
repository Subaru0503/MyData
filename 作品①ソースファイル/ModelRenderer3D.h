///////////////////////////////////////
//
// ���f���`��N���X
//
// �`��ɕK�v�ȃV�F�[�_�[�̐ݒ蓙������
//
///////////////////////////////////////

// �C���N���[�h�K�[�h
#ifndef __MODEL_RENDERER_3D_H__
#define __MODEL_RENDERER_3D_H__

// �C���N���[�h��
#include "Component.h"
#include "Model.h"
#include "Camera.h"

// �V�F�[�_�[�}�l�[�W���[
#include "ShaderManager.h"

// �N���X�w��
class ModelRenderer3D : public Component
{
public:

	// �R���X�g���N�^
	ModelRenderer3D();

	// �f�X�g���N�^
	~ModelRenderer3D();

	// �X�V
	void Execute() final;

	// �`��
	void Draw();

	// �V�F�[�_�[�ɂ���ăo�b�t�@�ɓn������ς���
	void CallByName();

	// �s�����n��
	void SetVS_Default();

	// ��̐F��ς���s�N�Z���V�F�[�_�[
	void SetPS_Sky();

	// �p�X�w��
	void SetPath(std::string name);

	//----�Z�b�g�֐�----

	// �J�����Z�b�g
	inline void SetCamera(Camera* camera)
	{
		m_pCamera = camera;
	}
	
	// �V�F�[�_�[�Z�b�g
	void SetShader(const char** shaderFiles);

	// �`��t���O���Z�b�g
	void SetDrawFlg(bool flg);

	//----�Q�b�g�֐�----

	// �`��t���O��Ԃ�
	bool GetDrawFlg();

private:

	// �J����
	Camera* m_pCamera;

	// �p�X
	char m_ModelName[MAX_PATH];

	// ���f��
	Model* m_pModel;

	// ���f���傫��
	float m_Scale;

	// �V�F�[�_�[��
	const char* m_ShagerName[2];

	// ���f���ɓK�p����V�F�[�_�[
	Shader* m_Shader[2];

	// ����
	float m_Time;

	// �`��t���O
	bool m_DrawFlg;
};

#endif // __MODEL_RENDERER_3D_H__