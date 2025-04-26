#ifndef __PLANET_H__
#define __PLANET_H__

//=====�C���N���[�h=====
#include <DirectXMath.h>
#include "Shader.h"
#include "Model.h"

/****************************************
*@brief �Z���N�g��ʂɔz�u����f���̏���
*****************************************/
class Planet
{
public:
	Planet();
	virtual ~Planet();
	void Update(float tick);
	void Draw(DirectX::XMFLOAT4X4* mat);
	DirectX::XMFLOAT3 GetPos();
	void StartFocus();
	void EndFocus();

protected:
	Model* m_pModel;		// ���f���f�[�^
	VertexShader* m_pVS;	// ���_�V�F�[�_�[
	DirectX::XMFLOAT3 m_pos;	// ���W
	DirectX::XMFLOAT3 m_scale;	// �g�k��
	DirectX::XMFLOAT3 m_rotate;	// ��]�p�x
	bool m_bFocus;				// �I���t���O

};

#endif // !__PLANET_H__