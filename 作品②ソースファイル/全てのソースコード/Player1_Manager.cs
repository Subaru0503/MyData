using System.Collections;
using UnityEngine;
using UnityEngine.InputSystem;
using static Unity.Collections.AllocatorManager;

public class Player1_Manager : MonoBehaviour
{
    [SerializeField] private Vector2 Range;
    private Jump _jump;
    private Move _move;
    private float _moveInput; // 移動数値の保存用
    private Animator _animator;
    private Rigidbody2D _rigidbody2D;
    private float _jumpingPointY;
    private SoundManager _soundManager;
    // 落下物の判定をするためのレイヤーマスク
    [SerializeField] private LayerMask _fallingObjectLayer;
    [SerializeField] private Vector2 _fallingObjectCheckPos;
    [SerializeField] private Vector2 _fallingObjectCheckSize; // 四角形のサイズ

    private float _blownAwayInterval = 1.0f;

    private GameManager _gameManager;

    private bool _isControl = false;


    // Start is called before the first frame update
    void Start()
    {
        _jump = GetComponent<Jump>();
        _move = GetComponent<Move>();
        _animator = GetComponent<Animator>();
        _rigidbody2D = GetComponent<Rigidbody2D>();
        _soundManager = GetComponent<SoundManager>();
        _blownAwayInterval = 0.0f;
        _gameManager = GameObject.Find("GameManager").GetComponent<GameManager>();

        _isControl = false;
    }

    private void Update()
    {
        if (_isControl == false) return;


        // オブジェクトがギズモの範囲内かどうかを確認する条件式
        if (transform.position.x >= -(Range.x/2) &&
            transform.position.x <= (Range.x / 2) &&
            transform.position.y >= -(Range.y / 2))
        {
            _animator.SetBool("OutOfRange", false); // 範囲内なら false

        }
        else
        {
            if (_animator.GetBool("OutOfRange") == false)
            {
                _soundManager.PlayerSound(6);
            }
            _animator.SetBool("OutOfRange", true);  // 範囲外なら true

        }

        if (_moveInput > 0 || Input.GetKey(KeyCode.D))
        {
            _move.RightMove();
            _animator.SetInteger("Move", 1);
        }
        else if (_moveInput < 0 || Input.GetKey(KeyCode.A))
        {
            _move.LeftMove();
            _animator.SetInteger("Move", -1);
        }
        else
        {
            _move.ResetValue();
            _animator.SetInteger("Move", 0);
        }



        if (Input.GetKeyDown(KeyCode.Space) && _jump.IsGrounded()) // ジャンプ
        {

            // しゃがみアニメーションを再生
            if (_animator.GetBool("OutOfRange") == false)
            {
                _animator.SetTrigger("Crouch");
                _animator.SetBool("Jump", true);
            }
            StartCoroutine(JumpSequence());
            _jumpingPointY = transform.position.y - 0.1f;
            _soundManager.PlayerSound(2); // インデックスの2番　ジャンプサウンド
        }

        if (_rigidbody2D.velocity.y < 0 && !_jump.IsGrounded())
        {

            _animator.SetBool("Jump", false);
            _animator.SetBool("Fall", true);
            if (_jumpingPointY > transform.position.y)
            {
                _animator.SetBool("FallHard", true);
            }

        }
        else
        {
            if (_animator.GetBool("Fall") || _animator.GetBool("FallHard"))
            {

                _animator.SetBool("Fall", false);
                _animator.SetBool("FallHard", false);
                _soundManager.PlayerSound(3); // インデックスの2番　ジャンプサウンド
            }
            _animator.SetBool("Fall", false);
            _animator.SetBool("FallHard", false);

        }

        // プレイヤーのローカル空間に基づいて groundCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(_fallingObjectCheckPos);

        // プレイヤーの回転角に基づいて矩形の角度を設定
        float rotationZ = transform.eulerAngles.z;

        Collider2D collider = Physics2D.OverlapBox(checkPos, _fallingObjectCheckSize, rotationZ, _fallingObjectLayer);

        // OverlapBoxで接地を判定
        if (collider)
        {
            Rigidbody2D rb = collider.GetComponent<Rigidbody2D>();
            if (rb != null)
            {
                if (rb.velocity.magnitude >= 3)
                {
                    BlownAway();
                }

            }

        }


        _blownAwayInterval += Time.deltaTime;

    }

    private void BlownAway()
    {
        if (_blownAwayInterval >= 1.0f)
        {
            bool randomBool = Random.Range(0, 2) == 1;  // 0 なら false、1 なら true
            _animator.SetBool("BlownAwayState", randomBool);
            _animator.SetTrigger("BlownAway");

            if (!_animator.GetCurrentAnimatorStateInfo(0).IsName("Player1_BlownAway") && !_animator.GetCurrentAnimatorStateInfo(0).IsName("Player1_BlownAway2"))
            {
                _soundManager.PlayerSound(4); // インデックスの4番　頭をぶつけた
            }

            _blownAwayInterval = 0.0f;
        }



    }
    private IEnumerator JumpSequence()
    {


        // アニメーションの長さ分待つ（しゃがみの時間を仮に0.5秒としています）
        yield return new WaitForSeconds(0.05f);

        // 実際のジャンプ処理
        _jump.Jumping();


    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        // オブジェクトの位置を基準に四角形を描画
        Vector3 halfSize = new Vector3(Range.x / 2, Range.y / 2, 0);

        // 四角形の頂点を計算して描画
        Vector3 topLeft = new Vector3(-halfSize.x, halfSize.y, 0);
        Vector3 topRight = new Vector3(halfSize.x, halfSize.y, 0);
        Vector3 bottomLeft = new Vector3(-halfSize.x, -halfSize.y, 0);
        Vector3 bottomRight = new Vector3(halfSize.x, -halfSize.y, 0);

        Gizmos.DrawLine(topLeft, topRight);
        Gizmos.DrawLine(topRight, bottomRight);
        Gizmos.DrawLine(bottomRight, bottomLeft);
        Gizmos.DrawLine(bottomLeft, topLeft);

        // プレイヤーのローカル空間に基づいて groundCheckPos を計算
        Vector2 checkPos = (Vector2)transform.position + (Vector2)transform.TransformDirection(_fallingObjectCheckPos);

        // プレイヤーの回転角に基づいて矩形の角度を設定
        float rotationZ = transform.eulerAngles.z;

        // Gizmosの回転行列を設定して、矩形を描画
        Gizmos.color = Color.red;
        Gizmos.matrix = Matrix4x4.TRS(checkPos, Quaternion.Euler(0, 0, rotationZ), Vector3.one);
        Gizmos.DrawWireCube(Vector2.zero, _fallingObjectCheckSize);




    }

    // 入力のコールバック
    public void OnMove(InputAction.CallbackContext context)
    {
        if(!_isControl) return;
        _moveInput = context.ReadValue<Vector2>().x;

    }

    public void OnSelect(InputAction.CallbackContext context)
    {
        if (context.performed && Time.timeScale == 1)
        {
            _gameManager.GamePose();
        }
        else if (context.performed && Time.timeScale == 0)
        {
            _gameManager.GameResume();
        }
    }
    public void OnStert(InputAction.CallbackContext context)
    {
        if (context.performed)
        {
            _gameManager.StartSkip();
        }
    }
    public void OnSouth(InputAction.CallbackContext context)
    {
        if (!_isControl) return;
        if (context.performed) // 押された瞬間だけジャンプする
        {
            if(_jump ==null)
            {
                return;
            }

            if (_jump.IsGrounded())
            {
                // しゃがみアニメーションを再生
                if(_animator.GetBool("OutOfRange") == false)
                {
                    _animator.SetTrigger("Crouch");
                    _animator.SetBool("Jump", true);
                }

                StartCoroutine(JumpSequence());
                _jumpingPointY = transform.position.y - 0.1f;
                _soundManager.PlayerSound(2); // インデックスの2番　ジャンプサウンド
            }


        }

    }


    public void SetControl(bool Enable)
    {
        _isControl = Enable;
    }
}
