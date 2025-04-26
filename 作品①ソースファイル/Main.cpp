#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneRoot.h"
#include "DebugMenu.h"

#include <crtdbg.h>

// �}�l�[�W���[
#include "SoundManager.h"	// �T�E���h�}�l�[�W���[

//--- �O���[�o���ϐ�
std::shared_ptr<SceneRoot> g_pScene;

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	// �v���O�����I�����Ƀ��������[�N��
	// �`�F�b�N����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HRESULT hr;

	// DirectX������
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	// �e�@�\������
	Geometory::Init();
	Sprite::Init();
	InitInput();
	// ���ǂݍ���
	SoundManager::GetInstance().SoundLoad();
#ifdef _DEBUG
	debug::Menu::Init();
	// �w�i�F
	debug::Item* color = debug::Item::CreateValue("AmbientColor", debug::Item::Color, true);
	debug::Menu::Create("00_Info").AddItem(color);
#endif
	// �V�[���쐬
	SceneBase::Initialize();
	g_pScene = std::make_shared<SceneRoot>();
	g_pScene->Init();

	// �������\�[�X�쐬
	auto rtv = g_pScene->CreateObj<RenderTarget>("RTV");
	rtv->CreateFromScreen();
	auto dsv = g_pScene->CreateObj<DepthStencil>("DSV");
	hr = dsv->Create(width, height, false);

	SetRenderTargets(1, &rtv, dsv);

	return hr;
}

void Uninit()
{
#ifdef _DEBUG
	debug::Menu::Uninit();
#endif

	g_pScene->Uninit();
	g_pScene.reset();
	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	UninitDirectX();
}

void Update(float tick)
{
#ifdef _DEBUG
	debug::Menu::Update();
#endif
	UpdateInput();
	g_pScene->_update(tick);
}

void Draw()
{
	auto rtv = g_pScene->GetObj<RenderTarget>("RTV");
	auto dsv = g_pScene->GetObj<DepthStencil>("DSV");
	float color[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
#ifdef _DEBUG
	DirectX::XMFLOAT4 ambient = debug::Menu::Get("00_Info")["AmbientColor"].GetColor();
	color[0] = ambient.x;
	color[1] = ambient.y;
	color[2] = ambient.z;
	color[3] = ambient.w;
#endif
	GetContext()->ClearRenderTargetView(rtv->GetView(), color);
	GetContext()->ClearDepthStencilView(dsv->GetView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	g_pScene->_draw();
#ifdef _DEBUG
	debug::Menu::Draw();
#endif

	SwapDirectX();
}

// EOF