using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bubble : MonoBehaviour
{
    private Rigidbody2D _rb;
   [SerializeField] private GameObject _Item;

    [SerializeField] private float _moveSpeed = 0.5f;  // 上にに進む速度
    [SerializeField] private float _maxSpeed = 1.0f;   // 最高速
    [SerializeField] private float _accelerationDuration = 5.0f;  // 最高速に至るまでの時間 


    private float _holizonSpeed = 0.5f;  // 左右の動きの強さ
    private float _frequency = 2.0f;  // 動きの周期
    private float _time;  // 時間

    private UISprite _sprite;


    [SerializeField] private List<Sprite> _SpriteList;
    void Start()
    {
        _rb = GetComponent<Rigidbody2D>();
        _sprite =GetComponent<UISprite>();

        switch (gameObject.tag)
        {
            case "Stick":
                _Item.GetComponent<SpriteRenderer>().sprite = _SpriteList[0];
                _sprite.SetUISprite(_SpriteList[0]);
                break;
            case "Big":
                _Item.GetComponent<SpriteRenderer>().sprite = _SpriteList[1];
                _sprite.SetUISprite(_SpriteList[1]);
                break;
            case "Eraser":
                _Item.GetComponent<SpriteRenderer>().sprite = _SpriteList[2];
                _sprite.SetUISprite(_SpriteList[2]);
                break;
        }

        // スケールをベジエ曲線で制御するコルーチンを開始
        StartCoroutine(ScaleWithBezierCurve());

        // 速度を徐々に増加させるコルーチンを開始
        StartCoroutine(IncreaseMoveSpeed());
    }

    // Update is called once per frame
    void Update()
    {

        _time += Time.deltaTime;

        // サイン波を使って左右に動かす
        float holizonMovement = Mathf.Sin(_time * _frequency) * _holizonSpeed;

        _rb.velocity = new Vector2(holizonMovement, _moveSpeed);
    }

    // ベジエ曲線でスケールを制御するコルーチン
    IEnumerator ScaleWithBezierCurve()
    {
        float duration = 0.5f;  // 1秒間のスケール変化
        float elapsedTime = 0f;

        Vector3 startScale = new Vector3(0.5f, 0.5f, 0.5f);  // スケール0から
        Vector3 controlPoint1 = new Vector3(0.75f, 0.75f, 0.75f);  // 中間制御点1
        Vector3 controlPoint2 = new Vector3(0.0f, 0.0f, 0.0f);  // 中間制御点2
        Vector3 endScale = Vector3.one;  // スケール1へ

        while (elapsedTime < duration)
        {
            elapsedTime += Time.deltaTime;
            float t = elapsedTime / duration;  // 時間の進行割合

            // ベジエ曲線を使ってスケールを計算
            Vector3 newScale = BezierCurve(t, startScale, controlPoint1, controlPoint2, endScale);
            transform.localScale = newScale;

            yield return null;  // 次のフレームまで待機
        }

        // 最後にスケールを確実に1に設定
        transform.localScale = endScale;
    }

    // 5秒間かけて_moveSpeedを0.5から1.0に増加させるコルーチン
    IEnumerator IncreaseMoveSpeed()
    {
        float initialSpeed = 0.5f;
        float elapsedTime = 0f;

        while (elapsedTime < _accelerationDuration)
        {
            elapsedTime += Time.deltaTime;
            _moveSpeed = Mathf.Lerp(initialSpeed, _maxSpeed, elapsedTime / _accelerationDuration);
            yield return null;
        }

        _moveSpeed = _maxSpeed;  // 最終的に1.0に設定
    }
    // 三次ベジエ曲線の計算
    Vector3 BezierCurve(float t, Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3)
    {
        float u = 1 - t;
        float tt = t * t;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * t;

        Vector3 p = uuu * p0;  // (1-t)^3 * P0
        p += 3 * uu * t * p1;  // 3(1-t)^2 * t * P1
        p += 3 * u * tt * p2;  // 3(1-t) * t^2 * P2
        p += ttt * p3;         // t^3 * P3

        return p;
    }
}
