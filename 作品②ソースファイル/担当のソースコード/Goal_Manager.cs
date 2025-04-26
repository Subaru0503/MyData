using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal_Manager : MonoBehaviour
{
    Goal goal;  // �S�[���R���|�[�l���g

    private float currentTime = 0.0f;  // �o�ߎ���
    [SerializeField] private GameManager _gameManager;
    [SerializeField] private MainCameraManager _mainCameraManager;
    [SerializeField] private GameObject _gameClearAnimation;
    [SerializeField] private CountTimer _countTimer;
    [SerializeField] private float _DelayTime;
    // Start is called before the first frame update
    void Start()
    {
        // ���̎擾
        goal = GetComponent<Goal>();
    }

    // Update is called once per frame
    void Update()
    {
        // �S�[�����Ă��珈�������Ȃ�
        if (goal.goalFlg)
        {
            StartCoroutine(ClearCountDelete());
            return;
        }

        // �S�[�����C�����z���Ă���A��с`���^��ɂ��邩�m�F
        // �����̊֐��őҋ@��ԃt���O���Ǘ����Ă���
        if(!goal.LineCheck())
        {
            currentTime = 0.0f; // ���ԏ�����
            goal.CountDownReset();
            return;             // �����I��
        }

        // ���J�E���g�_�E������
        if (currentTime >= goal.checkTime)
        {
            _countTimer.TimeerEnable(false);
            goal.goalFlg = true;
            GoalAnimation();
        }

        goal.CountDown(goal.checkTime - currentTime);    // �J�E���g�_�E��

        currentTime += Time.deltaTime;  // �o�ߎ���

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
        // 1�b�҂�
        yield return new WaitForSeconds(_DelayTime);

        // �֐����Ăяo��
        _gameManager.GameClear();
    }

    IEnumerator ClearCountDelete()
    {
        // 1�b�҂�
        yield return new WaitForSeconds(1);

        // �֐����Ăяo��
        goal.CountDownReset();
    }

}
