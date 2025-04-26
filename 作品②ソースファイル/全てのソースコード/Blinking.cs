using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Blinking : MonoBehaviour
{
    //[SerializeField, Header("�_�ŊԊu")] private int blinkingTime = 10;

    [SerializeField, Header("�_���t���[��")] private int blinkingTime = 48;
    [SerializeField, Header("�����t���[��")] private int blinkingOutTime = 12;

    [SerializeField, Header("�_�ŉ�")] private int blinkingNum = 3;
    [SerializeField, Header("�x��")] private int delay = 60;

    [SerializeField, Header("�I�[�f�B�I�\�[�X")] private AudioSource audioSource;

    [SerializeField, Header("�x���̉�(L)")] private AudioClip windCautionSELeft;
    [SerializeField, Header("�x���̉�(R)")] private AudioClip windCautionSERight;

    [SerializeField, Header("���̉�(L)")] private AudioClip windSELeft;
    [SerializeField, Header("���̉�(R)")] private AudioClip windSERight;


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
