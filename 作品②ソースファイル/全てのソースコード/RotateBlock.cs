using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBlock : MonoBehaviour
{
    // ����������u���b�N�̎�ސ�
    [SerializeField] private float rotateZ;

    // ���ɗ��Ƃ��u���b�N�̏��
    public GameObject next { get; set; }

    public void RightRotate()
    {
        next.transform.Rotate(0.0f, 0.0f, -rotateZ);
    }

    public void LeftRotate()
    {
        next.transform.Rotate(0.0f, 0.0f, rotateZ);
    }
}
