#include "Leaf.h"
#include "Player.h"
#include "Object.h"

Leaf::Leaf()
	:efkHandle{0}
{
	effect = LibEffekseer::Create("Assets/Effect/Glass.efkefc");
}

Leaf::~Leaf()
{
}

void Leaf::Play(Object* pObj, int i)
{
		if (pObj->GetKind() == Object::TREE && pObj->IsShake())
		{
			if (LibEffekseer::GetManager().Get()->GetInstanceCount(efkHandle[i]) < 1) {
			efkHandle[i] = LibEffekseer::GetManager()->Play(effect, pObj->GetPos().x, pObj->GetPos().y - 3.0f, pObj->GetPos().z);				// 再生
			LibEffekseer::GetManager().Get()->SetScale(efkHandle[i], 0.8f, 0.9f, 0.9f);							// サイズ変更
			//LibEffekseer::GetManager().Get()->SetSpeed(efkHandle[efkNum], 4);											// 再生速度変更
			LibEffekseer::GetManager().Get()->SetAllColor(efkHandle[i], ::Effekseer::Color(255, 255, 255, 255));	// 色変更
		}
	}
}

void Leaf::Draw()
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

void Leaf::SetObject(list<Object*>* pObj)
{
	m_pObjectlist = pObj;
}

void Leaf::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}
