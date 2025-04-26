using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UpdateMass : MonoBehaviour
{

    Rigidbody2D rb;

    private int childNum;                           // 子オブジェクトの数

    private float singleMass;                       // ひとつのブロックの質量

    // Start is called before the first frame update
    void Start()
    {
        // 子オブジェクトの数を格納
        childNum = transform.childCount;

        // 実体取得取得
        rb = GetComponent<Rigidbody2D>();

        singleMass = rb.mass;               // 一個当たりの質量抽出
        rb.mass = singleMass * childNum;    // 子オブジェクトの数に合うように計算
    }

    // Update is called once per frame
    void Update()
    {
        // 子オブジェクトの数に変化があったら
        if(childNum != transform.childCount)
        {
            childNum = transform.childCount;    // 子オブジェクトの数更新
            rb.mass = singleMass * childNum;    // 子オブジェクトの数に合うように計算
        }
    }
}
