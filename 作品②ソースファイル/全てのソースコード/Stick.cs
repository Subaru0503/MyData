using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stick : MonoBehaviour
{
    public SoundManager _soundManager { get; set; } // サウンドコンポーネント

    public int layerMask { get; set; }             // のりがくっつけるレイヤー

    public string BaseTag { get; set; }            // 土台のタグ

    private LineRenderer lineRenderer;
    private BoxCollider2D boxCollider;
    private PolygonCollider2D polygonCollider;

    private float mass = 0;                         // 一個のブロックの質量情報

    private bool PlaySE = false;                    // SE再生フラグ

    // Start is called before the first frame update
    void Awake()
    {
        // コンポーネント追加
        lineRenderer = gameObject.AddComponent<LineRenderer>();

        // レイヤー設定
        lineRenderer.sortingOrder = 3;

        // コンポーネント取得
        polygonCollider = GetComponent<PolygonCollider2D>();

        // LineRendererがオブジェクトの位置や回転に追従するように調整
        lineRenderer.useWorldSpace = false;

        StickDraw();
    }

    // 仮でわかりやすくするために線を描画
    public void StickDraw()
    {
        if (polygonCollider)
        {
            PolygonDraw();
        }
    }

    private void BoxDraw()
    {
        // BoxCollider2Dの頂点数に合わせてLineRendererの頂点数を設定
        lineRenderer.positionCount = 5;  // 4つの頂点＋1つ目の頂点に戻るために5つ必要

        // 線の色と太さを設定
        lineRenderer.startColor = Color.red;
        lineRenderer.endColor = Color.red;
        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;

        // BoxCollider2Dのサイズを基に頂点を計算（ローカル座標）
        Vector2 size = boxCollider.size;   // BoxCollider2Dのサイズ（ローカル座標系）
        Vector2 offset = boxCollider.offset; // BoxCollider2Dのオフセット（ローカル座標系）

        Vector3 topLeft = new Vector3(-size.x / 2 + offset.x, size.y / 2 + offset.y, 0);
        Vector3 topRight = new Vector3(size.x / 2 + offset.x, size.y / 2 + offset.y, 0);
        Vector3 bottomRight = new Vector3(size.x / 2 + offset.x, -size.y / 2 + offset.y, 0);
        Vector3 bottomLeft = new Vector3(-size.x / 2 + offset.x, -size.y / 2 + offset.y, 0);

        // 頂点をLineRendererに設定
        lineRenderer.SetPosition(0, topLeft);
        lineRenderer.SetPosition(1, topRight);
        lineRenderer.SetPosition(2, bottomRight);
        lineRenderer.SetPosition(3, bottomLeft);
        lineRenderer.SetPosition(4, topLeft);  // 最後に最初の頂点に戻る
    }

    private void PolygonDraw()
    {
        // PolygonCollider2Dの頂点数に合わせてLineRendererの頂点数を設定
        lineRenderer.positionCount = polygonCollider.points.Length + 1;  // 閉じた形にするために+1

        // 色を反映させるためにマテリアル設定
        lineRenderer.material = new Material(Shader.Find("Sprites/Default"));

        // 線の色と太さを設定
        Gradient gradient = new Gradient();
        gradient.SetKeys(
            new GradientColorKey[] {
                new GradientColorKey(Color.yellow, 0.0f),      // 始点: 黄色

                new GradientColorKey(new Color(1.0f, 0.5f, 0.0f), 0.5f),      // 真ん中: 赤とオレンジの中間色

                new GradientColorKey(Color.yellow, 1.0f),      // 終点: 黄色
            },
            new GradientAlphaKey[]{
                new GradientAlphaKey(1.0f, 0.0f),   // 始点の透明度: 不透明
                new GradientAlphaKey(1.0f, 1.0f)    // 終点の透明度: 不透明
            }
        );

        lineRenderer.colorGradient = gradient;

        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;

        // PolygonCollider2Dの各頂点をLineRendererに設定（ローカル座標）
        for (int i = 0; i < polygonCollider.points.Length; i++)
        {
            Vector3 localPosition = new Vector3(polygonCollider.points[i].x,
                polygonCollider.points[i].y, -0.1f);  // ローカル座標の頂点を取得
            lineRenderer.SetPosition(i, localPosition);
        }

        // 最後の頂点に最初の頂点を設定して閉じる
        lineRenderer.SetPosition(polygonCollider.points.Length,
            new Vector3(polygonCollider.points[0].x,
            polygonCollider.points[0].y,
            -0.1f));
    }

    // 触れたブロックがくっつく判定
    private void OnCollisionEnter2D(Collision2D collision)
    {
        // どっちも同じ親なら処理をしない
        // プレイヤーなら処理をしない
        // 特定のレイヤーなら処理をしない
        if ((transform.parent && collision.collider.transform.parent &&
            collision.collider.transform.parent == transform.parent) ||
            collision.collider.tag == "Player" || collision.collider.tag == "Eraser" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        if (mass == 0)
        {
            // 情報取得
            mass = GetComponent<Rigidbody2D>().mass;
        }
        // 土台以外のブロックに衝突したら自分自身の情報を渡す
        if (layerMask == collision.gameObject.layer)
        {
            // 自分自身の情報を受け渡す
            PassSelfInfo(collision.collider.gameObject);
        }

        // レイヤーが指定されたもので、親がないブロックだったら
        if(layerMask == collision.gameObject.layer &&
            !collision.collider.transform.parent)
        {
            // 土台にくっつく
            if (collision.gameObject.tag == BaseTag)
            {
                BaseAttach(collision.gameObject);
            }
            // 衝突したブロックが自分にくっつく
            else
            {
                AttachSelf(collision.gameObject);
            }
        }
        // 接触したブロックがお互いに親を持っていて、同じ親じゃなかった場合
        // ひとつのグループにする
        // 土台が子になってる親に合わせる
        else if(transform.parent && collision.collider.transform.parent.childCount > 0 &&
            transform.parent.childCount > 0)
        {
            MergeParent(collision.collider.gameObject);              // ひとつの親オブジェクトに統合
        }
        // すでに親子関係があるブロックにのりブロックが触れた場合
        else if(collision.collider.transform.parent.childCount > 0)
        {
            StickTo(collision.collider.gameObject);                  // 相手にくっつく
        }

        // 再生してなかったらする
        if (!PlaySE)
        {
            _soundManager.PlayerSound(2);   // SE再生
            PlaySE = true;                          // フラグ上げ
        }
    }

    // 自分自身の情報を受け渡す
    private void PassSelfInfo(GameObject block)
    {
        ResetBlock resetBlock = block.GetComponent<ResetBlock>();

        // 既に情報を取得してたら処理をしない
        if (resetBlock && resetBlock.stick) return;

        // 土台なら専用のフラグを上げる
        if(block.tag == BaseTag)
        {
            resetBlock.Base = true;
        }
        resetBlock.StickBlock = gameObject;                 // 情報を渡す
        resetBlock.stick = true;                            // くっついたフラグを上げる
        resetBlock.mass = mass;                             // 質量情報を取得
    }


    // 土台にくっつく
    private void BaseAttach(GameObject block)
    {
        //if (block.transform.parent) return;

        // 親が用意されてなかったら
        if (!block.transform.parent)
        {
            var obj = new GameObject();                             // 親生成
            obj.AddComponent<Rigidbody2D>();                        // Rigidbody2D追加
            obj.AddComponent<UpdateMass>();                         // スクリプト追加
            obj.tag = block.tag;                                    // タグ設定
            obj.layer = block.layer;                                // レイヤー設定

            Rigidbody2D rb = obj.GetComponent<Rigidbody2D>();
            rb.mass = mass;                                         // 質量設定
            rb.gravityScale = 0;                                    // 重力OFF
            rb.isKinematic = true;                                  // 物理演算OFF

            block.transform.parent = obj.transform;                       // 親設定
            Destroy(block.transform.GetComponent<Rigidbody2D>());         // 自身のRigidbody2D削除
        }

        // 自分に親がいた場合子を全て移して親を削除
        if (transform.parent)
        {
            Transform oldparent = transform.parent;
            while (oldparent.childCount > 0)
            {
                int i = 0;
                oldparent.GetChild(i).parent = block.transform.parent;
            }

            Destroy(oldparent.gameObject);
        }
        // 親がいなかったら親を設定してリジッドボディの削除
        else
        {
            transform.parent = block.transform.parent;                         // 親設定
            Destroy(transform.GetComponent<Rigidbody2D>());             // 自身のRigidbody2D削除
        }
    }

    // 自分自身にくっつく
    private void AttachSelf(GameObject block)
    {
        // 親が用意されてなかったら
        if(!transform.parent)
        {
            var obj = new GameObject();                             // 親生成
            obj.AddComponent<Rigidbody2D>();                        // Rigidbody2D追加
            obj.AddComponent<UpdateMass>();                         // スクリプト追加
            obj.layer = gameObject.layer;                           // レイヤー設定

            Rigidbody2D rb = obj.GetComponent<Rigidbody2D>();
            rb.mass = mass;                                         // 質量を代入

            transform.parent = obj.transform;                       // 親設定
            Destroy(transform.GetComponent<Rigidbody2D>());         // 自身のRigidbody2D削除
        }

        block.transform.parent = transform.parent;                  // のりがついてないブロックの親設定
        Destroy(block.GetComponent<Rigidbody2D>());                 // Rigidbody2D削除
    }

    // ひとつの親オブジェクトにまとめる
    private void MergeParent(GameObject block)
    {
        Transform oldparent;
        //List<Transform> childTransform = new List<Transform>();

        // ぶつかったブロックの親オブジェクトが土台の親だった場合
        if (block.transform.parent.tag == BaseTag)
        {
            // 情報を取得しておく
            oldparent = transform.parent;

            //// カウントがずれるから先に情報取得する
            //for (int i = 0; i < transform.parent.childCount; i++)
            //{
            //    childTransform.Add(transform.parent.GetChild(i));
            //}

            //for (int i = 0; i < childTransform.Count; i++)
            //{
            //    childTransform[i].parent = block.transform;
            //}

            // 自分自身の親子グループの子を全てぶつかったブロックの親オブジェクトの子にする
            while (oldparent.childCount > 0)
            {
                int i = 0;
                oldparent.GetChild(i).parent = block.transform.parent;
            }

            // 要らない親オブジェクトは破棄しましょう
            Destroy(oldparent.gameObject);                              // 親オブジェクト削除　ごめんね
            return;
        }

        // ↓土台が入ってる親オブジェクトもしくはどっちも土台が入ってないオブジェクトだった場合

        // 情報を取得しておく
        oldparent = block.transform.parent;

        //// カウントがずれるから先に情報取得する
        //for (int i = 0; i < block.transform.childCount; i++)
        //{
        //    childTransform.Add(block.transform.GetChild(i));
        //}

        //// ぶつかった相手のブロックを自分の親オブジェクトにいれる
        //for (int i = 0; i < childTransform.Count; i++)
        //{
        //    childTransform[i].parent = transform.parent;
        //}

        // ぶつかったブロックの親子グループの子を全て自分自身の親オブジェクトの子にする
        while (oldparent.childCount > 0)
        {
            int i = 0;
            oldparent.GetChild(i).parent = transform.parent;
        }

        // 要らない親オブジェクトは破棄しましょう
        Destroy(oldparent.gameObject);                              // 親オブジェクト削除　ごめんね
    }

    // 相手にくっつく
    private void StickTo(GameObject block)
    {
        transform.parent = block.transform.parent;              // 親を設定
        Destroy(transform.GetComponent<Rigidbody2D>());             // 自身のRigidbody2D削除
    }
}
