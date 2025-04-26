//CameraBase.cpp
//=====�C���N���[�h��=====
#include "CameraBase.h"

#define ASPECT	(16.0f / 9.0f)

//=====�R���X�g���N�^=====
CameraBase::CameraBase()
	: m_pos(0.0f, 2.0f, 2.0f)
	, m_look(0.0f, 1.0f, 0.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_fovy(DirectX::XMConvertToRadians(60.0f))
	, m_aspect(ASPECT)
	, m_near(0.1f)
	, m_far(100.0f)
	, m_radY(2.0f)
	, m_radXZ(2.0f)
	, m_rad(4.0f)
{
}

//=====�]�u�ς݃r���[�s��̎擾=====
DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{	
	//---�i�[�ꏊ����
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	
	//---�v�f����
	DirectX::XMVECTOR eye	= DirectX::XMVectorSet(m_pos.x , m_pos.y, m_pos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);
	DirectX::XMVECTOR up	= DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	
	//---�i�[
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	
	//---�]�u
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====�]�u�ς݃v���W�F�N�V�����s��̎擾=====
DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	//---�i�[�ꏊ����
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;

	//---�i�[
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	
	//---�]�u
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

//=====�]�u�O�r���[�s��̎擾=====
DirectX::XMFLOAT4X4 CameraBase::GetNPViewMatrix()
{	
	//---�i�[�ꏊ����
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	
	//---�v�f����
	DirectX::XMVECTOR eye	= DirectX::XMVectorSet(m_pos.x , m_pos.y, m_pos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);
	DirectX::XMVECTOR up	= DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	
	//---�i�[
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====�]�u�O�v���W�F�N�V�����s��̎擾=====
DirectX::XMFLOAT4X4 CameraBase::GetNPProjectionMatrix()
{
	//---�i�[�ꏊ����
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;

	//---�i�[
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

DirectX::XMFLOAT3 CameraBase::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 CameraBase::GetLook()
{
	return m_look;
}
