#include "CameraDCC.h"
#include "Input.h"
#include "DebugMenu.h"
#include <algorithm>

//----データ型----
#include "float3.h"

//enum CameraDCCKind
//{
//	CAM_DCC_NONE,
//	CAM_DCC_ORBIT,
//	CAM_DCC_TRACK,
//	CAM_DCC_DOLLY,
//	CAM_DCC_FLIGHT,
//};

CameraDCC::CameraDCC()
	: GameObject("CameraDCC")
	//, m_state(CAM_DCC_NONE)
	, m_oldPos{ 0, 0 }
	, m_pComponent(AddComponent<Camera>())
	, m_target(nullptr)
{
//#ifdef _DEBUG
//	auto& window = debug::Menu::Get("00_Info");
//	debug::Item* group = debug::Item::CreateGroup("Camera");
//	group->AddGroupItem(debug::Item::CreateValue("Speed", debug::Item::Float, true));
//	group->AddGroupItem(debug::Item::CreateValue("FlipMouseX", debug::Item::Bool, true));
//	group->AddGroupItem(debug::Item::CreateValue("FlipMouseY", debug::Item::Bool, true));
//	window.AddItem(group);
//#endif
}
CameraDCC::~CameraDCC()
{
}
void CameraDCC::Update()
{
	UpdateState();
//	if (m_state == CAM_DCC_NONE) return;
//
//
//	Argument arg;
//	// マウス移動量
//	POINT cursorPos;
//	GetCursorPos(&cursorPos);
//	arg.mouseMove = DirectX::XMFLOAT2((float)cursorPos.x - m_oldPos.x, (float)cursorPos.y - m_oldPos.y);
//#ifdef _DEBUG
//	auto& window = debug::Menu::Get("00_Info");
//	arg.mouseMove.x *= window["Camera"]["FlipMouseX"].GetBool() ? -1.0f : 1.0f;
//	arg.mouseMove.y *= window["Camera"]["FlipMouseY"].GetBool() ? -1.0f : 1.0f;
//#endif
//	m_oldPos = cursorPos;
//	// カメラ情報
//	DirectX::XMFLOAT3 front = GetFront();
//	DirectX::XMFLOAT3 side = GetRight();
//	DirectX::XMFLOAT3 up(0.0f, 1.0f, 0.0f);
//	DirectX::XMFLOAT3 look = m_pComponent->GetLook();
//	arg.vCamFront	= DirectX::XMLoadFloat3(&front);
//	arg.vCamSide	= DirectX::XMLoadFloat3(&side);
//	arg.vCamPos		= DirectX::XMLoadFloat3(&m_pos);
//	arg.vCamLook	= DirectX::XMLoadFloat3(&look);
//	arg.vCamUp		= DirectX::XMVector3Normalize(DirectX::XMVector3Cross(arg.vCamFront, arg.vCamSide));
//
//	switch (m_state)
//	{
	//case CAM_DCC_ORBIT:		UpdateOrbit(arg);	break;
	//case CAM_DCC_TRACK:		UpdateTrack(arg);	break;
	//case CAM_DCC_DOLLY:		UpdateDolly(arg);	break;
	//case CAM_DCC_FLIGHT:	UpdateFlight(arg);	break;
	//}
}

void CameraDCC::UpdateState()
{
	//CameraDCCKind prev = (CameraDCCKind)m_state;
	//if (IsKeyPress(VK_MENU))
	//{
	//	m_state = CAM_DCC_NONE;
	//	if (IsKeyPress(VK_LBUTTON)) m_state = CAM_DCC_ORBIT;
	//	if (IsKeyPress(VK_MBUTTON)) m_state = CAM_DCC_TRACK;
	//	if (IsKeyPress(VK_RBUTTON)) m_state = CAM_DCC_DOLLY;
	//}
	//else if (IsKeyPress(VK_RBUTTON))
	//{
	//	m_state = CAM_DCC_FLIGHT;
	//}
	//else
	//{
	//	m_state = CAM_DCC_NONE;
	//}
	//if (prev != m_state)
	//{
	//	GetCursorPos(&m_oldPos);
	//}
	if (!m_target) return;

	Camera* pCamera = GetComponent<Camera>();
	float3 targetPos = float3::Tofloat3(m_target->GetPos());
	float3 camPos = float3::Tofloat3(m_pos);

	camPos = targetPos;
	camPos.y = targetPos.y + 10.0f;
	camPos.z = targetPos.z - 10.0f;

	float focus = float3::distance(targetPos, camPos);

	SetPos(float3::ToXMFLOAT3(camPos));
	pCamera->SetFocus(focus);
}

// カメラ座標初期設定
void CameraDCC::CamInitSetPos()
{
	Camera* pCamera = GetComponent<Camera>();
	float3 targetPos = float3::Tofloat3(m_target->GetPos());
	float3 camPos = float3::Tofloat3(m_pos);

	camPos = targetPos;
	camPos.y = targetPos.y + 10.0f;
	camPos.z = targetPos.z - 10.0f;

	float focus = float3::distance(targetPos, camPos);

	SetPos(float3::ToXMFLOAT3(camPos));
	pCamera->SetFocus(focus);
}

//void CameraDCC::UpdateOrbit(Argument& arg)
//{
//	// マウスの移動量 / 画面サイズ の比率から、画面全体でどれだけ回転するか指定する。
//	float angleX =  360.0f * arg.mouseMove.x / 1280.0f;
//	float angleY =  180.0f * arg.mouseMove.y / 720.0f;
//
//	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
//		DirectX::XMVectorSet(0, 1, 0, 0), DirectX::XMConvertToRadians(angleX)
//	);
//	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
//	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
//
//	DirectX::XMVECTOR vAxisX = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//	vAxisX = DirectX::XMVector3Rotate(vAxisX, qRotate);
//	quat = DirectX::XMQuaternionRotationAxis(vAxisX, DirectX::XMConvertToRadians(angleY));
//	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
//
//	DirectX::XMStoreFloat4(&m_quat, qRotate);
//
//	// 注視点からカメラの後方へフォーカス距離だけ移動させる
//	DirectX::XMFLOAT3 dir = GetFront();
//	DirectX::XMVECTOR vDir = DirectX::XMLoadFloat3(&dir);
//	vDir = DirectX::XMVectorScale(vDir, -m_pComponent->GetFocus());
//	DirectX::XMVECTOR vPos = DirectX::XMVectorAdd(arg.vCamLook, vDir);
//	DirectX::XMStoreFloat3(&m_pos, vPos);
//}
//void CameraDCC::UpdateTrack(Argument& arg)
//{
//	float fClip = m_pComponent->GetFar();
//
//	// 高さA、底辺Bとする三角形について tanΘ = A / Bが成り立つ
//	// 上記式をもとに割り出した遠景の高さを、移動量 / 画面サイズ の比率から、移動量として求める
//	float width = m_pComponent->GetFovy();
//	float farScreenHeight = tanf(width * 0.5f) * fClip;
//	float screenRateW = arg.mouseMove.x / 640.0f;
//	float screenRateH = arg.mouseMove.y / 360.0f;
//	float farMoveX = -farScreenHeight * screenRateW * m_pComponent->GetAspect();
//	float farMoveY = farScreenHeight * screenRateH;
//
//	// カメラの姿勢をもとに移動
//	float rate = m_pComponent->GetFocus() / fClip;
//	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
//	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamSide, farMoveX * rate));
//	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamUp, farMoveY * rate));
//	DirectX::XMStoreFloat3(&m_pos, DirectX::XMVectorAdd(arg.vCamPos, vCamMove));
//}
//void CameraDCC::UpdateDolly(Argument& arg)
//{
//	float focus = m_pComponent->GetFocus();
//	float fClip = m_pComponent->GetFar();
//	float nClip = m_pComponent->GetNear();
//
//	// フォーカス位置とクリップ面の位置に応じて補正移動量を計算
//	float clipDistance = fClip - nClip;
//	float rate = (focus - nClip) / clipDistance;
//
//	// 移動量
//	float move = rate * (arg.mouseMove.x + arg.mouseMove.y) * fClip * 0.01f;
//	focus = std::min(fClip, std::max(nClip, focus - move));
//
//	// カメラ位置更新
//	DirectX::XMVECTOR vMove = DirectX::XMVectorScale(arg.vCamFront, -focus);
//	DirectX::XMStoreFloat3(&m_pos, DirectX::XMVectorAdd(arg.vCamLook, vMove));
//	m_pComponent->SetFocus(focus);
//}
//void CameraDCC::UpdateFlight(Argument& arg)
//{
//	// マウスの移動量 / 画面サイズ の比率から、画面全体でどれだけ回転するか指定する。
//	float angleX = 360.0f * arg.mouseMove.x / 1280.0f;
//	float angleY = 180.0f * arg.mouseMove.y / 720.0f;
//
//	// 横回転
//	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
//	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(
//		arg.vCamUp, DirectX::XMConvertToRadians(angleX)
//	);
//	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
//
//	// 縦回転
//	DirectX::XMVECTOR vAxis = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
//	vAxis = DirectX::XMVector3Rotate(vAxis, qRotate);
//	quat = DirectX::XMQuaternionRotationAxis(vAxis, DirectX::XMConvertToRadians(angleY));
//	qRotate = DirectX::XMQuaternionMultiply(qRotate, quat);
//
//	// 回転の更新
//	DirectX::XMStoreFloat4(&m_quat, qRotate);
//	
//	// 軸の取得
//	DirectX::XMFLOAT3 front = GetFront();
//	DirectX::XMFLOAT3 side = GetRight();
//	arg.vCamFront = DirectX::XMLoadFloat3(&front);
//	arg.vCamSide = DirectX::XMLoadFloat3(&side);
//
//	// キー入力で移動
//	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
//	if (IsKeyPress('W')) vCamMove = DirectX::XMVectorAdd(vCamMove, arg.vCamFront);
//	if (IsKeyPress('S')) vCamMove = DirectX::XMVectorSubtract(vCamMove, arg.vCamFront);
//	if (IsKeyPress('A')) vCamMove = DirectX::XMVectorSubtract(vCamMove, arg.vCamSide);
//	if (IsKeyPress('D')) vCamMove = DirectX::XMVectorAdd(vCamMove, arg.vCamSide);
//	if (IsKeyPress('Q')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
//	if (IsKeyPress('E')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f,-1.0f, 0.0f, 0.0f));
//	vCamMove = DirectX::XMVectorScale(vCamMove, m_pComponent->GetFar() * 0.0001f);
//
//	// 更新
//	DirectX::XMVECTOR vCamPos = DirectX::XMVectorAdd(arg.vCamPos, vCamMove);
//	DirectX::XMStoreFloat3(&m_pos, vCamPos);
//}