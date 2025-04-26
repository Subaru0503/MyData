using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal_Manager : MonoBehaviour
{
    Goal goal;  // ゴールコンポーネント

    private float currentTime = 0.0f;  // 経過時間
    [SerializeField] private GameManager _gameManager;
    [SerializeField] private MainCameraManager _mainCameraManager;
    [SerializeField] private GameObject _gameClearAnimation;
    [SerializeField] private CountTimer _countTimer;
    [SerializeField] private float _DelayTime;
    // Start is called before the first frame update
    void Start()
    {
        // 実体取得
        goal = GetComponent<Goal>();
    }

    // Update is called once per frame
    void Update()
    {
        // ゴールしてたら処理をしない
        if (goal.goalFlg)
        {
            StartCoroutine(ClearCountDelete());
            return;
        }

        // ゴールラインを越している、らび～が真上にいるか確認
        // ↓この関数で待機状態フラグを管理している
        if(!goal.LineCheck())
        {
            currentTime = 0.0f; // 時間初期化
            goal.CountDownReset();
            return;             // 処理終了
        }

        // ↓カウントダウン処理
        if (currentTime >= goal.checkTime)
        {
            _countTimer.TimeerEnable(false);
            goal.goalFlg = true;
            GoalAnimation();
        }

        goal.CountDown(goal.checkTime - currentTime);    // カウントダウン

        currentTime += Time.deltaTime;  // 経過時間

    }

    void GoalAnimation()
    {
        GameObject Player1 = GameObject.FindWithTag("Player");
        GameObject Player2 = GameObject.FindWithTag("Player2");
        Vector3 AnimationPos = new Vector3(Player2.transform.position.x, Player2.transform.position.y - 0.5f, Player2.transform.position.z);
        Instantiate(_gameClearAnimation, AnimationPos, Quaternion.identity);
        _mainCameraManager.GameClear();
        _DelayTime += _mainCameraManager.GetGoalAnimationFrame();

        Player1.SetActive(false);
        Player2.SetActive(false);
        StartCoroutine(ClearDelay());

    }
    IEnumerator ClearDelay()
    {
        // 1秒待つ
        yield return new WaitForSeconds(_DelayTime);

        // 関数を呼び出す
        _gameManager.GameClear();
    }

    IEnumerator ClearCountDelete()
    {
        // 1秒待つ
        yield return new WaitForSeconds(1);

        // 関数を呼び出す
        goal.CountDownReset();
    }

}
