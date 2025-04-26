// EasingFunction.cpp
// イージング関数まとめ

//=== インクルード ===
#include "EasingFunction.h"	// イージング関数宣言
#include <DirectXMath.h>	// 計算関数用
// 円周率定義
const float PI = DirectX::XM_PI;

float EaseInSine(float param)
{
	return 1 - cos(param * PI / 2);
}

float EaseOutSine(float param)
{
	return sin(param * PI / 2);
}

float EaseInOutSine(float param)
{
	return -1 * (cos(PI * param) - 1) / 2;
}

float EaseInQuat(float param)
{
	return pow(param, 2);
}

float EaseOutQuat(float param)
{
	return 1 - pow(1 - param, 2);
}

float EaseInOutQuat(float param)
{
	return param < 0.5 ?
		2 * pow(param, 2) :
		1 - pow(-2 * param * 2, 2) / 2;
}

float EaseInQubic(float param)
{
	return pow(param, 3);
}

float EaseOutQubic(float param)
{
	return 1 - pow(1 - param, 2);
}

float EaseInOutQubic(float param)
{
	return param < 0.5 ?
		4 * pow(param, 3) :
		1 - pow(-2 * param + 2, 3) / 2;
}

float EaseInQuart(float param)
{
	return pow(param, 4);
}

float EaseOutQuart(float param)
{
	return 1 - pow(1 - param, 4);
}

float EaseInOutQuart(float param)
{
	return param < 0.5 ?
		8 * pow(param, 4) :
		1 - pow(-2 * param + 2, 4) / 2;
}

float EaseInQuint(float param)
{
	return pow(param, 5);
}

float EaseOutQuint(float param)
{
	return 1 - pow(1 - param, 5);
}

float EaseInOutQuint(float param)
{
	return param < 0.5 ?
		16 * pow(param, 5) :
		1 - pow(-2 * param + 2, 5) / 2;
}

float EaseInExpo(float param)
{
	return param == 0 ? 0 :
		pow(2, 10 * param - 10);
}

float EaseOutExpo(float param)
{
	return param == 1 ? 1 :
		1 - pow(2, -10 * param);
}

float EaseInOutExpo(float param)
{
	return param == 0 ? 0 : param == 1 ? 1 : param < 0.5 ?
		pow(2, 20 * param - 10) / 2 :
		(2 - pow(2, 20 * param + 10)) / 2;
}

float EaseInCirc(float param)
{
	return 1 - sqrt(1 - pow(param, 2));
}

float EaseOutCirc(float param)
{
	return sqrt(1 - pow(param - 1, 2));
}

float EaseInOutCirc(float param)
{
	return param < 0.5 ?
		(1 - sqrt(1 - pow(2 * param, 2))) / 2 :
		(sqrt(1 - pow(-2 * param + 2, 2)) + 1) / 2;
}

float EaseInBack(float param)
{
	float c1 = 1.70158;
	float c3 = c1 + 1;
	return c3 * pow(param, 3) - c1 * pow(param, 2);
}

float EaseOutBack(float param)
{
	float c1 = 1.70158;
	float c3 = c1 + 1;
	return 1 + c3 * pow(param - 1, 3) + c1 * pow(param - 1, 2);
}

float EaseInOutBack(float param)
{
	float c1 = 1.70158;
	float c2 = c1 * 1.525;
	return param < 0.5 ?
		(pow(2 * param, 2) *((c2 + 1) * 2 * param - c2)) / 2 :
		(pow(2 * param - 2, 2) * 
		((c2 + 1) * (param * 2 - 2) + c2) + 2) / 2;
}

float EaseInElastic(float param)
{
	float c4 = (2 * PI) / 3;
	return param == 0 ? 0 :param == 1 ? 1 :
		-pow(2, 10 * param - 10) *
		sin((param * 10 - 10.75) * c4);
//またはsin(param * 10 - 10.75) * c4;	
}

float EaseOutElastic(float param)
{
	float c4 = (2 * PI) / 3;
	return param == 0 ? 0 : param == 1 ? 1 :
		pow(2, -10 * param) *
		sin((param * 10 - 0.75) * c4) + 1;
}

float EaseInOutElastic(float param)
{
	float c5 = (2 * PI) / 4.5;
	return param == 0 ? 0 : param == 1 ? 1 : param < 0.5 ?
		-(pow(2, 20 * param - 10) * 
		sin((20 * param - 11.125) * c5)) / 2 :
		(pow(2, -20 * param + 10) *
		sin((20 * param - 11.125) * c5)) / 2 + 1;
}

float EaseInBounce(float param)
{
	return 1 - EaseOutBounce(1 - param);
}

float EaseOutBounce(float param)
{
	float n1 = 7.5625;
	float d1 = 2.75;
	return param < 1 / d1 ? n1 * param * param :
		param < 2 / d1 ?
		n1 * pow(param - 1.5 / d1, 2) + 0.75 :
		param < 2.5 / d1 ?
		n1 * pow(param - 2.25 / d1, 2) + 0.9375 :
		n1 * pow(param - 2.625 / d1, 2) + 0.984375;
}

float EaseInOutBounce(float param)
{
	return param < 0.5 ?
		(1 - EaseOutBounce(1 - 2 * param)) / 2 :
		(1 + EaseOutBounce(2 * param - 1)) / 2;
}
