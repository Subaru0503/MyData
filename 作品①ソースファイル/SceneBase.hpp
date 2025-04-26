#ifndef __SCENE_BASE_HPP__
#define __SCENE_BASE_HPP__

#include <memory>
#include <map>
#include <string>
#include <list>
#include <Windows.h>
#include <GameObject.hpp>
#include "DebugMenu.h"
#include "Shader.h"

// �t�F�[�h
#include "Fade.h"

// �^
#include "float3.h"

// @brief �V�[���ǉ��p�I�u�W�F�N�g
class SceneObjectBase
{
public:
	virtual ~SceneObjectBase() {}
	void* m_pObj;
	bool isGameObject;
};

template<class T>
class SceneObject : public SceneObjectBase
{
public:
	SceneObject(T* ptr) {
		m_pObj = ptr;
		isGameObject = std::is_base_of<GameObject, T>();
	}
	virtual ~SceneObject() { delete static_cast<T*>(m_pObj); }
};

// @breif �V�[����{�N���X
class SceneBase
{
private:
	using Objects = std::map<std::string, SceneObjectBase*>;
	using Items = std::list<std::string>;
public:
	enum Scene
	{
		None,
		TITLE,
		GAME,
		STAGE2,
		MAX,
	};
public:
	static void Initialize();
	SceneBase(const char* name);
	virtual ~SceneBase();
	void _update(float tick);
	void _draw();

	void ParentorTitleObjUpdate();	// �X�e�[�W�V�[���ȊO�̃I�u�W�F�N�g�X�V����
	void StageObjUpdate();			// �X�e�[�W�V�[���̃I�u�W�F�N�g�X�V����

	template<class T> T* AddSubScene();
	void RemoveSubScene();

	// �I�u�W�F�N�g����֐�
	template<class T> T* CreateObj(const char* name);	
	template<> GameObject* CreateObj(const char* name);
	template<class T> T* CreateSceneObj(const char* name);
	void DestroyObj(const char* name);
	template<class T> T* GetObj(const char* name);

	// �p���V�[���̈�ʂ�̏���
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

protected:

	GameObject* Get3DObj(int no);
	GameObject* Get2DObj(int no);

private:
	std::string m_name;
	int m_ColliderObjSize;	// �R���C�_�[�����̃I�u�W�F�N�g��
#ifdef _DEBUG
	static debug::Item* hierarchy;
	static debug::Item* inspector;
#endif
protected:
	SceneBase* m_pParent;
	SceneBase* m_pSubScene;
	static Fade* m_pFade;
	static Objects m_objects;
	Items m_items;
	bool m_ObjUpdateStopFlg;
};

/// <summary>
/// �T�u�V�[���̒ǉ�
/// </summary>
/// <typeparam name="T">�T�u�V�[���̌^</typeparam>
/// <returns>���������T�u�V�[��</returns>
template<class T> T* SceneBase::AddSubScene()
{
	RemoveSubScene();
	T* pScene = new T;
	m_pSubScene = pScene;
	pScene->m_pParent = this;
	pScene->Init();
	return pScene;
}

/// <summary>
/// �I�u�W�F�N�g�̐���
/// </summary>
/// <typeparam name="T">�I�u�W�F�N�g�̌^</typeparam>
/// <param name="name">�I�u�W�F�N�g�̖���</param>
/// <returns>���������I�u�W�F�N�g</returns>
template<class T> T* SceneBase::CreateObj(const char* name)
{
#ifdef _DEBUG
	// �f�o�b�O���̂݁A���̃_�u�肪�Ȃ����`�F�b�N
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// �q�G�����L�[�ɒǉ�
	hierarchy->AddListItem(name);

#endif // _DEBUG

	// �I�u�W�F�N�g����
	T* ptr = new T();
	m_objects.insert(std::pair<std::string, SceneObjectBase*>(name, new SceneObject<T>(ptr)));
	m_items.push_back(name);
	return ptr;
}

template<> GameObject* SceneBase::CreateObj(const char* name)
{
#ifdef _DEBUG
	// �f�o�b�O���̂݁A���̃_�u�肪�Ȃ����`�F�b�N
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// �q�G�����L�[�ɒǉ�
	hierarchy->AddListItem(name);
#endif // _DEBUG

	GameObject* ptr = new GameObject(name);
	m_objects.insert(std::pair<std::string, SceneObjectBase*>(name, new SceneObject<GameObject>(ptr)));
	m_items.push_back(name);
	return ptr;
}

template<class T>
inline T * SceneBase::CreateSceneObj(const char * name)
{
#ifdef _DEBUG
	// �f�o�b�O���̂݁A���̃_�u�肪�Ȃ����`�F�b�N
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// �q�G�����L�[�ɒǉ�
	hierarchy->AddListItem(name);

#endif // _DEBUG

	// �I�u�W�F�N�g����
	T* ptr = new T(name);
	m_objects.insert(std::pair<std::string, SceneObjectBase*>(name, new SceneObject<T>(ptr)));
	m_items.push_back(name);
	return ptr;
}

/// <summary>
/// �I�u�W�F�N�g�̎擾
/// </summary>
/// <typeparam name="T">�I�u�W�F�N�g�̌^</typeparam>
/// <param name="name">�I�u�W�F�N�g�̖���</param>
/// <returns>�擾�����I�u�W�F�N�g</returns>
template<class T> T* SceneBase::GetObj(const char* name)
{
	// �I�u�W�F�N�g�̒T��
	Objects::iterator it = m_objects.find(name);
	if (it == m_objects.end()) return nullptr;

	// �^�ϊ�
	T* ptr = reinterpret_cast<T*>(it->second->m_pObj);
	return ptr;
}

#endif // __SCENE_BASE_HPP__