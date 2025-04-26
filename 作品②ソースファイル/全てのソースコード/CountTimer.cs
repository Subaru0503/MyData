using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CountTimer : MonoBehaviour
{
    // 使用する数字
    [SerializeField] private List<Sprite> number;

    // タイマー
    [SerializeField] private List<Image> timerImage;

    private float currentTimer = 0.0f;  // 経過時間

    private bool _timerEnable = false;

    // Start is called before the first frame update
    void Start()
    {
        _timerEnable = false;
    }

    // Update is called once per frame
    void Update()
    {
        // 経過時間描画
        // 分単位で経過してるか
        if (currentTimer / 60.0f < 10.0f)
        {
            // 分描画
            timerImage[0].sprite = number[0];
            timerImage[1].sprite = number[(int)(currentTimer / 60.0f)];
        }
        else
        {
            timerImage[0].sprite = number[(int)(currentTimer / 60.0f / 10.0f)];
            timerImage[1].sprite = number[(int)(currentTimer / 60.0f % 10.0f)];
        }

        if(currentTimer % 60.0f < 10.0f)
        {
            // 秒数描画
            timerImage[2].sprite = number[0];
            timerImage[3].sprite = number[(int)(currentTimer % 60.0f)];
        }
        else
        {
            // 秒数描画
            timerImage[2].sprite = number[(int)(currentTimer % 60.0f / 10.0f)];
            timerImage[3].sprite = number[(int)(currentTimer % 60.0f % 10.0f)];
        }

        if(_timerEnable) currentTimer += Time.deltaTime; // 経過時間
    }   

    public float GetTimer()
    {
        return currentTimer;
    }

    public void SetTimer(float timer)
    {
        currentTimer = timer;
    }
    public void TimeerEnable(bool Enable)
    {
        _timerEnable = Enable;
    }
}
