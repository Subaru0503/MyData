#include "TSuction.h"

TSuction::TSuction()
	:efkHandle(0)
{
	effect = LibEffekseer::Create("Assets/Effect/Storm.efkefc");
}

TSuction::~TSuction()
{
}

void TSuction::Update()
{
	if (LibEffekseer::GetManager().Get()->GetInstanceCount(efkHandle) < 1) {
		efkHandle = LibEffekseer::GetManager()->Play(effect, 0.0f, -1.0f, 0.0f);				// �Đ�
		LibEffekseer::GetManager().Get()->SetScale(efkHandle, 1.5f, 1.0f, 1.0f);							// �T�C�Y�ύX
		LibEffekseer::GetManager().Get()->SetSpeed(efkHandle, 1);											// �Đ����x�ύX
		LibEffekseer::GetManager().Get()->SetAllColor(efkHandle, ::Effekseer::Color(255, 255, 255, 100));	// �F�ύX
	}
}

void TSuction::Draw()
{
		//---�i�[�ꏊ����
		DirectX::XMFLOAT4X4 mat[2];
		DirectX::XMMATRIX view;

		//---�v�f����
		DirectX::XMVECTOR eye = DirectX::XMVectorSet(-20.0f, 2.0f, 10.5f, 0.0f);
		DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//---�i�[
		view = DirectX::XMMatrixLookAtLH(eye, focus, up);
		DirectX::XMStoreFloat4x4(&mat[0], view);


		//---�i�[�ꏊ����
		DirectX::XMMATRIX proj;

		//---�i�[
		proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
		DirectX::XMStoreFloat4x4(&mat[1], proj);

	LibEffekseer::SetViewPosition(DirectX::XMFLOAT3(-20.0f, 2.0f, 10.5f));
	LibEffekseer::SetCameraMatrix(mat[0], mat[1]);
}

void TSuction::Stop()
{
	LibEffekseer::GetManager().Get()->StopEffect(efkHandle);	// ��~
}

