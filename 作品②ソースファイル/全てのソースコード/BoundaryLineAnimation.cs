using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[DefaultExecutionOrder(3)] public class BoundaryLineAnimation : MonoBehaviour
{
    private RectTransform t;
    private RectTransform n;
    private RectTransform b;

    private bool nowAnimasion = false;

    private int animationFrame;

    private int yarnAnimationFrame;
    private int needleAnimationFrame;

    private bool yarnAnimation = true;
    private bool needleAnimation = false;

    private float yarnStartX = 1070;
    private float yarnGoalX = 970;
    private float yarnSub;

    private float yarnRatio = 0.0f;
    private float yarnAddRatio = 0.0f;

    private float needleStartX = 1200;
    private float needleGoalX = -850;
    private float needleSub;

    //private float threadStartSizeX = -1920;
    private float threadStartSizeX = -2420;
    private float threadGoalSizeX = -360;
    private float threadSub;

    private float needleRatio = 0.0f;
    private float needleAddRatio = 0.0f;

    // Start is called before the first frame update
    void Start()
    {
        gameObject.SetActive(false);

        transform.GetChild(0).gameObject.TryGetComponent(out t);
        transform.GetChild(1).gameObject.TryGetComponent(out n);
        transform.GetChild(2).gameObject.TryGetComponent(out b);

        yarnAnimationFrame = (int)((animationFrame / 10.0f) * 3);
        needleAnimationFrame = animationFrame - yarnAnimationFrame;

        yarnAddRatio = 1.0f / yarnAnimationFrame;
        needleAddRatio = 1.0f / needleAnimationFrame;

        yarnSub = yarnGoalX - yarnStartX;
        needleSub = needleGoalX - needleStartX;
        threadSub = threadGoalSizeX - threadStartSizeX;

        b.localPosition = new Vector3(yarnStartX, b.localPosition.y, b.localPosition.z);
        n.localPosition = new Vector3(needleStartX, n.localPosition.y, n.localPosition.z);
        t.sizeDelta = new Vector2(threadStartSizeX, t.sizeDelta.y);

        // ぱっと出てくるのではなく 毛糸が転がってくる -> 針と糸が右までいく
        // の方がいいかも

        // 毛糸玉は1070 から 970 
        // いとも位置を
        // 糸 1860 から 300　サイズ
        // 針は770(1200) から -850
    }

    // Update is called once per frame
    void Update()
    {
        if (nowAnimasion)
        {
            if (yarnAnimation)
            {
                yarnRatio += yarnAddRatio;
                if (1.0f < yarnRatio)
                {
                    yarnRatio = 1.0f;
                    yarnAnimation = false;
                    needleAnimation = true;
                }

                b.localPosition = new Vector3(yarnStartX + (yarnSub * EaseInOutSine(yarnRatio)), b.localPosition.y, b.localPosition.z);
            }

            else if(needleAnimation)
            {
                needleRatio += needleAddRatio;
                if (1.0f < needleRatio) nowAnimasion = false;
                n.localPosition = new Vector3(needleStartX + (needleSub * EaseInOutSine(needleRatio)), n.localPosition.y, n.localPosition.z);
                t.sizeDelta = new Vector2(threadStartSizeX + (threadSub * EaseInOutSine(needleRatio)), t.sizeDelta.y);
            }
        }
    }

    public void StartAnimation()
    {
        nowAnimasion = true;
    }

    public void SetAnimationFrame(int af)
    {
        animationFrame = (int)(af * 1.0f);
    }

    public void Skip()
    {
        b.localPosition = new Vector3(yarnGoalX, b.localPosition.y, b.localPosition.z);
        n.localPosition = new Vector3(needleGoalX, n.localPosition.y, n.localPosition.z);
        t.sizeDelta = new Vector2(threadGoalSizeX, t.sizeDelta.y);
        nowAnimasion = false;
    }

    public bool GetNowAnimasion() {return nowAnimasion;}

    private float EaseInOutSine(float r) { return -(Mathf.Cos(Mathf.PI * r) - 1) / 2; }

}
