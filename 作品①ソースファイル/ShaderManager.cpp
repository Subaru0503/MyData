// インクルード部
#include "ShaderManager.h"
#include "Shader.h"

ShaderManager::ShaderList ShaderManager::m_shaders;
// 初期化
void ShaderManager::Init()
{
	const char* file[] = {
		"VS_Object",
		"VS_WorldPos",
		"VS_Color",
		"PS_TexColor",
		"PS_Color",
		"PS_SkyBrightness",
		"PS_Title",
	};

	ShaderSetUP(file, _countof(file));
}

// シェーダーセットアップ
void ShaderManager::ShaderSetUP(const char ** shaderFiles, int shaderNum)
{
	for (int i = 0; i < shaderNum; ++i) {
		Shader* shader;
		if (strstr(shaderFiles[i], "PS_") == shaderFiles[i]) {
			shader = CreateShader<PixelShader>(shaderFiles[i]);
		}
		else if (strstr(shaderFiles[i], "VS_") == shaderFiles[i]) {
			shader = CreateShader<VertexShader>(shaderFiles[i]);
		}
		else {
			MessageBox(NULL, shaderFiles[i], "Shader name [VS_ / PS_]", MB_OK);
		}
		std::string path = "Assets/Shader/";
		path += shaderFiles[i];
		path += ".cso";
		if (FAILED(shader->Load(path.c_str()))) {
			MessageBox(NULL, shaderFiles[i], "Shader Error", MB_OK);
		}
	}
}
