#ifndef __SHADER_LIST_H__
#define __SHADER_LIST_H__

#include "Shader.h"
#include "Model.h"


class ShaderList
{
	// 定義
public:
	enum VSKind
	{
		VS_WORLD,
		VS_ANIME,
		VS_KIND_MAX
	};
	enum PSKind
	{
		PS_LAMBERT,
		PS_SPECULAR,
		PS_TOON,
		PS_FOG,
		PS_KIND_MAX
	};


public:
	ShaderList();
	~ShaderList();

	static void Init();
	static void Uninit();

	// シェーダー取得
	static VertexShader* GetVS(VSKind vs);
	static PixelShader* GetPS(PSKind ps);

	// 定数バッファへの設定
	static void SetWVP(DirectX::XMFLOAT4X4* wvp);
	static void SetBones(DirectX::XMFLOAT4X4* bones200);
	static void SetMaterial(const Model::Material& material);
	static void SetMaterial_Custom(const Model::Material& material);
	static void SetLight(DirectX::XMFLOAT4 color, DirectX::XMFLOAT3 dir);
	static void SetCameraPos(const DirectX::XMFLOAT3 pos);
	static void SetFog(DirectX::XMFLOAT4 color, float start, float range);
	
private:
	static void MakeWorldVS();
	static void MakeAnimeVS();
	static void MakeLambertPS();
	static void MakeSpecularPS();
	static void MakeToonPS();
	static void MakeFogPS();

private:
	static VertexShader* m_pVS[VS_KIND_MAX];
	static PixelShader* m_pPS[PS_KIND_MAX];
	
};

#endif // __SHADER_LIST_H__