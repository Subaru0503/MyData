#include "DustCloud.h"
#include "Player.h"
#include "Object.h"
#include "ObjectManager.h"
Dust::Dust()
	:efkHandle(0)
	,efkNum(0)
{
	effect = LibEffekseer::Create("Assets/Effect/HokoriMini.efkefc");
}

Dust::~Dust()
{
}

void Dust::Update()
{/*
	for (Effekseer::Handle Handle : efkHandle)
	{
		LibEffekseer::GetManager().Get()->SetLocation(Handle, m_pObject->GetPos().x, m_pObject->GetPos().y, m_pObject->GetPos().z);
	}*/
}

void Dust::Play()
{
	for (Object* pObject : *m_pObjectlist)
	{
		if (pObject->GetEfkDestory())
		{
			efkHandle.push_back(LibEffekseer::GetManager()->Play(effect, pObject->GetPos().x, pObject->GetPos().y, pObject->GetPos().z));				// 再生
			LibEffekseer::GetManager().Get()->SetScale(efkHandle[efkNum], 1.0f, 1.0f, 1.0f);							// サイズ変更
			//LibEffekseer::GetManager().Get()->SetSpeed(efkHandle[efkNum], 4);											// 再生速度変更
			LibEffekseer::GetManager().Get()->SetAllColor(efkHandle[efkNum], ::Effekseer::Color(255, 255, 255, 255));	// 
			efkNum++;
			pObject->SetEfkDestory(false);
		}
	}
}

void Dust::Draw()
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

void Dust::SetObject(list<Object*>* pObj)
{
	m_pObjectlist = pObj;
}

void Dust::SetPlayer(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}