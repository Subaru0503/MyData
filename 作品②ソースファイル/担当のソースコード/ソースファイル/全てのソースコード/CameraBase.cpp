//CameraBase.cpp
//=====インクルード部=====
#include "CameraBase.h"

#define ASPECT	(16.0f / 9.0f)

//=====コンストラクタ=====
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

//=====転置済みビュー行列の取得=====
DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{	
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	
	//---要素準備
	DirectX::XMVECTOR eye	= DirectX::XMVectorSet(m_pos.x , m_pos.y, m_pos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);
	DirectX::XMVECTOR up	= DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	
	//---格納
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	
	//---転置
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====転置済みプロジェクション行列の取得=====
DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;

	//---格納
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
	
	//---転置
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&mat, proj);

	return mat;
}

//=====転置前ビュー行列の取得=====
DirectX::XMFLOAT4X4 CameraBase::GetNPViewMatrix()
{	
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	
	//---要素準備
	DirectX::XMVECTOR eye	= DirectX::XMVectorSet(m_pos.x , m_pos.y, m_pos.z, 0.0f);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f);
	DirectX::XMVECTOR up	= DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);
	
	//---格納
	view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	DirectX::XMStoreFloat4x4(&mat, view);

	return mat;
}

//=====転置前プロジェクション行列の取得=====
DirectX::XMFLOAT4X4 CameraBase::GetNPProjectionMatrix()
{
	//---格納場所準備
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;

	//---格納
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
