#include "MoveLight.h"
#include <algorithm>
#include "Input.h"
#include "Light.h"

MoveLight::MoveLight()
	: GameObject("MoveLight")
	, m_pComponent(AddComponent<Light>())
{
	m_pComponent->SetRange(40.0f);

	//float rotXZ = 0.0f;

	//rotXZ = DirectX::XMConvertToRadians(10.0f);

	//DirectX::XMVECTOR quat = DirectX::XMLoadFloat4(&m_quat);
	//DirectX::XMVECTOR axisXZ = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	//axisXZ = DirectX::XMVector3Rotate(axisXZ, quat);
	//DirectX::XMVECTOR quatXZ = DirectX::XMQuaternionRotationAxis(
	//	axisXZ, rotXZ
	//);
	//quat = DirectX::XMQuaternionMultiply(quat, quatXZ);

	//DirectX::XMStoreFloat4(&m_quat, quat);
}
MoveLight::~MoveLight()
{
}

void MoveLight::Update()
{
	if (IsKeyPress('L'))
	{

		constexpr float rotSpeed = DirectX::XMConvertToRadians(360.0f / (2.0f * 60)); // 2•b‚Å1‰ñ“]
		float rotY = 0.0f;
		float rotXZ = 0.0f;
		if (IsKeyPress('A')) { rotY += rotSpeed; }
		if (IsKeyPress('D')) { rotY -= rotSpeed; }
		if (IsKeyPress('W')) { rotXZ += rotSpeed; }
		if (IsKeyPress('S')) { rotXZ -= rotSpeed; }

		DirectX::XMVECTOR quat = DirectX::XMLoadFloat4(&m_quat);
		DirectX::XMVECTOR quatY = DirectX::XMQuaternionRotationAxis(
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotY
		);
		quat = DirectX::XMQuaternionMultiply(quat, quatY);

		DirectX::XMVECTOR axisXZ = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		axisXZ = DirectX::XMVector3Rotate(axisXZ, quat);
		DirectX::XMVECTOR quatXZ = DirectX::XMQuaternionRotationAxis(
			axisXZ, rotXZ
		);
		quat = DirectX::XMQuaternionMultiply(quat, quatXZ);

		DirectX::XMStoreFloat4(&m_quat, quat);
	}

	DirectX::XMFLOAT3 front = GetFront();
	DirectX::XMVECTOR vFront = DirectX::XMLoadFloat3(&front);
	DirectX::XMVECTOR vPos = DirectX::XMVectorScale(vFront, -m_pComponent->GetRange());
	DirectX::XMStoreFloat3(&m_pos, vPos);

}