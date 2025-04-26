using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Goal : MonoBehaviour
{
    [SerializeField] private Transform goalLine;        // �S�[�����C��

    [SerializeField] private GameObject countObject;     // �J�E���g�_�E���I�u�W�F�N�g
    [SerializeField] private Sprite[] countNumber = new Sprite[6];
    private Image countImage;
    private RectTransform rectTransform;
    private int oldCount = 0;

    [SerializeField] private Vector2 goalcheckPos;
    [SerializeField] private Vector2 goalcheckSize;     // �l�p�`�̃T�C�Y

    [SerializeField, Header("�I�[�f�B�I�\�[�X�A�^�b�`")] private AudioSource audioSource;
    [SerializeField, Header("�J�E���g�_�E��SE")] private AudioClip countdownSE;
    [SerializeField, Header("�t�B�j�b�V��SE")] private AudioClip finishSE;

    //[SerializeField] private GameManager _game_manager; // �Q�[���}�l�[�W���[

    public float checkTime;                             // �m�F����

    public GameObject goalUI;                           // �S�[��UI

    public bool player_1standby { get; set; }           // �������ҁ`�ҋ@��ԃt���O

    public bool isInArea { get; set; }                  // �g���ɓ����Ă���t���O

    public bool goalFlg { get; set; }                   // �S�[���t���O

    private Player2_Manager _player2_manager;           // �v���C���[2�}�l�[�W���[

    private GameObject player_1;                        // �������ҁ`�̏��
    private GameObject player_2;                        // ��с`�̏��

    private float oldplayer_2pos;                       // ��с`�̉ߋ����W(x)

    //private bool toggle = true;                         // �Ƃ��邪�؂����p�̃t���O

    // Start is called before the first frame update
    void Start()
    {
        player_1standby = false;
        goalFlg = false;
        countObject.TryGetComponent(out countImage);
        countObject.TryGetComponent(out rectTransform);
    }

    private void Update()
    {
        // �v���C���[�̏�񂪂Ȃ������珈�����Ȃ�
        if (!player_1 || !player_2) return;

        // �������ҁ`��x���W�ƍ��킹��
        goalcheckPos.x = player_1.transform.position.x;
    }

    // �S�[���`�F�b�N
    public bool LineCheck()
    {
        // �v���C���[�̎��̎擾
        if(!player_1 || !player_2)
        {
            player_1 = GameObject.Find("Player_1(Clone)");
            player_2 = GameObject.Find("Player_2(Clone)");
            // �R���|�[�l���g�擾
            _player2_manager = player_2.GetComponent<Player2_Manager>();
        }
        // �S�[�����C���𒴂��Ă���
        // �������ҁ`�̐^��ɂ�с`������
        else if(player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f &&
            // ���������ҁ`�Ƃ�с`�̈ʒu����(0.5f�Ȃ̂̓v���C���[�̃X�P�[�����{����1������)
            goalcheckPos.x - goalcheckSize.x / 2.0f <=
            player_2.transform.position.x + 0.5f &&
            goalcheckPos.x + goalcheckSize.x / 2.0f >=
            player_2.transform.position.x - 0.5f &&
            !_player2_manager.Input_move)
        {
            player_1standby = false;        // �ҋ@��ԃt���O��������

            isInArea = true;                // �g���ɓ����Ă���

            Debug.Log("��������");
            return true;
        }
        // �͈͓��ɂ�с`�����邪�����Ă�����
        else if (player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f &&
            // ���������ҁ`�Ƃ�с`�̈ʒu����(0.5f�Ȃ̂̓v���C���[�̃X�P�[�����{����1������)
            goalcheckPos.x - goalcheckSize.x / 2.0f <=
            player_2.transform.position.x + 0.5f &&
            goalcheckPos.x + goalcheckSize.x / 2.0f >=
            player_2.transform.position.x - 0.5f &&
            _player2_manager.Input_move)
        {
            player_1standby = true;         // �ҋ@��ԃt���O���グ��

            isInArea = true;                // �g���ɓ����Ă���

            Debug.Log("��с`�̏������������ĂȂ�");
            return false;
        }
        // �S�[�����C���𒴂������A��с`���^��ɂ��Ȃ�
        else if(player_1.transform.position.y - player_1.transform.localScale.y / 2.0f >=
            goalLine.position.y - goalLine.localScale.y / 2.0f)
        {
            player_1standby = true;         // �ҋ@��ԃt���O���グ��
            isInArea = false;                // �����グ�����t���O��������
            Debug.Log("�ҋ@���");


            return false;
        }

        player_1standby = false;            // �ҋ@��ԃt���O��������
        isInArea = false;                // �����グ�����t���O��������

        return false;
    }

    public void CountDown(float time)
    {
        var c = (int)Mathf.Ceil(time);
        if (c < 0) c = 0;
        if (oldCount != c)
        {
            rectTransform.sizeDelta = new Vector2(1000, 1000);
            if (c == 0) audioSource.PlayOneShot(finishSE);
            else audioSource.PlayOneShot(countdownSE);
        }
        oldCount = c;
        countImage.sprite = countNumber[c];
        rectTransform.sizeDelta = new Vector2(rectTransform.sizeDelta.x - 16.67f, rectTransform.sizeDelta.y - 16.67f);
        countObject.SetActive(true);
    }

    public void CountDownReset()
    {
        countObject.SetActive(false);
        rectTransform.sizeDelta = new Vector2(1000, 1000);
    }

    // �f�o�b�O�p�M�Y��
    private void OnDrawGizmos()
    {
        // �v���C���[�̃��[�J����ԂɊ�Â��� groundCheckPos ���v�Z
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(goalcheckPos);

        // �v���C���[�̉�]�p�Ɋ�Â��ċ�`�̊p�x��ݒ�
        float rotationZ = transform.eulerAngles.z;

        // Gizmos�̉�]�s���ݒ肵�āA��`��`��
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, rotationZ), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, goalcheckSize);
    }
}
