using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;

public class ReadyGo : MonoBehaviour
{

    [SerializeField, Header("Ready表示フレーム")] private int readyCount = 60;
    [SerializeField, Header("ReadyとGoが出るまでの遅延")] private int delay = 0;
    [SerializeField, Header("Go表示フレーム")] private int goCount = 120;

    private AudioSource audioSource;
    [SerializeField, Header("レディーゴーSE")] private AudioClip readyGoSE;

    private RectTransform rectTransform;

    GameObject ready;
    GameObject go;

    [SerializeField] private CountTimer _countTimer;

    private PlayerInputManager playerInputManager;

    private int count = 999;

    private bool nowReadyGo = false;
    private bool nowReady = false;
    private bool nowDelay = false;
    private bool nowGo = false;

    public bool endReadyGo = false;

    // Start is called before the first frame update
    void Start()
    {
        ready = transform.GetChild(0).gameObject;
        go = transform.GetChild(1).gameObject;

        endReadyGo = false;

        ready.SetActive(false);
        go.SetActive(false);

        TryGetComponent(out rectTransform);
        TryGetComponent(out audioSource);
    }

    // Update is called once per frame
    void Update()
    {
        ++count;
        if (nowReadyGo)
        {
            if (nowReady)
            {
                if (count == readyCount)
                {
                    count = -1;
                    ready.SetActive(false);
                    nowReady = false;
                    nowDelay = true;
                }
            }
            else if (nowDelay)
            {
                if (count == delay)
                {
                    count = -1;
                    go.SetActive(true);
                    nowDelay = false;
                    nowGo = true;
                }
            }
            else if (nowGo)
            {
                if (count == goCount)
                {
                    ready.SetActive(false);
                    go.SetActive(false);
                    playerInputManager.ToggleEnable(true);
                    _countTimer.TimeerEnable(true);
                    endReadyGo = true;

                    rectTransform.parent.gameObject.SetActive(false);
                }
            }
        }
        else
        {
            if (count == delay)
            {
                nowReadyGo = true;
                nowReady = true;
                ready.SetActive(true);
                count = -1;
                audioSource.PlayOneShot(readyGoSE);
            }
        }
    }

    public void Setting(PlayerInputManager pim)
    {
        playerInputManager = pim;
    }

    public void StartReady()
    {
        //nowReadyGo = true;
        //ready.SetActive(true);
        //bro.SetActive(false);
        count = -1;
    }

    public void Skip()
    {
        /*
        count = -1;
        go.SetActive(true);
        nowDelay = false;
        nowGo = true;
        frameToFinish = 0;
        readyCount = 0;
        delay = 0;
        goCount = 30;
        */
        count = -1;
    }
}
