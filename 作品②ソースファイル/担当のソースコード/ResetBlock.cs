using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ResetBlock : MonoBehaviour
{
    // くっついているブロック
    public GameObject StickBlock { get; set; }

    // くっついたフラグ
    public bool stick { get; set; }

    // 土台フラグ
    public bool Base { get; set; }

    // 質量
    public float mass { get; set; }

    // Start is called before the first frame update
    void Start()
    {
        // 初期化
        StickBlock = null;
        stick = false;
    }

    // Update is called once per frame
    void Update()
    {
        // くっついてないなら処理をしない
        if (!stick) return;

        // くっついていたブロックが消えたら
        if(!StickBlock && !Base)
        {
            ReturnToBlock();    // 元のブロックに戻る
            stick = false;      // フラグ下げ
        }
        else if (!StickBlock && Base)
        {
            // 親の重力、物理計算をONにする
            Rigidbody2D rb = transform.parent.GetComponent<Rigidbody2D>();
            rb.gravityScale = 1;
            rb.isKinematic = false;

            // 親と自分を切り離す
            transform.parent.tag = "Untagged";
            transform.parent = null;
            Base = false;
            stick = false;
        }
    }

    // 通常のブロックに戻る
    public void ReturnToBlock()
    {
        gameObject.AddComponent
            <Rigidbody2D>().mass = mass;// Rigidbody2D追加
        transform.parent = null;
    }
}
