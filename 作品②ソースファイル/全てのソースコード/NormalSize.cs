using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalSize : MonoBehaviour
{
    // �T�C�Y�{��
    [SerializeField] private float scaleFactor;

    // �T�C�Y��ʏ�T�C�Y�ɂ���
    public void ReSize()
    {
        transform.localScale *= scaleFactor;    // �T�C�Y���g��
    }
}
