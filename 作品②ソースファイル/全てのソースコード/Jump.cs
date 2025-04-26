using UnityEngine;

public class Jump : MonoBehaviour
{
    private Rigidbody2D rb;
    [SerializeField] public float jumpForce = 5f; // �W�����v��
    [SerializeField] private bool isGrounded = false; // �n�ʂɂ��邩�ǂ����̃t���O

    // �n�ʂ̔�������邽�߂̃��C���[�}�X�N
    [SerializeField] private LayerMask groundLayer;
    [SerializeField] private Vector2 groundCheckPos;
    [SerializeField] private Vector2 groundCheckSize; // �l�p�`�̃T�C�Y

    // �Ζʂ̃W�����v�͒����p
    private float slopeAngleThreshold = 45f; // ���̊p�x�𒴂���ƃW�����v�͂�␳
    private float minJumpForce = 4f; // �Œ�W�����v��

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    public void Jumping()
    {
        // �W�����v����
        if (isGrounded)
        {
            rb.velocity = new Vector2(rb.velocity.x, 0);

            // �n�ʂ̊p�x�ɉ������W�����v�͂̕␳
            float adjustedJumpForce = AdjustJumpForceBasedOnSlope();

            // �W�����v�����s
            rb.AddForce(new Vector2(0, adjustedJumpForce), ForceMode2D.Impulse);
        }
    }

    private void Update()
    {
        // �v���C���[�̃��[�J����ԂɊ�Â��� groundCheckPos ���v�Z
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(groundCheckPos);

        // �v���C���[�̉�]�p�Ɋ�Â��ċ�`�̊p�x��ݒ�
        float rotationZ = transform.eulerAngles.z;

        // OverlapBox�Őڒn�𔻒�
        isGrounded = Physics2D.OverlapBox(checkPos, groundCheckSize, rotationZ, groundLayer);
    }

    private float AdjustJumpForceBasedOnSlope()
    {
        // �L�����N�^�[�̑����Ƀ��C���΂��A�n�ʂ̊p�x���擾
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, groundCheckSize.y / 2 + 0.1f, groundLayer);

        if (hit.collider != null)
        {
            // �n�ʂ̖@���x�N�g������p�x���擾
            Vector2 groundNormal = hit.normal;
            float slopeAngle = Vector2.Angle(groundNormal, Vector2.up);

            // �Ζʂ����ȏ�̊p�x�Ȃ�W�����v�͂�␳
            if (slopeAngle > slopeAngleThreshold)
            {
                return Mathf.Max(minJumpForce, jumpForce * Mathf.Cos(slopeAngle * Mathf.Deg2Rad));
            }
        }

        // �ΖʂłȂ��ꍇ�͒ʏ�̃W�����v�͂�Ԃ�
        return jumpForce;
    }

    // �f�o�b�O�p�M�Y��
    private void OnDrawGizmos()
    {
        // �v���C���[�̃��[�J����ԂɊ�Â��� groundCheckPos ���v�Z
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(groundCheckPos);

        // �v���C���[�̉�]�p�Ɋ�Â��ċ�`�̊p�x��ݒ�
        float rotationZ = transform.eulerAngles.z;

        // Gizmos�̉�]�s���ݒ肵�āA��`��`��
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, rotationZ), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, groundCheckSize);
    }

    public bool IsGrounded()
    {
        return isGrounded;
    }
}