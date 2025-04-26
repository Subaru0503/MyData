using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    [SerializeField] GameObject _TutorialPanel;
    [SerializeField] GameObject _PosePanel;
    [SerializeField] GameObject _GoalPanel;
    [SerializeField] GameObject _GameOverPanel;
    [SerializeField] private PlayerInputManager _inputManager;

    [SerializeField] private int _dropBlocks;
    [SerializeField] private int _useItem;
    [SerializeField] private static bool _TutorialFlug = true;
    [SerializeField] public int StageNum;
    [SerializeField] public MainCameraManager _mCManager; // メインカメラマネージャー
    private SoundManager _SoundManager;

    // Start is called before the first frame update
    void Start()
    {
        _SoundManager = GetComponent<SoundManager>();
        _dropBlocks = 0;
        _useItem = 0;

        if(_TutorialFlug)
        {
            _TutorialPanel.SetActive(true);
            _inputManager.ToggleEnable(false);
            Time.timeScale = 1;
        }
        else
        {
            Time.timeScale = 1;
            _mCManager.StartCameraAnimation();
        }

    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.Z))
        {
            StartSkip();
        }
        // "Escape"キーが押されたらポーズを切り替える
        if(_mCManager.GetEndStartAnimationReady())
        {
            if (Input.GetKeyDown(KeyCode.Escape))
            {
                if (Time.timeScale == 1) // このやり方だとNintendoコントローラーｔ
                {
                    GamePose();
                }
                else
                {
                    GameResume();
                }
            }
        }

 

    }
    public void GameClear()
    {
        Time.timeScale = 0;
        _inputManager.ToggleEnable(false);
        _GoalPanel.SetActive(true);
    }
    public void GameOver()
    {
        _SoundManager.PlayerSound(3);
        Time.timeScale = 0;
        _inputManager.ToggleEnable(false);
        _GameOverPanel.SetActive(true);
    }
   public void GamePose()
    {
        if (!_mCManager.GetEndStartAnimationReady()) return;
        _SoundManager.PlayerSound(0);
        Time.timeScale = 0;
        _inputManager.ToggleEnable(false);
        _PosePanel.SetActive(true);
    }
    public void GameResume()
    {
        _SoundManager.PlayerSound(1);
        Time.timeScale = 1;
        _inputManager.ToggleEnable(true);
        _PosePanel.SetActive(false);

    }
    public void GameRetry()
    {
        StartCoroutine(ExecuteGameRetry());
    }
    private IEnumerator ExecuteGameRetry()
    {
        yield return new WaitForSecondsRealtime(1.2f);
        Time.timeScale = 1;
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    public void GameTutorialEnd()
    {
        _TutorialPanel.SetActive(false);
        _mCManager.StartCameraAnimation();
        Time.timeScale = 1;

        _TutorialFlug = false;
    }

    public void StartSkip()
    {
        if(_mCManager.GetStartAnimation())
        {
            _mCManager.Skip();
        }
    }





    // セッターゲッター
    public void AddDropBlocks()
    { _dropBlocks++; }
    public void AddUseItem()
    { _useItem++;}

    public int GetDropBlocks()
    {return _dropBlocks; }
    public int GetUseItem()
    { return _useItem; }


}
