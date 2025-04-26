using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.UI;
using UnityEngine.Video;

public class OpeningManager : MonoBehaviour
{
    public VideoPlayer videoPlayer;
    private PlayerInput playerInput;
    public GameObject texture;
    private RawImage rawImage;
    [SerializeField] private float ReplayTime;
    [SerializeField] private GameObject skipHelp;
    [SerializeField] private GameObject stertPanel;
    private AudioSource bgmSource;  
    private AudioSource opSkipClip;

    void Awake()
    {
        Screen.SetResolution(1920, 1080, true);
    }

    private void Start()
    {
        bgmSource = GameObject.Find("AudioManager").GetComponent<AudioSource>();
        videoPlayer = GetComponent<VideoPlayer>();
        opSkipClip = GetComponent<AudioSource>();
        // loopPointReached�C�x���g�ɃC�x���g�n���h���[��o�^
        videoPlayer.loopPointReached += OnVideoEnd;

        if (!bgmSource.isPlaying)
        {
            StartCoroutine(PlayVideoWithDelay(5));

            StartCoroutine(CheckBGMBGMEnd());
        }
        else
        {
            texture.SetActive(false);
            stertPanel.SetActive(true);
        }



    }

    private void Update()
    {
        if (skipHelp.activeSelf == false)
        {

                if (Input.anyKeyDown ||
                Input.GetKeyDown(KeyCode.JoystickButton0) ||
                Input.GetKeyDown(KeyCode.JoystickButton1) ||
                Input.GetKeyDown(KeyCode.JoystickButton2) ||
                Input.GetKeyDown(KeyCode.JoystickButton3) ||
                Input.GetKeyDown(KeyCode.JoystickButton4) ||
                Input.GetKeyDown(KeyCode.JoystickButton5) ||
                Input.GetKeyDown(KeyCode.JoystickButton6) ||
                Input.GetKeyDown(KeyCode.JoystickButton7) ||
                Input.GetKeyDown(KeyCode.JoystickButton8) ||
                Input.GetKeyDown(KeyCode.JoystickButton9) ||
                Input.GetKeyDown(KeyCode.JoystickButton10) ||
                Input.GetKeyDown(KeyCode.JoystickButton11) ||
                Input.GetKeyDown(KeyCode.JoystickButton12) ||
                Input.GetKeyDown(KeyCode.JoystickButton13) ||
                Input.GetKeyDown(KeyCode.JoystickButton14) ||
                Input.GetKeyDown(KeyCode.JoystickButton15) ||
                Input.GetKeyDown(KeyCode.JoystickButton16) ||
                Input.GetKeyDown(KeyCode.JoystickButton17) ||
                Input.GetKeyDown(KeyCode.JoystickButton18) ||
                Input.GetKeyDown(KeyCode.JoystickButton19))
            {
                skipHelp.SetActive(true);
            }
        }
        else
        {
            if (Input.GetKeyDown(KeyCode.Z))
            {
                opSkipClip.Play();
                OpenignEnd();
            }
        }
    }

    // ���悪�I�������Ƃ��ɌĂяo����郁�\�b�h
    void OnVideoEnd(VideoPlayer vp)
    {
        OpenignEnd();
    }

    void OnDestroy()
    {
        // �j�����ɃC�x���g��������i���������[�N�h�~�j
        videoPlayer.loopPointReached -= OnVideoEnd;

    }

    IEnumerator PlayVideoWithDelay(int delayFrames)
    {
        // 5�t���[���ҋ@
        for (int i = 0; i < delayFrames; i++)
        {
            yield return null;  // 1�t���[���ҋ@
        }

        // ����̍Đ����J�n
        videoPlayer.Play();
        bgmSource.Play();
    }

    private IEnumerator CheckBGMBGMEnd()
    {
        while (true)
        {
            yield return null;  // ���t���[���m�F

            // BGM�̍Đ����I������ꍇ
            if (!bgmSource.isPlaying)
            {
                // ��������v���C����

                // ������ŏ�����Đ�
                videoPlayer.time = 0;
                texture.SetActive(true);
                skipHelp.SetActive(false);
                stertPanel.SetActive(false);

                videoPlayer.Play();
                bgmSource.Play();


                // �ēxBGM���I���̂�҂��߂̑ҋ@��ǉ�
                yield return new WaitUntil(() => bgmSource.isPlaying == false);
            }
        }
    }
    private void OpenignEnd()
    {
        videoPlayer.Stop();
        texture.SetActive(false);
        stertPanel.SetActive(true);

    }

    public void OnStert(InputAction.CallbackContext context)
    {
        if (context.performed)
        {
            if(skipHelp.activeSelf ==true)
            {
                opSkipClip.Play();
                OpenignEnd();
            }

        }
    }

}
