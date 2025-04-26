using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SetupFall : MonoBehaviour
{
    // デバッグ用
    [SerializeField] private bool DebugStage1 = false;
    [SerializeField] private bool DebugStage2 = false;
    [SerializeField] private bool DebugStage3 = false;

    // ステージごとの落下させるブロックの種類
    [SerializeField] private GameObject[] Stage1_FallBlock;
    [SerializeField] private GameObject[] Stage2_FallBlock;
    [SerializeField] private GameObject[] Stage3_FallBlock;

    // レアブロック
    [SerializeField] private GameObject RareBlock;

    // 座標補正
    [SerializeField] private float offset;

    // ブロックの質量
    [SerializeField] private float blockmass;

    // 次のブロックを生成までのインターバル
    [SerializeField] private float interval;

    private bool isDrop;

    // 落下させるブロックの種類数
    private List<GameObject> blockKind = new List<GameObject>();

    // 次に落とすブロックの情報
    private GameObject[] next = new GameObject[1];

    // Start is called before the first frame update
    void Awake()
    {
        BlockLoad();    // ブロック読み込み
        isDrop = false;
    }

    // 落下させるブロックの読み込み
    private void BlockLoad()
    {
        if (DebugStage1)
        {
            for (int i = 0; i < Stage1_FallBlock.Length; i++)
            {
                blockKind.Add(Stage1_FallBlock[i]);
            }
            return;
        }
        if (DebugStage2)
        {
            for (int i = 0; i < Stage2_FallBlock.Length; i++)
            {
                blockKind.Add(Stage2_FallBlock[i]);
            }
            return;
        }
        if (DebugStage3)
        {
            for (int i = 0; i < Stage3_FallBlock.Length; i++)
            {
                blockKind.Add(Stage3_FallBlock[i]);
            }
            return;
        }
        // シーンの名前で読み込むブロックを変える
        switch (SceneManager.GetActiveScene().name)
        {
            // ステージ1
            case "Stage1Scene":
                for (int i = 0; i < Stage1_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage1_FallBlock[i]);
                }
                break;
            // ステージ2
            case "Stage2Scene":
                for (int i = 0; i < Stage2_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage2_FallBlock[i]);
                }
                break;
            // ステージ3
            case "Stage3Scene":
                for (int i = 0; i < Stage3_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage3_FallBlock[i]);
                }
                break;
            // 該当するのがなかった
            default:
                Debug.Log("該当するシーンの名前がありませんでした");
                for (int i = 0; i < Stage1_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage1_FallBlock[i]);
                }
                break;
        }
    }

    // ブロック生成
    public void CreateBlock()
    {
        // レアブロック抽選
        int num = Random.Range(0, 100);

        Vector3 pos = transform.position;

        // 100分の一引き当て
        if (num == 0)
        {
            next[0] = Instantiate(RareBlock, pos, Quaternion.identity);
        }
        // 通常ブロック生成
        else
        {
            int index = Random.Range(0, blockKind.Count);

            next[0] = Instantiate(blockKind[index], pos, Quaternion.identity);
        }
    }

    // ブロック落下
    public void Fall()
    {
        if (!next[0] || isDrop == true) return;

        isDrop = true;
        // 移動
        Vector3 nextpos = next[0].transform.position;
        nextpos.y -= 0.5f;
        next[0].transform.position = nextpos;
        StartCoroutine(FallSequence());
    }
    private IEnumerator FallSequence()
    {
        if (next[0] == null) yield break; // next[0] が null なら処理を中断

        Vector3 startPos = next[0].transform.position;
        Vector3 endPos = startPos;
        endPos.y -= 0.5f; // 終了時の高さ

        float duration = 0.2f; // アニメーションの長さ
        float elapsedTime = 0;

        // アニメーションの時間分、徐々に位置を変更
        while (elapsedTime < duration)
        {
            elapsedTime += Time.deltaTime;
            float t = Mathf.Clamp01(elapsedTime / duration);
            next[0].transform.position = Vector3.Lerp(startPos, endPos, t);
            yield return null; // 次のフレームまで待つ
        }

        // コライダーの有効化とRigidbody2Dの追加
        PolygonCollider2D polygonCollider2D = next[0].GetComponent<PolygonCollider2D>();
        if (polygonCollider2D)
        {
            polygonCollider2D.enabled = true;
        }
        else
        {
            next[0].GetComponent<BoxCollider2D>().enabled = true;
        }

        next[0].AddComponent<Rigidbody2D>();
        Rigidbody2D rb = next[0].GetComponent<Rigidbody2D>();
        rb.mass = blockmass;
        next[0].GetComponent<NormalSize>().ReSize();
        next[0].GetComponent<FallSpeed>().Setrb();

        next[0] = null;
        isDrop = false;


    }
    // ブロック落下開始位置の移動
    public void BlockMove(bool Right)
    {
        // nullなら終了
        if (!next[0]) return;

        // 移動
        Vector3 nextpos = next[0].transform.position;

        if(Right)
        {
            nextpos.x = transform.position.x + offset;
        }
        else 
        { 
            nextpos.x = transform.position.x - offset; 
        }
        next[0].transform.position = nextpos;
    }
    public void BlockMoveReset()
    {
        // nullなら終了
        if (!next[0]) return;

        // 移動
        Vector3 nextpos = next[0].transform.position;

        nextpos.x = transform.position.x;
        next[0].transform.position = nextpos;
    }

    // next情報
    public GameObject IsNext
    {
        get
        {
            return next[0];
        }
        set
        {
            next[0] = value;
        }
    }

    // 生成間隔情報
    public float IsInterval()
    {
        return interval;
    }
}
