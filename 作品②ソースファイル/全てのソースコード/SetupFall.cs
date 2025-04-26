using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SetupFall : MonoBehaviour
{
    // �f�o�b�O�p
    [SerializeField] private bool DebugStage1 = false;
    [SerializeField] private bool DebugStage2 = false;
    [SerializeField] private bool DebugStage3 = false;

    // �X�e�[�W���Ƃ̗���������u���b�N�̎��
    [SerializeField] private GameObject[] Stage1_FallBlock;
    [SerializeField] private GameObject[] Stage2_FallBlock;
    [SerializeField] private GameObject[] Stage3_FallBlock;

    // ���A�u���b�N
    [SerializeField] private GameObject RareBlock;

    // ���W�␳
    [SerializeField] private float offset;

    // �u���b�N�̎���
    [SerializeField] private float blockmass;

    // ���̃u���b�N�𐶐��܂ł̃C���^�[�o��
    [SerializeField] private float interval;

    private bool isDrop;

    // ����������u���b�N�̎�ސ�
    private List<GameObject> blockKind = new List<GameObject>();

    // ���ɗ��Ƃ��u���b�N�̏��
    private GameObject[] next = new GameObject[1];

    // Start is called before the first frame update
    void Awake()
    {
        BlockLoad();    // �u���b�N�ǂݍ���
        isDrop = false;
    }

    // ����������u���b�N�̓ǂݍ���
    private void BlockLoad()
    {
        if (DebugStage1)
        {
            for (int i = 0; i < Stage1_FallBlock.Length; i++)
            {
                blockKind.Add(Stage1_FallBlock[i]);
            }
            return;
        }
        if (DebugStage2)
        {
            for (int i = 0; i < Stage2_FallBlock.Length; i++)
            {
                blockKind.Add(Stage2_FallBlock[i]);
            }
            return;
        }
        if (DebugStage3)
        {
            for (int i = 0; i < Stage3_FallBlock.Length; i++)
            {
                blockKind.Add(Stage3_FallBlock[i]);
            }
            return;
        }
        // �V�[���̖��O�œǂݍ��ރu���b�N��ς���
        switch (SceneManager.GetActiveScene().name)
        {
            // �X�e�[�W1
            case "Stage1Scene":
                for (int i = 0; i < Stage1_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage1_FallBlock[i]);
                }
                break;
            // �X�e�[�W2
            case "Stage2Scene":
                for (int i = 0; i < Stage2_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage2_FallBlock[i]);
                }
                break;
            // �X�e�[�W3
            case "Stage3Scene":
                for (int i = 0; i < Stage3_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage3_FallBlock[i]);
                }
                break;
            // �Y������̂��Ȃ�����
            default:
                Debug.Log("�Y������V�[���̖��O������܂���ł���");
                for (int i = 0; i < Stage1_FallBlock.Length; i++)
                {
                    blockKind.Add(Stage1_FallBlock[i]);
                }
                break;
        }
    }

    // �u���b�N����
    public void CreateBlock()
    {
        // ���A�u���b�N���I
        int num = Random.Range(0, 100);

        Vector3 pos = transform.position;

        // 100���̈��������
        if (num == 0)
        {
            next[0] = Instantiate(RareBlock, pos, Quaternion.identity);
        }
        // �ʏ�u���b�N����
        else
        {
            int index = Random.Range(0, blockKind.Count);

            next[0] = Instantiate(blockKind[index], pos, Quaternion.identity);
        }
    }

    // �u���b�N����
    public void Fall()
    {
        if (!next[0] || isDrop == true) return;

        isDrop = true;
        // �ړ�
        Vector3 nextpos = next[0].transform.position;
        nextpos.y -= 0.5f;
        next[0].transform.position = nextpos;
        StartCoroutine(FallSequence());
    }
    private IEnumerator FallSequence()
    {
        if (next[0] == null) yield break; // next[0] �� null �Ȃ珈���𒆒f

        Vector3 startPos = next[0].transform.position;
        Vector3 endPos = startPos;
        endPos.y -= 0.5f; // �I�����̍���

        float duration = 0.2f; // �A�j���[�V�����̒���
        float elapsedTime = 0;

        // �A�j���[�V�����̎��ԕ��A���X�Ɉʒu��ύX
        while (elapsedTime < duration)
        {
            elapsedTime += Time.deltaTime;
            float t = Mathf.Clamp01(elapsedTime / duration);
            next[0].transform.position = Vector3.Lerp(startPos, endPos, t);
            yield return null; // ���̃t���[���܂ő҂�
        }

        // �R���C�_�[�̗L������Rigidbody2D�̒ǉ�
        PolygonCollider2D polygonCollider2D = next[0].GetComponent<PolygonCollider2D>();
        if (polygonCollider2D)
        {
            polygonCollider2D.enabled = true;
        }
        else
        {
            next[0].GetComponent<BoxCollider2D>().enabled = true;
        }

        next[0].AddComponent<Rigidbody2D>();
        Rigidbody2D rb = next[0].GetComponent<Rigidbody2D>();
        rb.mass = blockmass;
        next[0].GetComponent<NormalSize>().ReSize();
        next[0].GetComponent<FallSpeed>().Setrb();

        next[0] = null;
        isDrop = false;


    }
    // �u���b�N�����J�n�ʒu�̈ړ�
    public void BlockMove(bool Right)
    {
        // null�Ȃ�I��
        if (!next[0]) return;

        // �ړ�
        Vector3 nextpos = next[0].transform.position;

        if(Right)
        {
            nextpos.x = transform.position.x + offset;
        }
        else 
        { 
            nextpos.x = transform.position.x - offset; 
        }
        next[0].transform.position = nextpos;
    }
    public void BlockMoveReset()
    {
        // null�Ȃ�I��
        if (!next[0]) return;

        // �ړ�
        Vector3 nextpos = next[0].transform.position;

        nextpos.x = transform.position.x;
        next[0].transform.position = nextpos;
    }

    // next���
    public GameObject IsNext
    {
        get
        {
            return next[0];
        }
        set
        {
            next[0] = value;
        }
    }

    // �����Ԋu���
    public float IsInterval()
    {
        return interval;
    }
}
