using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    // �ړ���
    [SerializeField] private float MoveValue;

    // ���W�b�h�{�f�B
    Rigidbody2D rb;

    // Start is called before the first frame update
    void Start()
    {
        // ���̎擾
        rb = GetComponent<Rigidbody2D>();
    }

    // �E�Ɉړ�
    public void RightMove()
    {
        rb.velocity = new Vector2(MoveValue, rb.velocity.y);
    }

    // ���Ɉړ�
    public void LeftMove()
    {
        rb.velocity = new Vector2(-MoveValue, rb.velocity.y);
    }

    // �ړ��ʃ��Z�b�g
    public void ResetValue()
    {
        if (rb == null) return;
        rb.velocity = new Vector2(0, rb.velocity.y);
    }
}
