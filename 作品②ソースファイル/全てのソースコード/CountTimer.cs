using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CountTimer : MonoBehaviour
{
    // �g�p���鐔��
    [SerializeField] private List<Sprite> number;

    // �^�C�}�[
    [SerializeField] private List<Image> timerImage;

    private float currentTimer = 0.0f;  // �o�ߎ���

    private bool _timerEnable = false;

    // Start is called before the first frame update
    void Start()
    {
        _timerEnable = false;
    }

    // Update is called once per frame
    void Update()
    {
        // �o�ߎ��ԕ`��
        // ���P�ʂŌo�߂��Ă邩
        if (currentTimer / 60.0f < 10.0f)
        {
            // ���`��
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
            // �b���`��
            timerImage[2].sprite = number[0];
            timerImage[3].sprite = number[(int)(currentTimer % 60.0f)];
        }
        else
        {
            // �b���`��
            timerImage[2].sprite = number[(int)(currentTimer % 60.0f / 10.0f)];
            timerImage[3].sprite = number[(int)(currentTimer % 60.0f % 10.0f)];
        }

        if(_timerEnable) currentTimer += Time.deltaTime; // �o�ߎ���
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
