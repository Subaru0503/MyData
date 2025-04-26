using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Blinking : MonoBehaviour
{
    //[SerializeField, Header("点滅間隔")] private int blinkingTime = 10;

    [SerializeField, Header("点灯フレーム")] private int blinkingTime = 48;
    [SerializeField, Header("消灯フレーム")] private int blinkingOutTime = 12;

    [SerializeField, Header("点滅回数")] private int blinkingNum = 3;
    [SerializeField, Header("遅延")] private int delay = 60;

    [SerializeField, Header("オーディオソース")] private AudioSource audioSource;

    [SerializeField, Header("警告の音(L)")] private AudioClip windCautionSELeft;
    [SerializeField, Header("警告の音(R)")] private AudioClip windCautionSERight;

    [SerializeField, Header("風の音(L)")] private AudioClip windSELeft;
    [SerializeField, Header("風の音(R)")] private AudioClip windSERight;


    private int count = 0;
    private int blinkingCount = 0;

    private bool nowBlinking = false;

    private Behaviour behaviour;

    private int maxFrame;

    private bool leftToRight = false;

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out behaviour);
        //TryGetComponent(out audioSource);

        behaviour.enabled = false;

        maxFrame = blinkingTime + blinkingOutTime;
    }

    // Update is called once per frame
    void Update()
    {

        if (nowBlinking)
        {
            if ((Time.timeScale == 1))
            {
                if (count == blinkingTime)
                {
                    behaviour.enabled = false;
                }

                if (count == maxFrame)
                {
                    count = 0;
                    behaviour.enabled = true;
                    ++blinkingCount;

                    if (leftToRight) audioSource.PlayOneShot(windCautionSELeft);
                    else audioSource.PlayOneShot(windCautionSERight);


                    if (blinkingCount == blinkingNum)
                    {
                        nowBlinking = false;
                        behaviour.enabled = true;
                        if (leftToRight) audioSource.PlayOneShot(windSELeft);
                        else audioSource.PlayOneShot(windSERight);
                    }
                }
                ++count;
            }
        }
    }

    public void StartBlinking(bool ltr)
    {
        count = 0;
        blinkingCount = 0;
        nowBlinking = true;
        behaviour.enabled = false;
        leftToRight = ltr;
    }
    public void EndBlinking()
    {
        nowBlinking = false;
        //rectTransform.enabled = false;
    }
    public int GetBlinkingMaxTime()
    {
        return (blinkingTime * (blinkingNum * 2) - blinkingTime + delay);
    }
}
