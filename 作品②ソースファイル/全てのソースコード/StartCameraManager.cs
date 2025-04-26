using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

[DefaultExecutionOrder(1)] public class StartCameraManager : MonoBehaviour
{
    [SerializeField, Header("スタート時のティルト速度")] private float tiltSpeed = 1.0f;
    [SerializeField, Header("スタート時のカメラ拡大率")] private float zoomRatio = 1.5f;

    [SerializeField, Header("ズームアウトと境界線アニメーションのフレーム")] private int startFrame = 180;
    [SerializeField, Header("スタート時の画面分離フレーム")] private int startSeparationFrame = 30;

    private ReadyGo readyGo;

    private Camera startCamera;

    private GameObject camera1P;
    private GameObject camera2P;
    private CameraSizeChange cameraSizeChange;
    private DoubleStartZoomIn doubleStartZoomIn;

    private GameObject boundaryLine;
    private BoundaryLineAnimation boundaryLineAnimation;

    private float distance = 0.0f;

    private float camera1pSize;
    private float camera2pSize;
    private float cameraSizeMax;

    private float startHeight; 
    private float ratio = 0.0f;
    private float addRatio = 0.0f;

    private bool nowTilt = true;

    private float frameRatio;

    private float camera1pRatio;
    private float camera2pRatio;

    private float screenRatio;

    private bool nowSizeChange = false;

    private int frameCount = 0;

    private bool firstFrame = true;

    private bool nowStartAnimation = false;              // 今スタートアニメーション中か

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out startCamera);
        var size = cameraSizeChange.GetCameraSizeMax();

        camera1pSize = size.x / zoomRatio;
        camera2pSize = size.y / zoomRatio;
        cameraSizeMax = camera1pSize + camera2pSize;

        startCamera.orthographicSize = cameraSizeMax;

        transform.position = camera2P.transform.position;
        startHeight = transform.position.y;

        addRatio = tiltSpeed / distance;

        frameRatio = 1.0f / startSeparationFrame;

        var cameraRatio = cameraSizeChange.GetCameraRatio();
        camera1pRatio = cameraRatio.x;
        camera2pRatio = cameraRatio.y;

        cameraSizeChange.SetCameraSize(new Vector2(camera1pSize, camera2pSize));

        boundaryLine.TryGetComponent(out boundaryLineAnimation);

        boundaryLineAnimation.SetAnimationFrame(startFrame);
    }

    // Update is called once per frame
    void Update()
    {
        if (nowStartAnimation)
        {
            if (nowTilt)
            {
                if ((1.0f - ratio) < addRatio)
                {
                    ratio = 1.0f;
                    nowTilt = false;
                    nowSizeChange = true;
                }
                else ratio += addRatio;

                transform.position = new Vector3(transform.position.x, startHeight - (distance * MyEaseOutBack(ratio)), transform.position.z);
            }

            else if (nowSizeChange)
            {
                ++frameCount;
                if ((1.0f - screenRatio) < frameRatio)
                {
                    screenRatio = 1.0f;
                    nowSizeChange = false;
                }
                else screenRatio += frameRatio;

                float r = EaseOutExpo(screenRatio);

                startCamera.rect = new Rect(0, 0, 1, camera1pRatio + camera2pRatio * (1 - r));
                startCamera.orthographicSize = camera1pSize + camera2pSize * (1 - r);
            }

            else
            {
                if (firstFrame)
                {
                    // スタートカメラの分解中は境界線はSetActive(false);
                    startCamera.rect = new Rect(0, 0, 0, 0);
                    startCamera.orthographicSize = 0;
                    boundaryLineAnimation.StartAnimation();
                    doubleStartZoomIn.StartZoomOut();
                    firstFrame = false;
                    //readyGo.StartReady();
                    //Destroy(this.gameObject);
                }
                else
                {
                    if (!boundaryLineAnimation.GetNowAnimasion() && !doubleStartZoomIn.GetNowZoomOut())
                    {
                        readyGo.StartReady();
                        nowStartAnimation = false;
                        gameObject.SetActive(false);
                    }
                }
            }
        }
    }

    public void StartCameraAnimation()
    {
        nowStartAnimation = true;
    }

    public void Setting(GameObject c1p, GameObject c2p, GameObject bl, CameraSizeChange csc, DoubleStartZoomIn dsz, ReadyGo r, float d)
    {
        camera1P = c1p;
        camera2P = c2p;
        boundaryLine = bl;
        cameraSizeChange = csc;
        doubleStartZoomIn = dsz;
        readyGo = r;
        distance = d;
    }

    public Vector2 GetRatioFrame()
    {
        return new Vector2(zoomRatio, startFrame);
    }

    public int GetTotalFrame() { return ((int)Mathf.Ceil(distance / tiltSpeed) + startFrame + startSeparationFrame); }
    public int GetStartFrame() { return startFrame; }

    public void Skip()
    {
        boundaryLineAnimation.Skip();
        doubleStartZoomIn.Skip();
        nowStartAnimation = false;
        gameObject.SetActive(false);
        //Destroy(this.gameObject);
    }

    public bool GetNowStartAnimation()
    {
        return nowStartAnimation;
    }

    private float EaseInOutSine(float r) { return -(Mathf.Cos(Mathf.PI * r) - 1) / 2; }

    private float EaseOutExpo(float r) { return (r == 1.0f ? 1.0f : 1.0f - Mathf.Pow(2, (-10 * r))); }

    private float EaseOutBack(float r) 
    {
        const float c1 = 1.70158f;
        const float c3 = c1 + 1;

        return 1 + c3 * Mathf.Pow(r - 1, 3) + c1 * Mathf.Pow(r - 1, 2);
    }

    private float MyEaseOutBack(float r)
    {
        const float c1 = 2.70158f;
        const float c3 = c1 + 1f;

        return 1 + c3 * Mathf.Pow(r - 1, 3) + c1 * Mathf.Pow(r - 1, 2);
    }
}
