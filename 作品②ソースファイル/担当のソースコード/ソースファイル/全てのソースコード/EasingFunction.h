// EasingFunction.h
// イージング関数まとめ
#ifndef __EASING_FUNCTION_H__
#define __EASING_FUNCTION_H__

//=== プロトタイプ宣言 ===
// Sine
float EaseInSine(float param);
float EaseOutSine(float param);
float EaseInOutSine(float param);
// Quat
float EaseInQuat(float param);
float EaseOutQuat(float param);
float EaseInOutQuat(float param);
// Qubic
float EaseInQubic(float param);
float EaseOutQubic(float param);
float EaseInOutQubic(float param);
// Quart
float EaseInQuart(float param);
float EaseOutQuart(float param);
float EaseInOutQuart(float param);
// Quint
float EaseInQuint(float param);
float EaseOutQuint(float param);
float EaseInOutQuint(float param);
// Expo
float EaseInExpo(float param);
float EaseOutExpo(float param);
float EaseInOutExpo(float param);
// Circ
float EaseInCirc(float param);
float EaseOutCirc(float param);
float EaseInOutCirc(float param);
// Back
float EaseInBack(float param);
float EaseOutBack(float param);
float EaseInOutBack(float param);
// Elastic
float EaseInElastic(float param);
float EaseOutElastic(float param);
float EaseInOutElastic(float param);
// Bounce
float EaseInBounce(float param);
float EaseOutBounce(float param);
float EaseInOutBounce(float param);

#endif // !__EASING_FUNCTION_H__
