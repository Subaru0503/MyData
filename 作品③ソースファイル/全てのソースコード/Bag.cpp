#include "Bag.h"
#include "Player.h"
#include "Object.h"
EBag::EBag()
	:efkHandle(0)
{
	effect = LibEffekseer::Create("Assets/Effect/KiraKira.efkefc");
}

EBag::~EBag()
{
}

void EBag::Play(Object * pObj)
{
	if (pObj->GetDelete())
	{
		efkHandle = LibEffekseer::GetManager()->Play(effect, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y -0.01f, m_pPlayer->GetPos().z - 0.2f);				// 再生
		LibEffekseer::GetManager().Get()->SetScale(efkHandle, 0.4f, 0.2f, 0.4f);							// サイズ変更
		LibEffekseer::GetManager().Get()->SetSpeed(efkHandle, 4);											// 再生速度変更
		LibEffekseer::GetManager().Get()->SetAllColor(efkHandle, ::Effekseer::Color(255, 255, 0, 255));	// 色変更
		LibEffekseer::GetManager().Get()->SetLocation(efkHandle, m_pPlayer->GetPos().x, m_pPlayer->GetPos().y + 0.5f, m_pPlayer->GetPos().z);
		LibEffekseer::GetManager().Get()->SetRotation(efkHandle, 0.0f, m_pPlayer->GetRad() + DirectX::XMConvertToRadians(180), 0.0f);
	}
}

void EBag::Draw()
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

void EBag::SetObject(list<Object*>* pObj)
{
	m_pObjectlist = pObj;
}

void EBag::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}
