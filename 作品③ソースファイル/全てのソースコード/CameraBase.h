//CameraBase.h
#ifndef __CAMERA_BASE_H__
#define __CAMERA_BASE_H__
//=====�C���N���[�h��=====
#include <DirectXMath.h>
#include "SceneManager.h"
#include "Planet.h"

//=====�N���X=====
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase() {};
	virtual void Update() = 0;

	virtual DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();
	DirectX::XMFLOAT4X4 GetNPViewMatrix();			// �]�u�O
	DirectX::XMFLOAT4X4 GetNPProjectionMatrix();	// �]�u�O
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();
	virtual void SetGreen(Planet* green) = 0;
	virtual void SetMushroom(Planet* mushroom) = 0;
	virtual void SetWholeCake(Planet* wholecake) = 0;

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	//�r���[�s��̐ݒ�ɕK�v�ȕϐ�
	float m_fovy, m_aspect, m_near, m_far;	//�v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
	float m_radY, m_radXZ, m_rad;			//�J�����̈ړ��E��]�ɕK�v�ȕϐ�
};

#endif