using UnityEngine;

public class Jump : MonoBehaviour
{
    private Rigidbody2D rb;
    [SerializeField] public float jumpForce = 5f; // ジャンプ力
    [SerializeField] private bool isGrounded = false; // 地面にいるかどうかのフラグ

    // 地面の判定をするためのレイヤーマスク
    [SerializeField] private LayerMask groundLayer;
    [SerializeField] private Vector2 groundCheckPos;
    [SerializeField] private Vector2 groundCheckSize; // 四角形のサイズ

    // 斜面のジャンプ力調整用
    private float slopeAngleThreshold = 45f; // この角度を超えるとジャンプ力を補正
    private float minJumpForce = 4f; // 最低ジャンプ力

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    public void Jumping()
    {
        // ジャンプ処理
        if (isGrounded)
        {
            rb.velocity = new Vector2(rb.velocity.x, 0);

            // 地面の角度に応じたジャンプ力の補正
            float adjustedJumpForce = AdjustJumpForceBasedOnSlope();

            // ジャンプを実行
            rb.AddForce(new Vector2(0, adjustedJumpForce), ForceMode2D.Impulse);
        }
    }

    private void Update()
    {
        // プレイヤーのローカル空間に基づいて groundCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(groundCheckPos);

        // プレイヤーの回転角に基づいて矩形の角度を設定
        float rotationZ = transform.eulerAngles.z;

        // OverlapBoxで接地を判定
        isGrounded = Physics2D.OverlapBox(checkPos, groundCheckSize, rotationZ, groundLayer);
    }

    private float AdjustJumpForceBasedOnSlope()
    {
        // キャラクターの足元にレイを飛ばし、地面の角度を取得
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, groundCheckSize.y / 2 + 0.1f, groundLayer);

        if (hit.collider != null)
        {
            // 地面の法線ベクトルから角度を取得
            Vector2 groundNormal = hit.normal;
            float slopeAngle = Vector2.Angle(groundNormal, Vector2.up);

            // 斜面が一定以上の角度ならジャンプ力を補正
            if (slopeAngle > slopeAngleThreshold)
            {
                return Mathf.Max(minJumpForce, jumpForce * Mathf.Cos(slopeAngle * Mathf.Deg2Rad));
            }
        }

        // 斜面でない場合は通常のジャンプ力を返す
        return jumpForce;
    }

    // デバッグ用ギズモ
    private void OnDrawGizmos()
    {
        // プレイヤーのローカル空間に基づいて groundCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(groundCheckPos);

        // プレイヤーの回転角に基づいて矩形の角度を設定
        float rotationZ = transform.eulerAngles.z;

        // Gizmosの回転行列を設定して、矩形を描画
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, rotationZ), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, groundCheckSize);
    }

    public bool IsGrounded()
    {
        return isGrounded;
    }
}