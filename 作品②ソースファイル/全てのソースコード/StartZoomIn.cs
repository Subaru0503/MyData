using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

[DefaultExecutionOrder(3)]
public class StartZoomIn : MonoBehaviour
{
    private float zoomRatio = 1.5f;

    private CameraSizeChange cameraSizeChange;
    private ReadyGo readyGo;

    private float cameraSizeMax;
    private float startSize;

    private float cameraSize;

    private int animationFrame;

    private float animationRatio = 0.0f;

    private float ratio = 0.0f;

    private float sizeSub = 0.0f;

    private bool nowZoomOut = false;

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out cameraSizeChange);
        cameraSizeMax = cameraSizeChange.GetScreenSize();

        startSize = cameraSizeMax / zoomRatio;
        cameraSizeChange.SetScreenSize(startSize);

        animationRatio = 1.0f / animationFrame;

        sizeSub = cameraSizeMax - startSize;
    }

    // Update is called once per frame
    void Update()
    {
        if (nowZoomOut)
        {
            ratio += animationRatio;
            if (1.0f < ratio) ratio = 1.0f;
            cameraSizeChange.SetScreenSize(startSize + sizeSub * EaseInSine(ratio));

            if (ratio == 1.0f)
            {
                //cameraSizeChange.SetScreenSize(cameraSizeMax);
                //readyGo.StartReady();
                //Destroy(this);
                readyGo.StartReady();
                nowZoomOut = false;
                enabled = false;
            }
        }
    }

    public void Setting(float zr, int af, ReadyGo r)
    {
        zoomRatio = zr;
        animationFrame = af;
        readyGo = r;
    }

    public void Skip()
    {
        if (nowZoomOut)
        {
            cameraSizeChange.SetScreenSize(cameraSizeMax);
            nowZoomOut = false;
            enabled = false;
        }
    }

    public bool GetNowZoomOut()
    {
        return nowZoomOut;
    }

    public void StartZoom()
    {
        nowZoomOut = true;
    }


    //private float EaseOutExpo(float inputValue) { return (inputValue == 1.0f ? 1.0f : 1.0f - Mathf.Pow(2, (-10 * inputValue))); }
    private float EaseInSine(float inputValue) { return 1 - Mathf.Cos((inputValue * Mathf.PI) / 2); }
}
