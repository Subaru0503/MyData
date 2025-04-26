using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

[DefaultExecutionOrder(-10)] public class PlayerInputManager : MonoBehaviour
{
    [SerializeField] private GameObject Player_1;
    [SerializeField] private Transform Player_1_Pos;
    [SerializeField] private GameObject Player_2;
    [SerializeField] private Transform Player_2_Pos;

    [SerializeField] private GameObject MainCamera;

    // Start is called before the first frame update
    void Start()
    {
        Player_1 = Instantiate(Player_1, Player_1_Pos.position, Quaternion.identity);
        Player_2 = Instantiate(Player_2, Player_2_Pos.position, Quaternion.identity);
        MainCamera.GetComponent<MainCameraManager>().SetPlayer(Player_1, Player_2);
        ToggleEnable(true);

    }

    // 0.1�b���A���^�C���Œx�������ē��͂��I��/�I�t�ɂ��郁�\�b�h
    public void ToggleEnable(bool enable)
    {
        StartCoroutine(ToggleInputWithDelay(enable, 0.1f)); // 0.1�b�̒x�����w��
    }

    // �R���[�`���Œx���������s�� (���A���^�C��)
    private IEnumerator ToggleInputWithDelay(bool enable, float delay)
    {
        yield return new WaitForSecondsRealtime(delay); // ���A���^�C���őҋ@

        // Player_1��PlayerInput���I��/�I�t
        Player_1.GetComponent<Player1_Manager>().SetControl(enable);

        // Player_2��PlayerInput���I��/�I�t
        Player_2.GetComponent<Player2_Manager>().SetControl(enable);
    }
}
