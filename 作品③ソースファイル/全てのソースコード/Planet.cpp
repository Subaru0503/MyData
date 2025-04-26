// Planet.cpp

//=====インクルード=====
#include "Planet.h"
#include "Geometory.h"

/**********************
*@brief コンストラクタ
***********************/
Planet::Planet()
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_rotate(0.0f, 0.0f, 0.0f)
	, m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_bFocus(false)
{
}

/*********************
*@brief デストラクタ
*********************/
Planet::~Planet()
{
	// メモリ未解放であれば解放
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

void Planet::Update(float tick)
{
	if (m_bFocus)
	{
		m_rotate.y += 30.0f * tick;
	}
}

void Planet::Draw(DirectX::XMFLOAT4X4* mat)
{
	DirectX::XMMATRIX world;
	// ワールド行列の計算
	world = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	world = DirectX::XMMatrixTranspose(world);	// シェーダーに渡す用にワールド行列を転置

	DirectX::XMStoreFloat4x4(&mat[0], world);	// シェーダーに渡すデータにワールド行列を変換してセット

	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	RenderTarget* pRTV = GetDefaultRTV();	// デフォのレンダーターゲットビューを取得
	DepthStencil* pDSV = GetDefaultDSV();	// デフォのデプスステンシルビューを取得
	SetRenderTargets(1, &pRTV, pDSV);		// レンダーターゲットの1番にセット

	m_pVS->WriteBuffer(0, mat);	// 座標変換行列を頂点シェーダーの定数バッファにコピー
	m_pModel->Draw();			// モデルを描画
}

DirectX::XMFLOAT3 Planet::GetPos()
{
	return m_pos;
}

void Planet::StartFocus()
{
	m_bFocus = true;
}

void Planet::EndFocus()
{
	m_bFocus = false;
}
