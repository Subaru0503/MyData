#include "GameObject.hpp"
#include "Component.h"
#include <typeinfo>
#include <algorithm>

/*
* @brief �R���X�g���N�^
* @param[in] name �I�u�W�F�N�g��
*/
GameObject::GameObject(std::string name)
	: m_name(name)
	, m_pos{}, m_quat{0.0f, 0.0f, 0.0f, 1.0f}, m_scale{1.0f, 1.0f, 1.0f}
	, m_2DObjNo(0)
	, m_3DObjNo(0)
	//, m_DirectRad(0.0f)
	, m_OnMoveFloor(false)
{
	// �I�u�W�F�N�g���ɉ����āA�ۑ��t�@�C���̓ǂݍ���
	std::string path = "Assets/GameObject/" + m_name + ".dat";
	FILE* fp;
	fopen_s(&fp, path.c_str(), "rb");
	if (fp) {
		// �t�@�C���ꊇ�ǂݍ���
		fseek(fp, 0, SEEK_END);
		long fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* ptr = new char[fileSize];
		fread(ptr, fileSize, 1, fp);
		m_datas.push_back({"data", ptr}); // �ꊇ�œǂݍ��񂾃f�[�^��ۑ�
		fclose(fp);

		// �Q�[���I�u�W�F�N�g���̃f�[�^�̓ǂݍ���
		memcpy(&m_pos, ptr, sizeof(m_pos));
		memcpy(&m_quat, ptr += sizeof(m_pos), sizeof(m_quat));
		memcpy(&m_scale, ptr += sizeof(m_quat), sizeof(m_scale));
		ptr += sizeof(m_scale);
		// �f�[�^�̃L�[�ƒl���ۑ�����Ă�����ւ̃|�C���^���擾
		while (ptr - m_datas[0].value < fileSize)
		{
			char* data[2]; // �L�[,�l
			size_t size;
			for (int i = 0; i < 2; ++i)
			{
				// �f�[�^�T�C�Y
				size = *reinterpret_cast<size_t*>(ptr);
				ptr += sizeof(size);
				// �f�[�^
				data[i] = ptr;
				ptr += size;
			}
			m_datas.push_back({ data[0], data[1] });
		}
	}
}

/*
* @brief �f�X�g���N�^
*/
GameObject::~GameObject()
{
	// �ۑ��f�[�^�̍폜
	if(!m_datas.empty())
		delete[] m_datas[0].value;

	auto it = m_components.begin();

#ifdef _DEBUG
	// �f�[�^�̕ۑ�
	std::string path = "Assets/GameObject/" + m_name + ".dat";
	FILE* fp;
	fopen_s(&fp, path.c_str(), "wb");
	if (fp)
	{
		// �Q�[���I�u�W�F�N�g�̃f�[�^��ۑ�
		fwrite(&m_pos, sizeof(m_pos), 1, fp);
		fwrite(&m_quat, sizeof(m_quat), 1, fp);
		fwrite(&m_scale, sizeof(m_scale), 1, fp);

		// �R���|�[�l���g�̃f�[�^��ۑ�
		it = m_components.begin();
		while (it != m_components.end())
		{
			const char* name = typeid(**it).name();
			Component::DataAccessor accessor(nullptr);
			(*it)->ReadWrite(&accessor);
			// �f�[�^�̃L�[��ۑ�
			size_t size = strlen(name);
			fwrite(&size, sizeof(size), 1, fp);
			fwrite(name, size, 1, fp);
			// �f�[�^�̕ۑ�
			size = accessor.GetWriteSize();
			fwrite(&size, sizeof(size), 1, fp);
			fwrite(accessor.GetData(), size, 1, fp);
			++it;
		}
		fclose(fp);
	}
#endif

	// �R���|�[�l���g�̍폜
	it = m_components.begin();
	while (it != m_components.end())
	{
		delete (*it);
		++it;
	}
}

/*
* @brief �X�V����
*/
void GameObject::Execute()
{
	// ���W�ޔ�
	m_oldpos = m_pos;

	// �R���|�[�l���g�̏���
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		(*it)->Execute();
		++it;
	}
	// �p����I�u�W�F�N�g�̏���
	Update();
}

/*
* ������Ԃɖ߂�
* �I�u�W�F�N�g���V�[�����n�܂����Ƃ��̏�Ԃɖ߂�
*/
void GameObject::ResetState()
{

}

/*
* @brief �Փ˂����I�u�W�F�N�g
*/
void GameObject::OnCollision(GameObject* obj)
{

}
/*
* @brief ���m�����I�u�W�F�N�g
*/
void GameObject::OnScanner(GameObject* obj)
{
}

#ifdef _DEBUG
/*
* @brief �C���X�y�N�^�[�ւ̕\��
* �I�����ꂽ���e��\��
*/
void GameObject::Debug(debug::Window* window)
{
	// �g�����X�t�H�[���O���[�v�̍쐬
	debug::Item* group = debug::Item::CreateGroup("Transform");
	group->AddGroupItem(debug::Item::CreateBind("Pos",		debug::Item::Vector, &m_pos));
	group->AddGroupItem(debug::Item::CreateCallBack("Rotation", debug::Item::Vector,
		[this](bool isWrite, void* arg) {
			DirectX::XMFLOAT3* pVec = static_cast<DirectX::XMFLOAT3*>(arg);
			if (isWrite) {
				DirectX::XMStoreFloat4(&m_quat,
					DirectX::XMQuaternionRotationRollPitchYaw( // zxy
						DirectX::XMConvertToRadians(pVec->x), // pitch
						DirectX::XMConvertToRadians(pVec->y), // yaw
						DirectX::XMConvertToRadians(pVec->z)) // roll
				);
			}
			else {
				// https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf
				// �N�H�[�^�j�I�� > �s��
				DirectX::XMVECTOR quat = DirectX::XMLoadFloat4(&m_quat);
				DirectX::XMFLOAT3X3 mat;
				DirectX::XMStoreFloat3x3(&mat, DirectX::XMMatrixRotationQuaternion(quat));

				// x����]�̌v�Z
				float rotX = asinf(mat._23);

				// �W���o�����b�N�̊m�F(cos(rotX) == 0�̎��ɔ���)
				bool isLock = (fabsf(rotX) == DirectX::XM_PIDIV2);

				float rotY = 0.0f;
				float rotZ = 0.0f;
				if (isLock) {
					// �W���o�����b�N����y����]�𖳎�
					rotZ = atanf(mat._12 / mat._11);
				}
				else {
					rotY = atanf(-mat._13 / mat._33);
					rotZ = atanf(-mat._21 / mat._22);
				}

				// �i�[
				pVec->x = DirectX::XMConvertToDegrees(rotX);
				pVec->y = DirectX::XMConvertToDegrees(rotY);
				pVec->z = DirectX::XMConvertToDegrees(rotZ);
			}
		}));
	group->AddGroupItem(debug::Item::CreateBind("Scale",	debug::Item::Vector, &m_scale));
	window->AddItem(group);

	// �R���|�[�l���g�̃C���X�y�N�^�[�o�^
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		(*it)->Debug(window);
		++it;
	}
}
#endif

/*
* @brief ���W�ݒ�
*/
void GameObject::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

/*
* @brief �T�C�Y�ݒ�
*/
void GameObject::SetScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

/*
* @brief ��]�ݒ�
*/
void GameObject::SetQuat(DirectX::XMFLOAT4 quat)
{
	m_quat = quat;
}

void GameObject::Set2DObjNo(int no)
{
	m_2DObjNo = no;
}

void GameObject::Set3DObjNo(int no)
{
	m_3DObjNo = no;
}

/*
* @brief �I�u�W�F�N�g�^�O�ݒ�
*/
void GameObject::SetTag(std::string tag)
{
	m_tag = tag;
}
/*
* @brief ���W�擾
*/
DirectX::XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}

/*
* @brief �ߋ����W�擾
*/
DirectX::XMFLOAT3 GameObject::GetOldPos()
{
	return m_oldpos;
}
/*
* @brief �T�C�Y�擾
*/
DirectX::XMFLOAT3 GameObject::GetScale()
{
	return m_scale;
}
/*
* @brief ��]�擾
*/
DirectX::XMFLOAT4 GameObject::GetQuat()
{
	return m_quat;
}
/*
* @brief ���[���h�s��擾
* @param[in] transpose �]�u�ݒ�
*/
DirectX::XMFLOAT4X4 GameObject::GetWorld(bool transpose)
{
	// �e�v�f�̍s����擾
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(
		DirectX::XMVectorSet(m_quat.x, m_quat.y, m_quat.z, m_quat.w)
	);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	// �s��̍��Z
	DirectX::XMMATRIX M = S * R * T;

	// �]�u
	if (transpose)
	{
		M = DirectX::XMMatrixTranspose(M);
	}
	// XMMATRIX����XMFLOAT�֕ϊ�
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, M);

	return fMat;
}
/*
* @brief �O���x�N�g���̎擾
*/
DirectX::XMFLOAT3 GameObject::GetFront()
{
	DirectX::XMVECTOR vFront = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vFront = DirectX::XMVector3Rotate(vFront, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vFront));
	return dir;
}

/*
* @brief �E�����x�N�g���̎擾
*/
DirectX::XMFLOAT3 GameObject::GetRight()
{
	DirectX::XMVECTOR vRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vRight = DirectX::XMVector3Rotate(vRight, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vRight));
	return dir;
}
/*
* @brief ����x�N�g���̎擾
*/
DirectX::XMFLOAT3 GameObject::GetUp()
{
	DirectX::XMVECTOR vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vUp = DirectX::XMVector3Rotate(vUp, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, vUp);
	return dir;
}

// 2D�I�u�W�F�N�g�ԍ���Ԃ�
int GameObject::Get2DObjNo()
{
	return m_2DObjNo;
}

// 3D�I�u�W�F�N�g�ԍ���Ԃ�
int GameObject::Get3DObjNo()
{
	return m_3DObjNo;
}

/*
* @brief �I�u�W�F�N�g�̃^�O�擾
*/
std::string GameObject::GetTag()
{
	return m_tag;
}

/*
* @brief �R���|�[�l���g�ǉ����̏���������
*/
void GameObject::_addComponent(Component* component)
{
	// �����I�u�W�F�N�g�̓o�^
	component->transform = this;

	// �ۑ��f�[�^�Ɉ�v����R���|�[�l���g�����邩�T��
	const char* name = typeid(*component).name();
	auto it = std::find_if(m_datas.begin(), m_datas.end(), [&name](SaveData& data) {
		return strstr(data.name, name) == data.name;
		});
	if (it == m_datas.end()) return;

	// �ۑ�����Ă������ݒ�
	Component::DataAccessor accessor(it->value);
	component->ReadWrite(&accessor);
}