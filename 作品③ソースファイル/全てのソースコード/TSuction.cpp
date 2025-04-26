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
		efkHandle = LibEffekseer::GetManager()->Play(effect, 0.0f, -1.0f, 0.0f);				// çƒê∂
		LibEffekseer::GetManager().Get()->SetScale(efkHandle, 1.5f, 1.0f, 1.0f);							// ÉTÉCÉYïœçX
		LibEffekseer::GetManager().Get()->SetSpeed(efkHandle, 1);											// çƒê∂ë¨ìxïœçX
		LibEffekseer::GetManager().Get()->SetAllColor(efkHandle, ::Effekseer::Color(255, 255, 255, 100));	// êFïœçX
	}
}

void TSuction::Draw()
{
		//---äiî[èÍèäèÄîı
		DirectX::XMFLOAT4X4 mat[2];
		DirectX::XMMATRIX view;

		//---óvëfèÄîı
		DirectX::XMVECTOR eye = DirectX::XMVectorSet(-20.0f, 2.0f, 10.5f, 0.0f);
		DirectX::XMVECTOR focus = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//---äiî[
		view = DirectX::XMMatrixLookAtLH(eye, focus, up);
		DirectX::XMStoreFloat4x4(&mat[0], view);


		//---äiî[èÍèäèÄîı
		DirectX::XMMATRIX proj;

		//---äiî[
		proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
		DirectX::XMStoreFloat4x4(&mat[1], proj);

	LibEffekseer::SetViewPosition(DirectX::XMFLOAT3(-20.0f, 2.0f, 10.5f));
	LibEffekseer::SetCameraMatrix(mat[0], mat[1]);
}

void TSuction::Stop()
{
	LibEffekseer::GetManager().Get()->StopEffect(efkHandle);	// í‚é~
}

