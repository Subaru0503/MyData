#include "EStun.h"
#include "Player.h"
EStun::EStun()
{
	effect = LibEffekseer::Create("Assets/Effect/kemuri.efkefc");
}

EStun::~EStun()
{

}

void EStun::Update()
{
	if (LibEffekseer::GetManager().Get()->GetInstanceCount(efkHandle) < 1) {
		efkHandle = LibEffekseer::GetManager()->Play(effect, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetPos().z);				// 再生
		LibEffekseer::GetManager().Get()->SetScale(efkHandle, 0.2f, 0.2f, 0.2f);							// サイズ変更
		LibEffekseer::GetManager().Get()->SetSpeed(efkHandle, 4);											// 再生速度変更
		LibEffekseer::GetManager().Get()->SetAllColor(efkHandle, ::Effekseer::Color(255, 255, 255, 100));	// 色変更
	}
	LibEffekseer::GetManager().Get()->SetLocation(efkHandle, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y + 0.5f, m_pPlayer->GetPos().z);
	LibEffekseer::GetManager().Get()->SetRotation(efkHandle, 0.0f, m_pPlayer->GetRad() + DirectX::XMConvertToRadians(180), 0.0f);
}

void EStun::Draw()
{
	DirectX::XMFLOAT4X4 efkMat[3];

	DirectX::XMStoreFloat4x4(&efkMat[0],
		DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f)/*
		DirectX::XMMatrixTranslation(0.0f,-5.0f,0.0f)*/));
	efkMat[1] = m_pPlayer->GetNViewMatrix();
	efkMat[2] = m_pPlayer->GetNProjectionMatrix();

	LibEffekseer::SetViewPosition(m_pPlayer->GetPos());
	LibEffekseer::SetCameraMatrix(efkMat[1], efkMat[2]);
}

void EStun::Stop()
{
	LibEffekseer::GetManager().Get()->StopEffect(efkHandle);	// 停止
}

void EStun::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}
