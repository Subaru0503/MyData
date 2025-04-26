using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ItemPouch : MonoBehaviour
{
    // タグ設定
    public string blocktagName;                                     // アイテムの対象になるタグ
    public string sticktagName;                                     // のりアイテムのタグ
    public string bigtagName;                                       // 巨大化アイテムのタグ
    public string erasertagName;                                    // 消しゴムアイテムのタグ

    [SerializeField] private LayerMask itemLayer;                   // アイテム共通のレイヤー

    [SerializeField] private GameObject eraserObj;                  // 消しゴムオブジェクト

    public SoundManager _soundManager { get; set; } // サウンドコンポーネント

    public GameObject item { get; set; }                            // 所持しているアイテム

    // 所持フラグ
    public bool hasStick { get; set; }                              // のアイテムりを所持
    public bool hasBig { get; set; }                                // 巨大化アイテムを所持
    public bool hasEraser { get; set; }                             // 消しゴムアイテムを所持

    private Image itemImage;                                        // アイテムUI

    private Sprite newSprite;                                       // 設定画像
    private Sprite noItemSprite;                                    // アイテムがないときの設定画像

    // Start is called before the first frame update
    void Start()
    {
        // 実体取得
        itemImage = GameObject.Find("ItemUIImage").GetComponent<Image>();
    }

    // アイテムのレイヤー操作
    public void ItemLayer(bool use)
    {
        if(use)
        {
            itemImage.sprite = noItemSprite;    // UI画像設定なし
            return;
        }
        itemImage.sprite = newSprite;           // UI画像設定
    }

    // アイテム使用 アイテムをポーチから削除
    public void ItemDelete()
    {
        Destroy(item);  // アイテム削除
        item = null;
        NoItem();       // アイテムがなくなったのでフラグを下げる
    }

    // 持ち物がなくなった
    private void NoItem()
    {
        // フラグ下げ    
        hasStick = false;
        hasBig = false;
        hasEraser = false;
    }

    // 持ち物チェック
    private void CheckItem()
    {
        // アイテムのタグを確認
        switch(item.tag)
        {
            case "Stick":           // のり
                hasStick = true;    // 所持フラグ上げ

                // 所持フラグ下げ
                hasBig = false;
                hasEraser = false;
                break;

            case "Big":             // 巨大化
                hasBig = true;      // 所持フラグ上げ

                // 所持フラグ下げ
                hasStick = false;
                hasEraser = false;
                break;

            case "Eraser":          // 消しゴム
                hasEraser = true;   // 所持フラグ上げ

                // 所持フラグ下げ
                hasStick = false;
                hasBig = false;
                break;
        }
    }

    // アイテム入手
    private void OnTriggerEnter2D(Collider2D collision)
    {
        // レイヤーチェック
        if(((1 << collision.gameObject.layer) & itemLayer.value) != 0)
        {
            _soundManager.PlayerSound(1);                                   // 入手SE再生

            item = collision.gameObject;                                            // アイテム情報
            CheckItem();                                                            // 入手したアイテムを確認
            item.transform.position = new
                Vector3(-100.0f, item.transform.position.y, 0.0f);                  // 座標をずらす

            // UI設定
            noItemSprite = item.                                                    // アイテムを持ってないときに
                GetComponent<UISprite>().IsnoItemUISprite;                          // 表示する画像情報取得
            newSprite = item.GetComponent<UISprite>().Issprite;                     // UIに表示する画像情報取得
            itemImage.sprite = newSprite;                                           // UI画像設定
        }
    }

    // 消しゴムアイテム
    public GameObject GetEraserObj()
    {
        return eraserObj;
    }
}
