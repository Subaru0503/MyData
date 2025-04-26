using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UpdateMass : MonoBehaviour
{

    Rigidbody2D rb;

    private int childNum;                           // �q�I�u�W�F�N�g�̐�

    private float singleMass;                       // �ЂƂ̃u���b�N�̎���

    // Start is called before the first frame update
    void Start()
    {
        // �q�I�u�W�F�N�g�̐����i�[
        childNum = transform.childCount;

        // ���̎擾�擾
        rb = GetComponent<Rigidbody2D>();

        singleMass = rb.mass;               // �������̎��ʒ��o
        rb.mass = singleMass * childNum;    // �q�I�u�W�F�N�g�̐��ɍ����悤�Ɍv�Z
    }

    // Update is called once per frame
    void Update()
    {
        // �q�I�u�W�F�N�g�̐��ɕω�����������
        if(childNum != transform.childCount)
        {
            childNum = transform.childCount;    // �q�I�u�W�F�N�g�̐��X�V
            rb.mass = singleMass * childNum;    // �q�I�u�W�F�N�g�̐��ɍ����悤�Ɍv�Z
        }
    }
}
