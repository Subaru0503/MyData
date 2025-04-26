struct VS_IN
{
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : TEXCOORD1;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.worldPos = vout.pos;
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

	vout.uv = vin.uv;

	// (float3x3)は拡縮を考慮しない法線の計算
	vout.normal = mul(vin.normal, (float3x3)world);
	// x,y,zでそれぞれ違う拡縮の場合、上記の計算では
	// 正しい法線が計算できない。※CPUで事前に計算して
	// 渡す必要あり。
	// 例えば横に伸ばす拡大を行ったとき、斜め方向の法線は
	// 横に伸びるのではなく、縦に伸びなければおかしい。
	// ※極端な話、無限に横に伸ばせば上を向いた平面になるはず
	// そこで、拡縮のみ行列の成分を打ち消す逆行列とすることで
	// 正しい法線が計算できる。
	// 手順)
	// 1.回転と拡縮が含まれた行列の逆行列を計算する。
	// 2.１で計算された逆行列を転置する。
	// 　直交行列の逆行列は転置行列の結果と等しい。

	return vout;
}