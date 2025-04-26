#ifndef __FLOAT3_H__
#define __FLOAT3_H__

struct float3
{
	float x;
	float y;
	float z;

	float3()
	{
		x = y = z = 0.0f;
	}
	float3(const float3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	float3(const float3* p)
	{
		if (p) {
			x = p->x;
			y = p->y;
			z = p->z;
		}
		else {
			x = y = z = 0.0f;
		}
	}
	float3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// float3に変換
	inline static float3 Tofloat3(const DirectX::XMFLOAT3& pDXF)
	{
		float3 f3;
		f3.x = pDXF.x;
		f3.y = pDXF.y;
		f3.z = pDXF.z;

		return f3;
	}

	// DirectX::XMFLOAT3に変換
	inline static DirectX::XMFLOAT3 ToXMFLOAT3(const float3& pf3)
	{
		DirectX::XMFLOAT3 df;
		df.x = pf3.x;
		df.y = pf3.y;
		df.z = pf3.z;

		return df;
	}

	// 正規化
	inline float3 normalize() const
	{
		float len = length();

		// 長さチェック(0なら正規化をせずに返す)
		if (len > 0.0f)
		{
			// ベクトルを長さで割って、単位ベクトルを返す
			return float3{ x / len, y / len, z / len };
		}
		else
		{
			// ゼロベクトルを返す
			return float3{ 0.0f, 0.0f, 0.0f };
		}
	}

	// 距離
	inline static float distance(float3& a, float3& b)
	{
		return sqrt((b.x - a.x) * (b.x - a.x) +
			(b.y - a.y) * (b.y - a.y) +
			(b.z - a.z) * (b.z - a.z));
	}

	// 内積
	inline static float dot(float3& a, float3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// 長さを計算
	inline  float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	// ゼロベクトル
	inline float3 Zero() const
	{
		return float3{ 0.0f, 0.0f, 0.0f };
	}

	inline float3 cross(float3& v)
	{
		return float3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	inline float3& operator += (const float3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	inline float3& operator -= (const float3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	inline float3& operator *= (float r)
	{
		x *= r;
		y *= r;
		z *= r;
		return *this;
	}
	inline float3& operator /= (float r)
	{
		if (r != 0.0f) {
			x /= r;
			y /= r;
			z /= r;
		}
		return *this;
	}

	inline float3 operator + () const
	{
		return *this;
	}

	inline float3 operator - () const
	{
		return float3(-x, -y, -z);
	}

	// binary operators
	inline float3 operator + (const float3& v) const
	{
		return float3(x + v.x, y + v.y, z + v.z);
	}

	inline float3 operator - (const float3& v) const
	{
		return float3(x - v.x, y - v.y, z - v.z);
	}

	inline float3 operator * (float r) const
	{
		return float3(x * r, y * r, z * r);
	}

	inline float3 operator / (float r) const
	{
		if (r != 0.0f) {
			return float3(x / r, y / r, z / r);
		}
		return *this;
	}

	inline bool operator == (const float3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	inline bool operator != (const float3& v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}
};

#endif