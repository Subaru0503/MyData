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
	// コンポーネントリスト
	using Components = std::vector<Component*>;

	// データの保存
	struct SaveData
	{
		const char* name;	// 保存する値の名称
		char* value;		// 保存値
	};
	using Datas = std::vector<SaveData>;
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void Execute();

	// 初期状態に戻す
	virtual void ResetState();

	// 当たったオブジェクトのあとの処理
	virtual void OnCollision(GameObject* obj);
	// 検知したオブジェクトのあとの処理
	virtual void OnScanner(GameObject* obj);

	// コンポーネントの生成
	template<class T>
	T* AddComponent();
	// コンポーネントの取得
	template<class T>
	T* GetComponent();

#ifdef _DEBUG
	// インスペクターへの表示
	virtual void Debug(debug::Window* window);
#endif

	// セット関数
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetScale(DirectX::XMFLOAT3 scale);
	void SetQuat(DirectX::XMFLOAT4 quat);
	// 2Dオブジェクト番号設定
	void Set2DObjNo(int no);
	// 3Dオブジェクト番号設定
	void Set3DObjNo(int no);
	void SetTag(std::string tag);	// オブジェクトタグ設定
	// 移動床の上にいるフラグ設定
	inline void SetOnMoveFloor(bool flg)
	{
		m_OnMoveFloor = flg;
	}

	// ゲット関数
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetOldPos();	// 過去座標を返す
	DirectX::XMFLOAT3 GetScale();	// サイズを返す
	DirectX::XMFLOAT4 GetQuat();	// 回転角度を返す
	DirectX::XMFLOAT4X4 GetWorld(bool transpose = true);
	DirectX::XMFLOAT3 GetFront();
	DirectX::XMFLOAT3 GetRight();
	DirectX::XMFLOAT3 GetUp();
	// 2Dオブジェクト番号
	int Get2DObjNo();
	// 3Dオブジェクト番号
	int Get3DObjNo();
	std::string GetTag();	// オブジェクトのタグを返す
	// 移動床の上にいるフラグを返す
	inline bool GetOnMoveFloor()
	{
		return m_OnMoveFloor;
	}
	// オブジェクト名を返す
	inline std::string GetName()
	{
		return m_name;
	}
protected:
	// 継承先のクラスでオブジェクト別の処理を実装する場合、上書きすること。
	virtual void Update() {}
private:
	// コンポーネント追加時に型に関係なく呼び出す処理
	void _addComponent(Component* component);

private:
	Components			m_components;	// コンポーネントの一覧
	Datas				m_datas;		// 保存データ
	std::string			m_name;			// オブジェクト名
	DirectX::XMFLOAT3	m_rotation;		// 回転
	int m_2DObjNo;					// 2Dオブジェクト番号
	int m_3DObjNo;					// 3Dオブジェクト番号
protected:
	GameObject* m_pCollisionObj;	// 衝突したオブジェクト
	std::string m_tag;				// オブジェクトタグ
	DirectX::XMFLOAT3	m_pos;		// 座標
	DirectX::XMFLOAT3	m_oldpos;	// 過去座標
	DirectX::XMFLOAT4	m_quat;		// 回転
	DirectX::XMFLOAT3	m_scale;	// 拡縮
	bool m_OnMoveFloor;				// 移動床の上にいるフラグ
};


/*
* @brief コンポーネントの追加
*/
template<class T>
T* GameObject::AddComponent()
{
#ifdef _DEBUG
	// デバッグ時のみ、指定された型がComponentを継承しているか確認
	static_assert(std::is_base_of<Component, T>(),
		"[GameObject::GetComponent] template T does not inherit from 'Component'");
#endif
	// コンポーネント生成
	T* ptr = new T;
	// 型に関係ない初期化処理を実施
	_addComponent(ptr);
	// 管理リストに追加
	m_components.push_back(ptr);

	return ptr;
}

/*
* @brief コンポーネントの取得
*/
template<class T>
T* GameObject::GetComponent()
{
	T* ptr = nullptr;
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		// 型チェック
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