using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class DoubleStartZoomIn : MonoBehaviour
{
    private CameraSizeChange cameraSizeChange;

    private float zoomRatio;

    private float camera1pSizeMax;
    private float camera2pSizeMax;

    private float camera1pSize;
    private float camera2pSize;

    private float camera1pSizeSub;
    private float camera2pSizeSub;

    private int animationFrame;

    private float animationRatio = 0.0f;

    private float ratio = 0.0f;

    private bool nowZoomOut = false;

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out cameraSizeChange);
        var size = cameraSizeChange.GetCameraSizeMax();

        camera1pSizeMax = size.x;
        camera2pSizeMax = size.y;

        camera1pSize = camera1pSizeMax / zoomRatio;
        camera2pSize = camera2pSizeMax / zoomRatio;

        camera1pSizeSub = camera1pSizeMax - camera1pSize;
        camera2pSizeSub = camera2pSizeMax - camera2pSize;


        animationRatio = 1.0f / animationFrame;

        /*
        startSize = cameraSizeMax / zoomRatio;
        cameraSizeChange.SetScreenSize(startSize);

        animationRatio = 1.0f / animationFrame;

        sizeSub = cameraSizeMax - startSize;
        */
    }

    // Update is called once per frame
    void Update()
    {
        if (nowZoomOut)
        {
            ratio += animationRatio;
            if (1.0f < ratio) ratio = 1.0f;
            float r = EaseInSine(ratio);
            cameraSizeChange.SetCameraSize(new Vector2(camera1pSize + (camera1pSizeSub * r), camera2pSize + (camera2pSizeSub * r)));

            if (ratio == 1.0f) nowZoomOut = false; ;
        }
    }

    public void Setting(float zr, int af)
    {
        zoomRatio = zr;
        animationFrame = af;
    }

    public void StartZoomOut()
    {
        nowZoomOut = true;
    }

    public void Skip()
    {
        cameraSizeChange.SetCameraSize(new Vector2(camera1pSizeMax, camera2pSizeMax));
        nowZoomOut = false;
        //Destroy(this);
    }

    public bool GetNowZoomOut()
    {
        return nowZoomOut;
    }

    //private float EaseOutExpo(float inputValue) { return (inputValue == 1.0f ? 1.0f : 1.0f - Mathf.Pow(2, (-10 * inputValue))); }

    private float EaseInSine(float inputValue) { return 1 - Mathf.Cos((inputValue * Mathf.PI) / 2); }
}
