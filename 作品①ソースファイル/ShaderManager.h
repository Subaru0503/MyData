// シェーダー管理クラス

// インクルードガード
#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

// インクルード部
#include "Shader.h"

// クラス定義
class ShaderManager
{
private:
	using ShaderList = std::map<std::string, Shader*>;
public:
	inline static ShaderManager& GetInstance()
	{
		static ShaderManager instance;
		return instance;
	}

	void Init();	// 初期化

	// シェーダーセットアップ
	void ShaderSetUP(const char** shaderFiles, int shaderNum);

	// シェーダーの生成
	template<class T> T* CreateShader(const char* name);
	// シェーダーの取得
	template<class T> T* GetShader(const char* name);
private:

	ShaderManager()
	{
		Init();	// 初期化
	}
	~ShaderManager()
	{
		for (auto _shader = m_shaders.begin(); _shader != m_shaders.end();)
		{
			delete _shader->second;
			_shader = m_shaders.erase(_shader);
		}
	}

private:
	static ShaderList m_shaders;
};

// シェーダーの生成
template<class T>
inline T * ShaderManager::CreateShader(const char * name)
{
	// シェーダー生成
	T* ptr = new T();
	m_shaders.insert(std::pair<std::string, Shader*>(name, ptr));
	return ptr;
}

// シェーダーの取得
template<class T>
inline T * ShaderManager::GetShader(const char * name)
{
	// シェーダーの探索
	ShaderList::iterator it = m_shaders.find(name);
	if (it == m_shaders.end()) return nullptr;

	// 型変換
	T* ptr = reinterpret_cast<T*>(it->second);
	return ptr;
}

#endif // __SHADER_MANAGER_H__
