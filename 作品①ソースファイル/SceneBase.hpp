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

// フェード
#include "Fade.h"

// 型
#include "float3.h"

// @brief シーン追加用オブジェクト
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

// @breif シーン基本クラス
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

	void ParentorTitleObjUpdate();	// ステージシーン以外のオブジェクト更新処理
	void StageObjUpdate();			// ステージシーンのオブジェクト更新処理

	template<class T> T* AddSubScene();
	void RemoveSubScene();

	// オブジェクト操作関数
	template<class T> T* CreateObj(const char* name);	
	template<> GameObject* CreateObj(const char* name);
	template<class T> T* CreateSceneObj(const char* name);
	void DestroyObj(const char* name);
	template<class T> T* GetObj(const char* name);

	// 継承シーンの一通りの処理
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

protected:

	GameObject* Get3DObj(int no);
	GameObject* Get2DObj(int no);

private:
	std::string m_name;
	int m_ColliderObjSize;	// コライダー持ちのオブジェクト数
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
/// サブシーンの追加
/// </summary>
/// <typeparam name="T">サブシーンの型</typeparam>
/// <returns>生成したサブシーン</returns>
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
/// オブジェクトの生成
/// </summary>
/// <typeparam name="T">オブジェクトの型</typeparam>
/// <param name="name">オブジェクトの名称</param>
/// <returns>生成したオブジェクト</returns>
template<class T> T* SceneBase::CreateObj(const char* name)
{
#ifdef _DEBUG
	// デバッグ中のみ、名称ダブりがないかチェック
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// ヒエラルキーに追加
	hierarchy->AddListItem(name);

#endif // _DEBUG

	// オブジェクト生成
	T* ptr = new T();
	m_objects.insert(std::pair<std::string, SceneObjectBase*>(name, new SceneObject<T>(ptr)));
	m_items.push_back(name);
	return ptr;
}

template<> GameObject* SceneBase::CreateObj(const char* name)
{
#ifdef _DEBUG
	// デバッグ中のみ、名称ダブりがないかチェック
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// ヒエラルキーに追加
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
	// デバッグ中のみ、名称ダブりがないかチェック
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
	// ヒエラルキーに追加
	hierarchy->AddListItem(name);

#endif // _DEBUG

	// オブジェクト生成
	T* ptr = new T(name);
	m_objects.insert(std::pair<std::string, SceneObjectBase*>(name, new SceneObject<T>(ptr)));
	m_items.push_back(name);
	return ptr;
}

/// <summary>
/// オブジェクトの取得
/// </summary>
/// <typeparam name="T">オブジェクトの型</typeparam>
/// <param name="name">オブジェクトの名称</param>
/// <returns>取得したオブジェクト</returns>
template<class T> T* SceneBase::GetObj(const char* name)
{
	// オブジェクトの探索
	Objects::iterator it = m_objects.find(name);
	if (it == m_objects.end()) return nullptr;

	// 型変換
	T* ptr = reinterpret_cast<T*>(it->second->m_pObj);
	return ptr;
}

#endif // __SCENE_BASE_HPP__