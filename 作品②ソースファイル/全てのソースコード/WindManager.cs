using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WindManager : MonoBehaviour
{
    [SerializeField, Header("���G���A�̃v���t�@�u")] private GameObject windAreaPrefab;
    [SerializeField, Header("���A�j���[�V�����̃v���t�@�u")] private GameObject windAnimationPrefab;

    [SerializeField, Header("���̐����x��")] private GameObject windCaution;

    [SerializeField, Header("Player1�̍������擾")] private Transform player1Transform;
    [SerializeField, Header("Player2�̍������擾")] private Transform player2Transform;

    [SerializeField, Header("���G���A�̉��̍L��")] private float areaWide = 15;

    [SerializeField, Header("�ǂɎՂ��锻��̐����x")] private int precision = 15;
    [SerializeField, Header("���̓����蔻�萶���t���[��(n�t���[�����ɐ���)")] private int generateFrame = 20;
    [SerializeField, Header("���̏o��Ԋu(�t���[��)")] private int windDelay = 30;
    [SerializeField, Header("���̏o�钷��(�t���[��)")] private int windTime = 30;
    [SerializeField, Header("���̗�")] private float windPower = 20.0f;
    [SerializeField, Header("�u���b�N�̃��C���[")] private LayerMask blockLayer;

    [SerializeField, Header("���̐����m��(0 �` 100)")] private int probability = 50;

    [SerializeField, Header("���A�j���[�V�����̐�")] private int windAnimationNum = 7;
    [SerializeField, Header("���A�j���[�V�����̍�")] private float windOffset = 2.0f;
    [SerializeField, Header("���A�j���[�V�����̉��ʒu")] private float windPosX = 15.0f;


    [SerializeField, Header("���C���J�����}�l�[�W���[")] private MainCameraManager mainCameraManager;

    private GameObject player1p;

    private GameObject[] windAnimation;
    private SpriteRenderer[] windRenderer;

    private Transform[] windsTransform;

    private RectTransform windCautionRectTransform;
    private Blinking blinking;
    private BlowOffAnimation blowOffAnimation;

    private AudioSource audioSource;

    private Vector2 checkSize;

    private float playerHeightAdd = 0;
    private float windAreaSize = 0;                                                     // ���G���A���̑傫��
    private float windAreaHeight = 0;

    private int count = 0;

    private bool winding;
    private bool leftToRightBlow;

    private int cautionTime;

    private Vector3 parectScale;

    private int halfWindAnimationNum;

    private bool nextWind = false;

    private CompositeCollider2D windCollider;

    // Start is called before the first frame update
    void Start()
    {
        TryGetComponent(out audioSource);
        TryGetComponent(out windCollider);

        player1p = GameObject.FindWithTag("Player");

        parectScale = transform.lossyScale;

        winding = false;
        windsTransform = new Transform[precision];

        windAnimation = new GameObject[windAnimationNum];
        windRenderer = new SpriteRenderer[windAnimationNum];

        halfWindAnimationNum = (int)Mathf.Floor(windAnimationNum * 0.5f);

        playerHeightAdd = (player1Transform.position.y - 1.0f) + player2Transform.position.y;
        windAreaHeight = playerHeightAdd * 0.5f;
        windAreaSize = (player2Transform.position.y - (player1Transform.position.y - 1.0f)) / precision;  // 1P�v���C���[�̏������܂ł��

        transform.localPosition = new Vector3(0.0f, windAreaHeight, 0.0f);

        leftToRightBlow = (Random.Range(0, 2) == 0 ? true : false);
        nextWind = (Random.Range(0, 100) < probability);

        checkSize = new Vector2(0.01f, windAreaSize);

        for (int i = 0; i < precision; ++i)
        {
            var proto = Instantiate(windAreaPrefab, new Vector3(areaWide * 0.5f * (leftToRightBlow ? -1 : 1), windAreaHeight + (windAreaSize * (i - (precision * 0.5f))), 0.0f), Quaternion.identity, transform);
            windsTransform[i] = proto.transform;
            windsTransform[i].localScale = checkSize / transform.lossyScale;
            proto.GetComponent<BoxCollider2D>().usedByComposite = true;
        }


        Vector3 pos = player1p.transform.position;
        for (int i = 0; i < windAnimationNum; ++i)
        {
            windAnimation[i] = Instantiate(windAnimationPrefab, new Vector3(windPosX * 0.5f * (leftToRightBlow ? -1 : 1), pos.y + ((i - halfWindAnimationNum) * windOffset), 0.0f), Quaternion.identity);
            windAnimation[i].TryGetComponent(out windRenderer[i]);
            windRenderer[i].flipX = leftToRightBlow;
            windAnimation[i].SetActive(false);
        }

        windCaution.TryGetComponent(out windCautionRectTransform);
        windCaution.TryGetComponent(out blinking);
        windCaution.TryGetComponent(out blowOffAnimation);
        blowOffAnimation.Setting(leftToRightBlow);

        cautionTime = windDelay - blinking.GetBlinkingMaxTime();
        windCautionRectTransform.localPosition = new Vector2(700 * (leftToRightBlow ? (-1) : (1)), windCautionRectTransform.localPosition.y);
    }

    // Update is called once per frame
    void Update()
    {
        if (mainCameraManager.GetEndStartAnimationReady() && (Time.timeScale == 1))
        {
            if (winding)                                        // �L��
            {
                ++count;
                if ((count % generateFrame) == 0)
                {
                    float x = areaWide * 0.5f * (leftToRightBlow ? -1 : 1);
                    for (int i = 0; i < 7; ++i) windAnimation[i].SetActive(true);
                    for (int i = 0; i < precision; ++i)
                    {
                        var hit = Physics2D.BoxCast(new Vector2(x, windsTransform[i].position.y), checkSize, 0.0f, new Vector2((leftToRightBlow ? 1 : (-1)), 0.0f), areaWide, blockLayer);
                        if (hit)
                        {
                            Vector3 s = new Vector3(hit.distance + 0.1f, windAreaSize, 0.0f);
                            windsTransform[i].localScale = new Vector3(s.x / parectScale.x, s.y / parectScale.y, s.z / parectScale.z);
                            float r = (hit.distance / areaWide);
                            windsTransform[i].position = new Vector3(x * (1 - r), windsTransform[i].position.y, 0.0f);
                        }
                        else
                        {
                            Vector3 s = new Vector3(areaWide + 0.1f, windAreaSize, 0.0f);
                            windsTransform[i].localScale = new Vector3(s.x / parectScale.x, s.y / parectScale.y, s.z / parectScale.z);
                            windsTransform[i].position = new Vector3(0.0f, windsTransform[i].position.y, 0.0f);
                        }
                    }
                    StartCoroutine(GenerateCollider());
                }
                if (count == windTime)
                {
                    count = 0;
                    winding = false;

                    nextWind = (Random.Range(0, 100) < probability);

                    //leftToRightBlow = !leftToRightBlow;
                    leftToRightBlow = (Random.Range(0, 2) == 1 ? true : false);
                    float x = areaWide * 0.5f * (leftToRightBlow ? -1 : 1);

                    for (int i = 0; i < precision; ++i)
                    {
                        windsTransform[i].position = new Vector2(-x, windsTransform[i].position.y);
                        windsTransform[i].localScale = checkSize / parectScale;
                    }

                    for (int i = 0; i < windAnimationNum; ++i) windAnimation[i].SetActive(false);

                    windCautionRectTransform.localPosition = new Vector2(700 * (leftToRightBlow ? (-1) : (1)), 0.0f);

                    blowOffAnimation.EndAnimation();
                    StartCoroutine(GenerateCollider());
                }
            }
            else                                                // ����
            {
                ++count;
                if (nextWind)
                {
                    if (count == cautionTime)
                    {
                        blinking.StartBlinking(leftToRightBlow);
                    }
                    if (count == windDelay)
                    {
                        count = 0;
                        Vector3 pos = player1p.transform.position;
                        float posX = windPosX * 0.5f * (leftToRightBlow ? -1 : 1);
                        for (int i = 0; i < windAnimationNum; ++i)
                        {
                            windAnimation[i].SetActive(true);
                            windAnimation[i].transform.position = new Vector2(posX, pos.y + ((i - halfWindAnimationNum) * windOffset));
                            windRenderer[i].flipX = leftToRightBlow;
                        }
                        winding = true;
                        nextWind = false;

                        blinking.EndBlinking();
                        blowOffAnimation.StartAnimation(leftToRightBlow);
                    }
                }
                else
                {
                    if (count == windDelay)
                    {
                        nextWind = (Random.Range(0, 100) < probability);
                        count = 0;
                    }
                }
            }
        }

        if (Time.timeScale == 1)
        {
            audioSource.UnPause();
            windCaution.SetActive(true);
        }
        else
        {
            audioSource.Pause();
            windCaution.SetActive(false);
        }
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (!winding) return;
        Rigidbody2D r;
        if (collision.gameObject.TryGetComponent(out r))
        {
            if (collision.gameObject.CompareTag("Block") || collision.gameObject.CompareTag("Player"))
                r.AddForce(new Vector2(windPower * (leftToRightBlow ? 1 : (-1)), 0.0f), ForceMode2D.Force);
            if (collision.gameObject.layer == 7 || collision.gameObject.layer == 10)
                r.AddForce(new Vector2(windPower * (leftToRightBlow ? 1 : (-1)), 0.0f), ForceMode2D.Force);
        }
    }

    IEnumerator GenerateCollider()
    {
        yield return new WaitForSeconds(0.05f);
        windCollider.GenerateGeometry();
    }
}
