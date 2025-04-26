using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bubble : MonoBehaviour
{
    private Rigidbody2D _rb;
   [SerializeField] private GameObject _Item;

    [SerializeField] private float _moveSpeed = 0.5f;  // ��ɂɐi�ޑ��x
    [SerializeField] private float _maxSpeed = 1.0f;   // �ō���
    [SerializeField] private float _accelerationDuration = 5.0f;  // �ō����Ɏ���܂ł̎��� 


    private float _holizonSpeed = 0.5f;  // ���E�̓����̋���
    private float _frequency = 2.0f;  // �����̎���
    private float _time;  // ����

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

        // �X�P�[�����x�W�G�Ȑ��Ő��䂷��R���[�`�����J�n
        StartCoroutine(ScaleWithBezierCurve());

        // ���x�����X�ɑ���������R���[�`�����J�n
        StartCoroutine(IncreaseMoveSpeed());
    }

    // Update is called once per frame
    void Update()
    {

        _time += Time.deltaTime;

        // �T�C���g���g���č��E�ɓ�����
        float holizonMovement = Mathf.Sin(_time * _frequency) * _holizonSpeed;

        _rb.velocity = new Vector2(holizonMovement, _moveSpeed);
    }

    // �x�W�G�Ȑ��ŃX�P�[���𐧌䂷��R���[�`��
    IEnumerator ScaleWithBezierCurve()
    {
        float duration = 0.5f;  // 1�b�Ԃ̃X�P�[���ω�
        float elapsedTime = 0f;

        Vector3 startScale = new Vector3(0.5f, 0.5f, 0.5f);  // �X�P�[��0����
        Vector3 controlPoint1 = new Vector3(0.75f, 0.75f, 0.75f);  // ���Ԑ���_1
        Vector3 controlPoint2 = new Vector3(0.0f, 0.0f, 0.0f);  // ���Ԑ���_2
        Vector3 endScale = Vector3.one;  // �X�P�[��1��

        while (elapsedTime < duration)
        {
            elapsedTime += Time.deltaTime;
            float t = elapsedTime / duration;  // ���Ԃ̐i�s����

            // �x�W�G�Ȑ����g���ăX�P�[�����v�Z
            Vector3 newScale = BezierCurve(t, startScale, controlPoint1, controlPoint2, endScale);
            transform.localScale = newScale;

            yield return null;  // ���̃t���[���܂őҋ@
        }

        // �Ō�ɃX�P�[�����m����1�ɐݒ�
        transform.localScale = endScale;
    }

    // 5�b�Ԃ�����_moveSpeed��0.5����1.0�ɑ���������R���[�`��
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

        _moveSpeed = _maxSpeed;  // �ŏI�I��1.0�ɐݒ�
    }
    // �O���x�W�G�Ȑ��̌v�Z
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
