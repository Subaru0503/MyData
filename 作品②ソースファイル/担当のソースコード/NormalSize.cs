using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NormalSize : MonoBehaviour
{
    // サイズ倍率
    [SerializeField] private float scaleFactor;

    // サイズを通常サイズにする
    public void ReSize()
    {
        transform.localScale *= scaleFactor;    // サイズを拡大
    }
}
