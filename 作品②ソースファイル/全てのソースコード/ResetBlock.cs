using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResetBlock : MonoBehaviour
{
    // �������Ă���u���b�N
    public GameObject StickBlock { get; set; }

    // ���������t���O
    public bool stick { get; set; }

    // �y��t���O
    public bool Base { get; set; }

    // ����
    public float mass { get; set; }

    // Start is called before the first frame update
    void Start()
    {
        // ������
        StickBlock = null;
        stick = false;
    }

    // Update is called once per frame
    void Update()
    {
        // �������ĂȂ��Ȃ珈�������Ȃ�
        if (!stick) return;

        // �������Ă����u���b�N����������
        if(!StickBlock && !Base)
        {
            ReturnToBlock();    // ���̃u���b�N�ɖ߂�
            stick = false;      // �t���O����
        }
        else if (!StickBlock && Base)
        {
            // �e�̏d�́A�����v�Z��ON�ɂ���
            Rigidbody2D rb = transform.parent.GetComponent<Rigidbody2D>();
            rb.gravityScale = 1;
            rb.isKinematic = false;

            // �e�Ǝ�����؂藣��
            transform.parent.tag = "Untagged";
            transform.parent = null;
            Base = false;
            stick = false;
        }
    }

    // �ʏ�̃u���b�N�ɖ߂�
    public void ReturnToBlock()
    {
        gameObject.AddComponent
            <Rigidbody2D>().mass = mass;// Rigidbody2D�ǉ�
        transform.parent = null;
    }
}
