using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Goal : MonoBehaviour
{
    [SerializeField] private Transform goalLine;        // ゴールライン

    [SerializeField] private GameObject countObject;     // カウントダウンオブジェクト
    [SerializeField] private Sprite[] countNumber = new Sprite[6];
    private Image countImage;
    private RectTransform rectTransform;
    private int oldCount = 0;

    [SerializeField] private Vector2 goalcheckPos;
    [SerializeField] private Vector2 goalcheckSize;     // 四角形のサイズ

    [SerializeField, Header("オーディオソースアタッチ")] private AudioSource audioSource;
    [SerializeField, Header("カウントダウンSE")] private AudioClip countdownSE;
    [SerializeField, Header("フィニッシュSE")] private AudioClip finishSE;

    //[SerializeField] private GameManager _game_manager; // ゲームマネージャー

    public float checkTime;                             // 確認時間

    public GameObject goalUI;                           // ゴールUI

    public bool player_1standby { get; set; }           // すたっぴ～待機状態フラグ

    public bool isInArea { get; set; }                  // 枠内に入っているフラグ

    public bool goalFlg { get; set; }                   // ゴールフラグ

    private Player2_Manager _player2_manager;           // プレイヤー2マネージャー

    private GameObject player_1;                        // すたっぴ～の情報
    private GameObject player_2;                        // らび～の情報

    private float oldplayer_2pos;                       // らび～の過去座標(x)

    //private bool toggle = true;                         // とぐるが切った用のフラグ

    // Start is called before the first frame update
    void Start()
    {
        player_1standby = false;
        goalFlg = false;
        countObject.TryGetComponent(out countImage);
        countObject.TryGetComponent(out rectTransform);
    }

    private void Update()
    {
        // プレイヤーの情報がなかったら処理しない
        if (!player_1 || !player_2) return;

        // すたっぴ～のx座標と合わせる
        goalcheckPos.x = player_1.transform.position.x;
    }

    // ゴールチェック
    public bool LineCheck()
    {
        // プレイヤーの実体取得
        if(!player_1 || !player_2)
        {
            player_1 = GameObject.Find("Player_1(Clone)");
            player_2 = GameObject.Find("Player_2(Clone)");
            // コンポーネント取得
            _player2_manager = player_2.GetComponent<Player2_Manager>();
        }
        // ゴールラインを超えてかつ
        // すたっぴ～の真上にらび～がいる
        else if(player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f &&
            // ↓すたっぴ～とらび～の位置判定(0.5fなのはプレイヤーのスケールが本来は1だから)
            goalcheckPos.x - goalcheckSize.x / 2.0f <=
            player_2.transform.position.x + 0.5f &&
            goalcheckPos.x + goalcheckSize.x / 2.0f >=
            player_2.transform.position.x - 0.5f &&
            !_player2_manager.Input_move)
        {
            player_1standby = false;        // 待機状態フラグを下げる

            isInArea = true;                // 枠内に入っている

            Debug.Log("準備完了");
            return true;
        }
        // 範囲内にらび～がいるが動いている状態
        else if (player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f &&
            // ↓すたっぴ～とらび～の位置判定(0.5fなのはプレイヤーのスケールが本来は1だから)
            goalcheckPos.x - goalcheckSize.x / 2.0f <=
            player_2.transform.position.x + 0.5f &&
            goalcheckPos.x + goalcheckSize.x / 2.0f >=
            player_2.transform.position.x - 0.5f &&
            _player2_manager.Input_move)
        {
            player_1standby = true;         // 待機状態フラグを上げる

            isInArea = true;                // 枠内に入っている

            Debug.Log("らび～の準備が完了してない");
            return false;
        }
        // ゴールラインを超えたが、らび～が真上にいない
        else if(player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f)
        {
            player_1standby = true;         // 待機状態フラグを上げる
            isInArea = false;                // 持ち上げ準備フラグを下げる
            Debug.Log("待機状態");


            return false;
        }

        player_1standby = false;            // 待機状態フラグを下げる
        isInArea = false;                // 持ち上げ準備フラグを下げる

        return false;
    }

    public void CountDown(float time)
    {
        var c = (int)Mathf.Ceil(time);
        if (c < 0) c = 0;
        if (oldCount != c)
        {
            rectTransform.sizeDelta = new Vector2(1000, 1000);
            if (c == 0) audioSource.PlayOneShot(finishSE);
            else audioSource.PlayOneShot(countdownSE);
        }
        oldCount = c;
        countImage.sprite = countNumber[c];
        rectTransform.sizeDelta = new Vector2(rectTransform.sizeDelta.x - 16.67f, rectTransform.sizeDelta.y - 16.67f);
        countObject.SetActive(true);
    }

    public void CountDownReset()
    {
        countObject.SetActive(false);
        rectTransform.sizeDelta = new Vector2(1000, 1000);
    }

    // デバッグ用ギズモ
    private void OnDrawGizmos()
    {
        // プレイヤーのローカル空間に基づいて groundCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(goalcheckPos);

        // プレイヤーの回転角に基づいて矩形の角度を設定
        float rotationZ = transform.eulerAngles.z;

        // Gizmosの回転行列を設定して、矩形を描画
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, rotationZ), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, goalcheckSize);
    }
}
