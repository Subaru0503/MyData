using System.Collections;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using UnityEngine;

public class Balloon : MonoBehaviour
{
    // Start is called before the first frame update

    [SerializeField] private GameObject _CapsuleItem; // �q�v�f�ł���Q�[���I�u�W�F�N�g
    [SerializeField] private GameObject _Bubble;
    [SerializeField] private float _delayTime;
    private Rigidbody2D _rb;
    private Animator _animator;
    bool _Rupture;

    private float _moveSpeed = 1.0f;  // ���ɐi�ޑ��x
    private float _verticalSpeed = 0.5f;  // �㉺�̓����̋���
    private float _frequency = 2.0f;  // �㉺�̓����̎���
    private float _time;  // ����


    private int _ItemID;
    [SerializeField] private List<Sprite> _SpriteList;



    void Start()
    {
        _CapsuleItem.transform.localPosition = new Vector3(0.0f, -1.2f);
        _rb = GetComponent<Rigidbody2D>();
        _animator = GetComponent<Animator>();
        _Rupture = false;

        _time = 0.0f;
        int randomNumber = Random.Range(0, _SpriteList.Count);  
        _ItemID = randomNumber;

        _CapsuleItem.GetComponent<SpriteRenderer>().sprite = _SpriteList[_ItemID];

        if(transform.position.x <0)
        {
            _moveSpeed *= -1;
        }
    }

    // Update is called once per frame
    void Update()
    {
        _time += Time.deltaTime;

        // �T�C���g���g���ď㉺�ɓ�����
        float verticalMovement = Mathf.Sin(_time * _frequency) * _verticalSpeed;

        // ���ɐi�݂A�㉺�ɓ����悤�ɐݒ�
        _rb.velocity = new Vector2(-_moveSpeed, verticalMovement);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        // �v���C���[�ƂԂ��������ǂ������^�O�Ŕ���
        if (collision.gameObject.CompareTag("Player") && _Rupture == false)
        {
            _Rupture = true;
            _animator.SetTrigger("Rupture");

            StartCoroutine(Rupture());
        }
    }


    // ��莞�Ԍ�ɃI�u�W�F�N�g�𐶐�����R���[�`��
    IEnumerator Rupture()
    {
        yield return new WaitForSeconds(_delayTime);  // �w�莞�ԑҋ@
        Vector3 offset = new Vector3(0.0f, -1.2f, 0.0f);
        GameObject bubbleItem =  Instantiate(_Bubble, transform.position + offset, transform.rotation);  // �I�u�W�F�N�g�𐶐�
        bubbleItem.gameObject.layer = 7;
        switch (_ItemID)
        {
            case 0:
                bubbleItem.gameObject.tag = "Stick";
                break;
            case 1:
                bubbleItem.gameObject.tag = "Big";
                break;
            case 2:
                bubbleItem.gameObject.tag = "Eraser";
                break;
        }
        Destroy(gameObject);
    }
}
