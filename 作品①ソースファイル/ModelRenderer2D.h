///////////////////////////////////////
//
// 2D���f���`��N���X
//
// �`��ɕK�v�ȃV�F�[�_�[�̐ݒ蓙������
//
///////////////////////////////////////

//----�C���N���[�h�K�[�h----
#ifndef __MODEL_RENDERER_2D_H__
#define __MODEL_RENDERER_2D_H__

//----�C���N���[�h��----
#include "Component.h"
#include "Texture.h"
#include "Camera.h"
#include "Sprite.h"

// �N���X��`
class ModelRenderer2D : public Component
{
public:
	// �`��p�����[�^
	struct Param
	{
		DirectX::XMFLOAT2 uvSize;
		DirectX::XMFLOAT4 color;
		int animeNo;
		DirectX::XMINT2 MaxGrid;
	};

public:

	// �R���X�g���N�^
	ModelRenderer2D();

	// �f�X�g���N�^
	~ModelRenderer2D();

	// �`��
	void Draw();

	// �V�F�[�_�[�ɂ���ăo�b�t�@�ɓn������ς���
	void CallByName();
	
	// �^�C�g���ɂŎg���V�F�[�_�[�ɏ���n��
	void SetPS_Title();

	// �e�N�X�`���ǂݍ���
	inline void Load(const char* name)
	{
		if (FAILED(m_pTexture->Create(name)))
		{
			MessageBox(NULL, name, "Error", MB_OK);
		}
	}

	//----�Z�b�g�֐�----
	inline void SetCamera(GameObject* camObj, Camera* camera)
	{
		m_pCamObj = camObj;
		m_pCamera = camera;
	}
	inline void SetDraw(bool flg)
	{
		m_DrawFlg = flg;
	}

	// ���_�V�F�[�_�[�ݒ�
	void SetVertexShader(Shader* vs, const char* shaderFiles);

	// �s�N�Z���V�F�[�_�[�ݒ�
	void SetPixelShader(Shader* ps, const char* shaderFiles);


	//----�Q�b�g�֐�----
	inline Param* GetParam()
	{
		return &m_Param;
	}
	inline bool GetDraw()
	{
		return m_DrawFlg;
	}

private:

	// �J����
	GameObject* m_pCamObj;
	Camera* m_pCamera;

	// �V�F�[�_�[��
	const char* m_ShagerName[2];

	// ���_�V�F�[�_�[
	Shader* m_VS;

	// �s�N�Z���V�F�[�_�[
	Shader* m_PS;

	// �e�N�X�`��
	Texture* m_pTexture;

	// �`��p�����[�^
	Param m_Param;

	// �`��t���O
	bool m_DrawFlg;
};

#endif // __MODEL_RENDERER_2D_H__