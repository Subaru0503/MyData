using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Hold : MonoBehaviour
{
    public GameObject holdBlock { get; set; }   // ホールドブロック

    private Image holdImage;                    // ホールドUI

    private int normalLayer;                    // 通常時のレイヤー

    // Start is called before the first frame update
    void Start()
    {
        holdImage = GameObject.Find("HoldUIImage").GetComponent<Image>();
    }

    // UI処理
    public void SetImage(Sprite newSprite)
    {
        holdImage.sprite = newSprite;   // 画像設定
    }

    // レイヤー値を戻す
    public void ResetLayer()
    {
        // ホールド前のレイヤー値にする
        holdBlock.GetComponent<SpriteRenderer>().sortingOrder = normalLayer;
    }

    // ブロックをホールド
    public void HoldBlock()
    {
        // 回転リセット
        holdBlock.transform.eulerAngles = new Vector3(0.0f, 0.0f, 0.0f);

        // レイヤー値退避
        normalLayer = holdBlock.GetComponent<SpriteRenderer>().sortingOrder;
        // 背景の後ろにやって見えなくする
        holdBlock.GetComponent<SpriteRenderer>().sortingOrder = -3;
    }
}
