using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotateBlock : MonoBehaviour
{
    // 落下させるブロックの種類数
    [SerializeField] private float rotateZ;

    // 次に落とすブロックの情報
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
