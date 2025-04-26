#include "ESuction.h"
#include "Player.h"

ESuction::ESuction()
	:RadXZ(2.0f)
	, efkHandle(0)
	, scalex(0.3f)
	, scalez(0.2)
{
	effect = LibEffekseer::Create("Assets/Effect/Storm.efkefc");
}

ESuction::~ESuction()
{

}

void ESuction::Update()
{

	if (LibEffekseer::GetManager().Get()->GetInstanceCount(efkHandle) < 1) {
		efkHandle = LibEffekseer::GetManager()->Play(effect, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y + 0.7f, m_pPlayer->GetPos().z);				// 再生
		LibEffekseer::GetManager().Get()->SetScale(efkHandle, scalex, 0.4f, scalez);
		LibEffekseer::GetManager().Get()->SetSpeed(efkHandle, 4);											// 再生速度変更
		LibEffekseer::GetManager().Get()->SetAllColor(efkHandle, ::Effekseer::Color(255, 255, 255, 100));	// 色変更
	}
	LibEffekseer::GetManager().Get()->SetLocation(efkHandle, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y + 0.5f, m_pPlayer->GetPos().z);
	LibEffekseer::GetManager().Get()->SetRotation(efkHandle, 0.0f, m_pPlayer->GetRad() + DirectX::XMConvertToRadians(180), 0.0f);
	//LibEffekseer::GetManager().Get()->AddLocation(efkHandle, ::Effekseer::Vector3D(m_pPlayer->GetMove().x, m_pPlayer->GetMove().y, m_pPlayer->GetMove().z));		// プレイヤーの移動量分エフェクト移動
	//LibEffekseer::GetManager().Get()->SetRotation(efkHandle, 3.1415 * 30.0f / 360, RadXZ, 0.0f);	// エフェクトを常に正面に向ける
}

void ESuction::Stop()
{
   	LibEffekseer::GetManager().Get()->StopEffect(efkHandle);	// 停止
}

void ESuction::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}

void ESuction::SetScale()
{
	scalex += 0.3;
	scalez += 0.1;
}

void ESuction::Draw()
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