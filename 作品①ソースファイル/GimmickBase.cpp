// �M�~�b�N���N���X

// �C���N���[�h��
#include "GimmickBase.h"

// �V�X�e��
#include "Input.h"

// �R���X�g���N�^
GimmickBase::GimmickBase(std::string name)
	: GameObject(name)
	, m_PairGimmick(nullptr)
	, m_invertEffectFlg(false)
	, m_CollisionUpdate(false)
	, m_GroundCollision(false)
{
	m_tag = "Gimmick";

	// �R���|�[�l���g�ǉ�
	AddComponent<BoxCollider>();		// �����蔻��
	AddComponent<ModelRenderer3D>();	// 3D�`��

	// �R���|�[�l���g�擾
	_boxCollider = GetComponent<BoxCollider>();
	_modelRenderer3D = GetComponent<ModelRenderer3D>();

	// �V�F�[�_�[�Z�b�g
	const char* file[] = {
		"VS_Object",
		"PS_TexColor",
	};

	_modelRenderer3D->SetShader(file);
}

// �f�X�g���N�^
GimmickBase::~GimmickBase()
{
}

// �X�V����
void GimmickBase::Update()
{
	for (int i = 0; i < m_TargetScrew.size(); i++)
	{
		// ���݂̊p�x�擾
		float rotY;
		DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_TargetScrew[i]->GetQuat());
		DirectX::XMMATRIX quaternionM = DirectX::XMMatrixRotationQuaternion(qRotate);
		// Yaw (Y����])
		rotY = DirectX::XMConvertToDegrees(atan2(quaternionM.r[0].m128_f32[2], quaternionM.r[2].m128_f32[2]));


		// �ς���ĂȂ������珈�������Ȃ�
		// �v���C���[����]�������ĂȂ������珈�����Ȃ�
		if (m_OldRotY[i] == rotY) continue;

		// ���ʔ��]�t���O���������Ă�����
		// �ߋ��p�x���l���������Ȃ��Ă�����d
		if ((m_OldRotY[i] < rotY && !m_invertEffectFlg) ||
			(m_OldRotY[i] > rotY && m_invertEffectFlg))
		{
			float rot = abs(rotY - m_OldRotY[i]);
			// �M�~�b�N����
			Gimmick(i, rot);
		}
		else
		{
			float rot = abs(rotY - m_OldRotY[i]);

			InvertGimmick(i, rot);
		}

		m_OldRotY[i] = rotY;	// �p�x���X�V
	}


	m_CollisionUpdate = false;
}

// �^�[�Q�b�g�I�u�W�F�N�g����
void GimmickBase::Gimmick(int index, float rotY)
{
}

// �ʏ�̃l�W���񂷕����Ƌt�����ɉ񂳂ꂽ�Ƃ��ɌĂ�
void GimmickBase::InvertGimmick(int index, float rotY)
{
}

 // �Փ˂����I�u�W�F�N�g
void GimmickBase::OnCollision(GameObject* obj)
{
	// �������ĂȂ������珈�����Ȃ�
	if (!obj)
	{
		// �t���O���Z�b�g
		m_GroundCollision = false;
		return;
	}
	string tag = obj->GetTag();
	if (tag == "Ground")
	{
		m_GroundCollision = true;
		m_CollisionUpdate = true;
	}
	else if(!m_CollisionUpdate)
	{
		// �t���O���Z�b�g
		m_GroundCollision = false;
	}
}