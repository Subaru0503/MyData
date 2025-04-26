// �V�F�[�_�[�Ǘ��N���X

// �C���N���[�h�K�[�h
#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__

// �C���N���[�h��
#include "Shader.h"

// �N���X��`
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

	void Init();	// ������

	// �V�F�[�_�[�Z�b�g�A�b�v
	void ShaderSetUP(const char** shaderFiles, int shaderNum);

	// �V�F�[�_�[�̐���
	template<class T> T* CreateShader(const char* name);
	// �V�F�[�_�[�̎擾
	template<class T> T* GetShader(const char* name);
private:

	ShaderManager()
	{
		Init();	// ������
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

// �V�F�[�_�[�̐���
template<class T>
inline T * ShaderManager::CreateShader(const char * name)
{
	// �V�F�[�_�[����
	T* ptr = new T();
	m_shaders.insert(std::pair<std::string, Shader*>(name, ptr));
	return ptr;
}

// �V�F�[�_�[�̎擾
template<class T>
inline T * ShaderManager::GetShader(const char * name)
{
	// �V�F�[�_�[�̒T��
	ShaderList::iterator it = m_shaders.find(name);
	if (it == m_shaders.end()) return nullptr;

	// �^�ϊ�
	T* ptr = reinterpret_cast<T*>(it->second);
	return ptr;
}

#endif // __SHADER_MANAGER_H__
