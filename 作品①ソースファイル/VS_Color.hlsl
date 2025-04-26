// インプットレイアウト
// CPUから渡される頂点の情報を定義したもの
struct VS_IN
{
	float3 pos : POSITION0;		// セマンティクス
	float2 uv : TEXCOORD0;
};

// 頂点シェーダーからピクセルシェーダーへ送るデータの定義
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR;
};

// 定数バッファ
// CPUとGPUでやり取りする、頂点以外のデータを格納する先
cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

cbuffer Param : register(b1)
{
	float2 offset;
	float2 size;
	float2 uvPos;
	float2 uvScale;
	float4 color;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	// ローカル座標をスクリーン座標へ変換
	vout.pos = float4(vin.pos, 1.0f);	// ローカル座標
	vout.pos.xy *= size;
	vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);	// ワールド座標
	vout.pos = mul(vout.pos, view);		// ビュー座標
	vout.pos = mul(vout.pos, proj);		// プロジェクション座標

	// ピクセルシェーダーで利用するUV座標を渡す
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;

	vout.color = color;

	return vout;
}