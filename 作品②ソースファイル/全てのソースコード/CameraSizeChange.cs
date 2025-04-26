using System;
using System.Collections;
using System.Collections.Generic;
using Unity.Mathematics;
using UnityEngine;

[DefaultExecutionOrder(0)] public class CameraSizeChange : MonoBehaviour
{
    // 1P�J������2P�J�����̍����ő�T�C�Y(�J����1��orthographicSize + �J����2��orthographicSize)�ȉ��ɂȂ������ʐ؂�ւ�
    [SerializeField, Header("�J���������t���[�������")] private int perFrame = 30;
    private float frameRatio;

    private GameObject boundaryLine;
    private RectTransform boundaryLineRectTransform;                                     // UI��RectTransform�擾
    private float boundaryLineHeight;                                                    // ���E���̍����擾

    [SerializeField, Header("�v���C���[1�̃J�����T�C�Y")] private float camera1pSize = 6;
    [SerializeField, Header("�v���C���[2�̃J�����T�C�Y")] private float camera2pSize = 4;

    private int camera1pSizeMax;
    private int camera2pSizeMax;

    private float ratio1P;                                                               // 1p�J�����T�C�Y�̔�
    private float ratio2P;                                                               // 2p�J�����T�C�Y�̔�
    private float ratioMax;                                                              // ��𑫂�������
    private float screenRatio1P;                                                         // �v���C���[1�̉�ʔ䗦
    private float screenRatio2P;                                                         // �v���C���[2�̉�ʔ䗦

    private Camera camera1P;                                                             // �J����1��Camera�R���|�[�l���g���擾
    private Camera camera2P;                                                             // �J����2��Camera�R���|�[�l���g���擾

    private float cameraSizeMax = 0;                                                     // �J����1�ƃJ����2�̍��v�T�C�Y
    //private float camera1PSize = 0;                                                      // �J����1��orthographicSize
    //private float camera2PSize = 0;                                                      // �J����2��orthographicSize

    private bool union = false;                                                          // �J��������������Ă��邩
    private bool separation = false;                                                     // �����t���O
    private float oldUnionRatio = 0.0f;                                                  // 1�t���[���O�̃J���������䗦
    private float unionRatio = 0.0f;                                                     // �J���������䗦

    private float unionCameraHeight = 0.0f;
    private float whenUnionCameraHeight = 0.0f;
    private bool unionCameraHeightFlag = true;

    private bool sizeCange = true;

    // Start is called before the first frame update
    private void Start()
    {
        camera1pSizeMax = (int)camera1pSize;
        camera2pSizeMax = (int)camera2pSize;

        camera1P.orthographicSize = camera1pSize;
        camera2P.orthographicSize = camera2pSize;
        cameraSizeMax = camera1pSize + camera2pSize;

        /*
        float gcd = Gcd((int)camera1pSize, (int)camera2pSize);
        ratio1P = camera1pSize / gcd;
        ratio2P = camera2pSize / gcd;
        ratioMax = ratio1P + ratio2P;
        */

        boundaryLine.TryGetComponent(out boundaryLineRectTransform);

        boundaryLineHeight = (1080 * (1.0f / ratioMax) * ratio1P) - 540;
        boundaryLineRectTransform.localPosition = new Vector3(boundaryLineRectTransform.localPosition.x, boundaryLineHeight, 0);

        float r = (1.0f / (ratio1P + ratio2P));
        screenRatio1P = ratio1P * r;
        screenRatio2P = ratio2P * r;
        frameRatio = 1.0f / perFrame;

        union = true;
        camera1P.rect = new Rect(0, 0, 1, 1);
        camera1P.orthographicSize = cameraSizeMax;
        camera2P.rect = new Rect(0, 0, 0, 0);
        camera2P.orthographicSize = 0;
        boundaryLine.SetActive(false);

        whenUnionCameraHeight = camera1P.transform.position.y;
    }

    // Update is called once per frame
    public void Update()
    {
        if (sizeCange)
        {
            float subHeight = camera2P.transform.position.y - camera1P.transform.position.y;
            float sub = subHeight - (cameraSizeMax);

            if (sub <= 0.0f && !separation)
            {
                if (!unionCameraHeightFlag)
                {
                    unionCameraHeightFlag = true;
                    whenUnionCameraHeight = camera1P.transform.position.y;
                }
                if (Union(true))
                {
                    //union = true;
                    camera1P.rect = new Rect(0, 0, 1, 1);
                    camera1P.orthographicSize = cameraSizeMax;
                    camera2P.rect = new Rect(0, 0, 0, 0);
                    camera2P.orthographicSize = 0;
                    boundaryLine.SetActive(true);
                }
            }
            else
            {
                if (Union(false))
                {
                    union = false;
                    separation = false;
                    unionCameraHeightFlag = false;
                    camera1P.rect = new Rect(0, 0, 1, screenRatio1P);
                    camera2P.rect = new Rect(0, screenRatio1P, 1, screenRatio2P);
                    camera1P.orthographicSize = camera1pSize;
                    camera2P.orthographicSize = camera2pSize;
                    //boundaryLineRectTransform.position = new Vector3(Screen.width * 0.5f, boundaryLineHeight, 0);
                    boundaryLine.SetActive(true);

                }
            }
        }
    }

    private bool Union(bool u)
    {
        oldUnionRatio = unionRatio;
        unionRatio += (u ? -frameRatio : frameRatio);
        if (unionRatio < 0.0f) unionRatio = 0.0f;
        if (1.0f < unionRatio) unionRatio = 1.0f;
        if (oldUnionRatio == unionRatio) return true;
        float r = EaseOutExpo(unionRatio);
        camera1P.rect = new Rect(0, 0, 1, screenRatio1P + screenRatio2P * (1 - r));
        camera2P.rect = new Rect(0, screenRatio1P + screenRatio2P * (1 - r), 1, screenRatio2P * (r));
        camera1P.orthographicSize = camera1pSize + camera2pSize * (1 - r);
        camera2P.orthographicSize = camera2pSize * (r);
        boundaryLineRectTransform.localPosition = new Vector3(boundaryLineRectTransform.localPosition.x, boundaryLineHeight + 540 * (1 - r), 0);
        if(u) camera1P.transform.position = new Vector3(camera1P.transform.position.x, whenUnionCameraHeight + (unionCameraHeight * (1 - r)), camera1P.transform.position.z);
        boundaryLine.SetActive(true);
        union = u;
        return false;
    }

    private float EaseOutExpo(float inputValue) { return (inputValue == 1.0f ? 1.0f : 1.0f - Mathf.Pow(2, (-10 * inputValue))); }

    public bool GetUnion() { return union; }

    public void Setting(Camera c1p, Camera c2p, GameObject bl)
    {
        camera1P = c1p;
        camera2P = c2p;
        boundaryLine = bl;
    }

    public void SetCameraHeight()
    {
        float gcd = Gcd((int)camera1pSize, (int)camera2pSize);
        ratio1P = camera1pSize / gcd;
        ratio2P = camera2pSize / gcd;
        ratioMax = ratio1P + ratio2P;

        unionCameraHeight = ((camera2P.transform.position.y - camera1P.transform.position.y) / ratioMax);
    }

    public void SetSeparation()
    {
        separation = true;
    }


    public void SetScreenSize(float s)
    {
        cameraSizeMax = s;
    }

    public float GetScreenSize()
    {
        return cameraSizeMax;
    }

    public Vector2 GetCameraSize()
    {
        return new Vector2(camera1pSize, camera2pSize);
    }

    public Vector2 GetCameraSizeMax()
    {
        return new Vector2(camera1pSizeMax, camera2pSizeMax);
    }

    public Vector2 GetCameraRatio()
    {
        return new Vector2(screenRatio1P, screenRatio2P);
    }

    public void SetSizeCange(bool sc)
    {
        sizeCange = sc;
    }

    public void SetCameraSize(Vector2 s)
    {
        camera1pSize = s.x;
        camera2pSize = s.y;
    }

    public void Skip()
    {
        unionRatio = 0.99f;
    }

    // ���[�N���b�h�̌ݏ��@�ɂ��A�ő����
    private int Gcd(int a, int b)
    {
        Func<int, int, int> gcd = null;
        gcd = (x, y) => y == 0 ? x : gcd(y, x % y);
        return a > b ? gcd(a, b) : gcd(b, a);
    }

    static Vector2 GetRectSize(RectTransform self)
    {
        var parent = self.parent as RectTransform;
        if (parent == null)
        {
            return new Vector2(self.rect.width, self.rect.height);
        }
        // �}�؂菈���B����͂Ȃ������悢�ꍇ������B
        if (parent.anchorMin == parent.anchorMax)
        {
            return parent.sizeDelta;
        }
        var parentSize = GetRectSize(parent);
        var anchor = self.anchorMax - self.anchorMin;
        var width = (parentSize.x * anchor.x) + self.sizeDelta.x;
        var height = (parentSize.y * anchor.y) + self.sizeDelta.y;
        return new Vector2(width, height);
    }
}
