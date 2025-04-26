using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
//using UnityEditor.SceneManagement;
using UnityEngine;
using UnityEngine.InputSystem;
using static UnityEngine.ParticleSystem;

[RequireComponent(typeof(CameraSizeChange))]

[DefaultExecutionOrder(-5)] public class MainCameraManager : MonoBehaviour
{
    [SerializeField, Header("境界線用UIをアタッチ")] private GameObject boundaryLine;
    [SerializeField, Header("ReadyGoをアタッチ")] private GameObject readyGo;
    //[SerializeField, Header("開始時のアニメーションフレーム")] private int startFrame = 30;
    [SerializeField, Header("プレイヤー追従速度")] private float followSpeed = 3.0f;
    [SerializeField, Header("カメラの注視点とプレイヤーの高さの差")] private float offsetHeight = -1.0f;

    [SerializeField, Header("このステージはカメラ追従をするか")] private bool isFollow = false;

    [SerializeField, Header("ゴール後の拡大率")] private float zoomRatio = 1.5f;
    [SerializeField, Header("ゴール後の拡大フレーム")] private int zoomInFrame = 30;
    [SerializeField, Header("ゴール後のティルトフレーム")] private int goalTiltFrame = 180;
    [SerializeField, Header("ゴール後拡大するまでのディレイ")] private int delay = 1;

    [SerializeField, Header("プレイヤー1Pの初期位置")] private GameObject player1pPos;
    [SerializeField, Header("プレイヤー2Pの初期位置")] private GameObject player2pPos;

    private CameraSizeChange cameraSizeChange;

    private ReadyGo readyGoScript;

    private GameObject camera1P;                                                             // カメラ1のCameraコンポーネントを取得
    private GameObject camera2P;                                                             // カメラ2のCameraコンポーネントを取得
    private GameObject startCamera;                                                          // スタートカメラを取得
    private StartCameraManager startCameraManager;

    private GameObject player1P;
    private GameObject player2P;

    private PlayerInputManager playerInputManager;

    private StartZoomIn startZoomIn;

    private bool skipView = false;
    private GameObject readyGoBro;

    private bool goal = false;
    private bool goalZool= false;
    private bool goalTilt = false;
    private bool goalZoolAfter= false;
    private GoalZoomIn goalZoomIn;
    private CameraTilt cameraTilt;

    void Awake()
    {
        //Screen.SetResolution(1920, 1080, true);
        //Application.targetFrameRate = 60; // 初期状態は-1になっている
    }

    // Start is called before the first frame update
    void Start()
    {
        GameObject.Find("PlayerInputManager").TryGetComponent(out playerInputManager);
        playerInputManager.ToggleEnable(false);

        camera1P = transform.GetChild(0).gameObject;
        camera2P = transform.GetChild(1).gameObject;
        startCamera = transform.GetChild(3).gameObject;
        startCamera.TryGetComponent(out startCameraManager);

        TryGetComponent(out cameraSizeChange);
        readyGo.TryGetComponent(out readyGoScript);

        cameraSizeChange.Setting(camera1P.GetComponent<Camera>(), camera2P.GetComponent<Camera>(), boundaryLine);

        if (isFollow)
        {
            camera2P.transform.position = new Vector3(player2P.transform.position.x, player2P.transform.position.y - 1.0f, -10.0f);
            //camera1P.transform.position = new Vector3(player2P.transform.position.x, player2P.transform.position.y - 1.0f, -10.0f);
            //camera1P.transform.position = new Vector3(camera2P.transform.position.x, player1P.transform.position.y + 1.0f, camera2P.transform.position.z);
            camera1P.transform.position = new Vector3(player2P.transform.position.x, player1P.transform.position.y + 2.0f, -10.0f);
            cameraSizeChange.SetCameraHeight();

            camera1P.AddComponent<FollowPlayer>().Setting(player1P, followSpeed, offsetHeight, camera1P.transform.position.y, player1pPos.transform.position.y);

            // 此処の + 2.0f と　したの + 2.0f は同じ
            //startCameraTilt = camera1P.AddComponent<StartCameraTilt>();
            //startCameraTilt.Setting(startFrame, (player2P.transform.position.y - 1.0f) - (player1P.transform.position.y + 2.0f), camera1P.transform.position.y);

            var info = startCameraManager.GetRatioFrame();
            var dszi = gameObject.AddComponent<DoubleStartZoomIn>();
            dszi.Setting(info.x, (int)info.y);

            startCameraManager.Setting(camera1P,camera2P, boundaryLine, cameraSizeChange, dszi, readyGoScript, (player2P.transform.position.y - 1.0f) - (player1P.transform.position.y + 2.0f));
            /*
             これをレディゴーに渡す
            startCameraManager.GetTotalFrame();
            */

            //readyGoScript.Setting(startCameraManager.GetStartFrame(), playerInputManager);

            readyGoScript.Setting(playerInputManager);

            //print(startCameraManager.GetTotalFrame());
        }
        else
        {
            float h = (player1P.transform.position.y + player2P.transform.position.y) * 0.5f;
            camera1P.transform.position = new Vector3(player2P.transform.position.x, h, -10.0f);
            camera2P.transform.position = new Vector3(player2P.transform.position.x, h, -10.0f);
            cameraSizeChange.SetCameraHeight();

            var info = startCameraManager.GetRatioFrame();
            startZoomIn = gameObject.AddComponent<StartZoomIn>();
            startZoomIn.Setting(info.x, (int)info.y, readyGoScript);
            readyGoScript.Setting(playerInputManager);

            /*
                こっちは
            info.yを渡すか同じフレームを渡すか
            */

            Destroy(startCamera);
        }

        readyGoBro = readyGo.transform.parent.GetChild(1).gameObject;
        readyGoBro.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (skipView)
        {
            if (!GetStartAnimation())
            {
                skipView = false;
                readyGoBro.SetActive(false);
            }
        }

        if (goal)
        {
            if (goalZool)
            {
                if (goalZoomIn.GetEndZoom())
                {
                    if (isFollow)
                    {
                        StartCoroutine(ClearTilt());
                        goalZool = false;
                    }
                }
            }
            else if (goalTilt)
            {
                if (cameraTilt.GetEndTilt())
                {
                    Destroy(camera1P.GetComponent<CameraTilt>());
                    goalZoomIn = camera1P.AddComponent<GoalZoomIn>();
                    goalZoomIn.Setting(zoomRatio, zoomInFrame, player2pPos.transform.position.y);
                    goalTilt = false;
                    goalZoolAfter = true;
                }
            }
            else if (goalZoolAfter)
            {
                if (goalZoomIn.GetEndZoom()) Destroy(camera1P.GetComponent<GoalZoomIn>());
            }
        }

        if (Input.GetKeyDown(KeyCode.V)) StartCoroutine(Shake(0.2f,0.3f));
    }

    public void SetPlayer(GameObject p1p, GameObject p2p)
    {
        player1P = p1p;
        player2P = p2p;
    }

    public void GameClear()
    {
        //StartCoroutine(ClearAnimationStart());
        goal = true;
        goalZool = true;
        goalZoomIn = camera1P.AddComponent<GoalZoomIn>();
        goalZoomIn. Setting(zoomRatio, zoomInFrame, player2pPos.transform.position.y);
        cameraSizeChange.SetSizeCange(false);

        //Destroy(cameraSizeChange);
    }

    public void Skip()
    {
        readyGoScript.Skip();
        if (isFollow)
        {
            cameraSizeChange.Skip();
            startCameraManager.Skip();
        }
        else
        {
            startZoomIn.Skip();
        }
    }

    public bool GetStartAnimation() 
    { 
        if (isFollow)   return startCameraManager.GetNowStartAnimation();
        else            return startZoomIn.GetNowZoomOut();
    }

    public bool GetEndStartAnimationReady()
    {
        if (isFollow) return !startCameraManager.GetNowStartAnimation() && readyGoScript.endReadyGo;
        else return !startZoomIn.GetNowZoomOut() && readyGoScript.endReadyGo;
    }

    public void StartCameraAnimation()
    {
        skipView = true;
        readyGoBro.SetActive(true);
        if (isFollow) startCameraManager.StartCameraAnimation();
        else startZoomIn.StartZoom();
    }

    public int GetGoalAnimationFrame()
    {

        if (isFollow)   return (((zoomInFrame + goalTiltFrame + zoomInFrame) / 60) + delay);
        else            return ((zoomInFrame / 60));
    }

    IEnumerator ClearTilt()
    {
        yield return new WaitForSeconds(delay);

        cameraTilt = camera1P.AddComponent<CameraTilt>();

        if (isFollow)
        {
            camera1P.transform.position = new Vector3(camera1P.transform.position.x, player1pPos.transform.position.y + 2.0f, -10);
            cameraTilt.Setting(goalTiltFrame, (player1pPos.transform.position.y + 2.0f - player2pPos.transform.position.y), player1pPos.transform.position.y + 2.0f);
        }
        else
        {
            float h = (player1pPos.transform.position.y + player2pPos.transform.position.y) * 0.5f;
            camera1P.transform.position = new Vector3(camera1P.transform.position.x, h, -10);
            cameraTilt.Setting(goalTiltFrame, 0, h);
        }

        camera1P.GetComponent<Camera>().orthographicSize = cameraSizeChange.GetScreenSize();

        goalTilt = true;
        Destroy(camera1P.GetComponent<FollowPlayer>());
        Destroy(camera1P.GetComponent<GoalZoomIn>());
    }

    // 揺れる時間, 震度
    public IEnumerator Shake(float duration, float magnitude)
    {
        Vector3 originalPosition = camera1P.transform.position;
        float elapsed = 0f;

        while (elapsed < duration)
        {
            camera1P.transform.position = originalPosition + Random.insideUnitSphere * magnitude;
            elapsed += Time.deltaTime;
            yield return null;
        }
        camera1P.transform.position = originalPosition;
    }
}
