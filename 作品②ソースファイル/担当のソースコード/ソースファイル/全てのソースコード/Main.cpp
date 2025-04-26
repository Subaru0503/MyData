//Main.cpp
//=====インクルード部=====
#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneGame.h"
#include "Defines.h"
#include "Rubbish.h"
#include "Sound.h"
#include "LibEffekseer.h"
#include "ShaderList.h"

//=====グローバル変数=====
CSceneMng* g_pScene;
bool g_GameEnd;			// ゲームループ用

//=====初期化処理=====
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	InitSound();
	Geometory::Init();
	Sprite::Init();
	ShaderList::Init();
	LibEffekseer::Init(GetDevice(), GetContext(), nullptr);
	InitInput();

	// シーン作成
	g_pScene = new CSceneMng();

	// ジオメトリ用カメラ初期化
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
	));
	Geometory::SetView(mat[0]);
	Geometory::SetProjection(mat[1]);


	return hr;
}

//=====終了処理=====
void Uninit()
{
	if(g_pScene) delete g_pScene;
	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	ShaderList::Uninit();
	LibEffekseer::Uninit();
	UninitSound();
	UninitDirectX();
}

//=====更新処理=====
void Update(float tick)
{
	UpdateInput();
	if (IsKeyPress(VK_ESCAPE) && IsKeyPress('R') && IsKeyPress('L')) {
		delete g_pScene;
		g_pScene = new CSceneMng();
	}
	if (g_pScene) g_pScene->Update(tick);
	g_GameEnd = g_pScene->GetGameEnd();
}

//=====描画処理=====
void Draw()
{
	BeginDrawDirectX();

	// 軸線の表示
#ifdef _DEBUGoff
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
	}
	// 軸
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	Geometory::DrawLines();
#endif

	if (g_pScene) g_pScene->Draw();
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);
	LibEffekseer::Draw();
	SetRenderTargets(1, &pRTV, nullptr);
	EndDrawDirectX();
}

bool GetGameEnd()
{
	return g_GameEnd;
}

// EOF