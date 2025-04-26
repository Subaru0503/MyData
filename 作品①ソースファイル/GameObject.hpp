#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <DirectXMath.h>
#include <string>
#include <vector>
#include "DebugMenu.h"

class Component;

class GameObject
{
private:
	// �R���|�[�l���g���X�g
	using Components = std::vector<Component*>;

	// �f�[�^�̕ۑ�
	struct SaveData
	{
		const char* name;	// �ۑ�����l�̖���
		char* value;		// �ۑ��l
	};
	using Datas = std::vector<SaveData>;
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void Execute();

	// ������Ԃɖ߂�
	virtual void ResetState();

	// ���������I�u�W�F�N�g�̂��Ƃ̏���
	virtual void OnCollision(GameObject* obj);
	// ���m�����I�u�W�F�N�g�̂��Ƃ̏���
	virtual void OnScanner(GameObject* obj);

	// �R���|�[�l���g�̐���
	template<class T>
	T* AddComponent();
	// �R���|�[�l���g�̎擾
	template<class T>
	T* GetComponent();

#ifdef _DEBUG
	// �C���X�y�N�^�[�ւ̕\��
	virtual void Debug(debug::Window* window);
#endif

	// �Z�b�g�֐�
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetScale(DirectX::XMFLOAT3 scale);
	void SetQuat(DirectX::XMFLOAT4 quat);
	// 2D�I�u�W�F�N�g�ԍ��ݒ�
	void Set2DObjNo(int no);
	// 3D�I�u�W�F�N�g�ԍ��ݒ�
	void Set3DObjNo(int no);
	void SetTag(std::string tag);	// �I�u�W�F�N�g�^�O�ݒ�
	// �ړ����̏�ɂ���t���O�ݒ�
	inline void SetOnMoveFloor(bool flg)
	{
		m_OnMoveFloor = flg;
	}

	// �Q�b�g�֐�
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetOldPos();	// �ߋ����W��Ԃ�
	DirectX::XMFLOAT3 GetScale();	// �T�C�Y��Ԃ�
	DirectX::XMFLOAT4 GetQuat();	// ��]�p�x��Ԃ�
	DirectX::XMFLOAT4X4 GetWorld(bool transpose = true);
	DirectX::XMFLOAT3 GetFront();
	DirectX::XMFLOAT3 GetRight();
	DirectX::XMFLOAT3 GetUp();
	// 2D�I�u�W�F�N�g�ԍ�
	int Get2DObjNo();
	// 3D�I�u�W�F�N�g�ԍ�
	int Get3DObjNo();
	std::string GetTag();	// �I�u�W�F�N�g�̃^�O��Ԃ�
	// �ړ����̏�ɂ���t���O��Ԃ�
	inline bool GetOnMoveFloor()
	{
		return m_OnMoveFloor;
	}
	// �I�u�W�F�N�g����Ԃ�
	inline std::string GetName()
	{
		return m_name;
	}
protected:
	// �p����̃N���X�ŃI�u�W�F�N�g�ʂ̏�������������ꍇ�A�㏑�����邱�ƁB
	virtual void Update() {}
private:
	// �R���|�[�l���g�ǉ����Ɍ^�Ɋ֌W�Ȃ��Ăяo������
	void _addComponent(Component* component);

private:
	Components			m_components;	// �R���|�[�l���g�̈ꗗ
	Datas				m_datas;		// �ۑ��f�[�^
	std::string			m_name;			// �I�u�W�F�N�g��
	DirectX::XMFLOAT3	m_rotation;		// ��]
	int m_2DObjNo;					// 2D�I�u�W�F�N�g�ԍ�
	int m_3DObjNo;					// 3D�I�u�W�F�N�g�ԍ�
protected:
	GameObject* m_pCollisionObj;	// �Փ˂����I�u�W�F�N�g
	std::string m_tag;				// �I�u�W�F�N�g�^�O
	DirectX::XMFLOAT3	m_pos;		// ���W
	DirectX::XMFLOAT3	m_oldpos;	// �ߋ����W
	DirectX::XMFLOAT4	m_quat;		// ��]
	DirectX::XMFLOAT3	m_scale;	// �g�k
	bool m_OnMoveFloor;				// �ړ����̏�ɂ���t���O
};


/*
* @brief �R���|�[�l���g�̒ǉ�
*/
template<class T>
T* GameObject::AddComponent()
{
#ifdef _DEBUG
	// �f�o�b�O���̂݁A�w�肳�ꂽ�^��Component���p�����Ă��邩�m�F
	static_assert(std::is_base_of<Component, T>(),
		"[GameObject::GetComponent] template T does not inherit from 'Component'");
#endif
	// �R���|�[�l���g����
	T* ptr = new T;
	// �^�Ɋ֌W�Ȃ����������������{
	_addComponent(ptr);
	// �Ǘ����X�g�ɒǉ�
	m_components.push_back(ptr);

	return ptr;
}

/*
* @brief �R���|�[�l���g�̎擾
*/
template<class T>
T* GameObject::GetComponent()
{
	T* ptr = nullptr;
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		// �^�`�F�b�N
		if (typeid(T) == typeid(**it))
		{
			ptr = reinterpret_cast<T*>(*it);
			break;
		}
		++it;
	}
	return ptr;
}

#endif // __GAME_OBJECT_H__