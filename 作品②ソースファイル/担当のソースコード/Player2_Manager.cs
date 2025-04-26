using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class Player2_Manager : MonoBehaviour
{
    // 移動コンポーネント
    Move _move;

    // ブロック落下コンポーネント
    SetupFall _setupfall;

    // 回転コンポーネント
    RotateBlock _rotateBlock;

    // ホールドコンポーネント
    Hold _hold;

    // アイテムコンポーネント
    ItemPouch _itemPouch;

    // ブロックをしまうコンポーネント
    StoreBlock _storeBlock;

    // ゴールコンポーネント
    Goal _goal;

    // アニメーターコンポーネント
    private Animator _animator;

    private SoundManager _soundManager;

    public bool Input_move { get; set; }

    //　移動パラメーター
    private float _moveInput;

    // Rボタン押下状態
    private bool isRightShoulderPressed = false;

    // Rボタン押下状態
    private bool isLeftShoulderPressed = false;

    private int normalLayerNum;         // 落下ブロックの通常レイヤー数値

    private float currentTime = 0.0f;   // 経過時間計算用

    private bool itemUseFlg = false;    // アイテム使用フラグ

    private bool kesiUseFlg = false;    // 消しゴムアイテム使用フラグ

    private bool holdUseFlg = false;    // ホールド使用フラグ

    private GameManager _gameManager;

    private bool _isControl = false;
    // Start is called before the first frame update
    void Start()
    {
        // コンポーネント実体取得
        _move = GetComponent<Move>();
        _setupfall = GetComponent<SetupFall>();
        _rotateBlock = GetComponent<RotateBlock>();
        _hold = GetComponent<Hold>();
        _itemPouch = GetComponent<ItemPouch>();
        _goal = GameObject.Find("Goal").GetComponent<Goal>();
        _storeBlock = GetComponent<StoreBlock>();
        _animator = GetComponent<Animator>();
        _soundManager = GetComponent<SoundManager>();

        _itemPouch._soundManager = _soundManager;

        _gameManager=GameObject.Find("GameManager").GetComponent<GameManager>();

        // ブロック生成
        _setupfall.CreateBlock();
        _rotateBlock.next = _setupfall.IsNext;
        normalLayerNum = _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder;

        _isControl = false;
    }


    // Update is called once per frame
    void Update()
    {
        // 移動入力がされてない
        Input_move = false;

        // Time.timeScaleが0の時は動作しないようにする
        if (_isControl == false) return;

        // 右
        if (Input.GetKey(KeyCode.RightArrow) || _moveInput > 0)
        {
            _animator.SetInteger("Move", 1);
            _move.RightMove();
            _setupfall.BlockMove(true);
            Input_move = true;
        }
        // 左
        else if (Input.GetKey(KeyCode.LeftArrow) || _moveInput < 0)
        {
            _move.LeftMove();
            _setupfall.BlockMove(false);
            _animator.SetInteger("Move", -1);
            Input_move = true;
        }
        else 
        {
            _animator.SetInteger("Move", 0);
            _setupfall.BlockMoveReset();
            _move.ResetValue();
        }


        if (_setupfall.IsNext)
        {
            _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder = normalLayerNum;
        }

        // すたっぴ～の持ち上げできる範囲に入ってたら処理をしない
        if (_goal.isInArea)
        {
            if (_animator.GetBool("LiftWait") == false)
            {
                _soundManager.PlayerSound(7);
            }


            _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder = -5;
            _animator.SetBool("LiftWait", true);

            return;
        }
        else
        {
            _animator.SetBool("LiftWait", false);
        }

        // ブロックが真下にあったらしまう
        if (_setupfall.IsNext && _storeBlock.block_InArea)
        {
            _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder = -5;

            // 落下できない
            if (Input.GetKeyDown(KeyCode.Return))
            {
                // SE再生
                _soundManager.PlayerSound(0);
            }

            return;
        }


        // 次のブロック用意
        if (!_setupfall.IsNext && currentTime >= _setupfall.IsInterval())
        {

            _animator.SetBool("Interval", false);
            _setupfall.CreateBlock();
            _rotateBlock.next = _setupfall.IsNext;
            normalLayerNum = _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder;
            currentTime = 0.0f;
        }
        else if(!_setupfall.IsNext)
        {
            _animator.SetBool("Interval", true);
            currentTime += Time.deltaTime;
            return;
        }


        // 右回転
        if ((Input.GetKey(KeyCode.P) || isRightShoulderPressed) &&
            !kesiUseFlg)
        {
            _rotateBlock.RightRotate();
        }
        // 左回転
        else if ((Input.GetKey(KeyCode.O) || isLeftShoulderPressed) &&
            !kesiUseFlg)
        {
            _rotateBlock.LeftRotate();
        }


        // ホールド
        if (Input.GetKeyDown(KeyCode.L) && !_hold.holdBlock &&
            !itemUseFlg && !holdUseFlg)
        {

            GameObject hold = _setupfall.IsNext;    // ネクストブロックをホールドする
            _hold.holdBlock = hold;                 // ホールドしてる情報として残す
            _hold.HoldBlock();                      // 回転リセット、レイヤーをいじる

            _hold.SetImage(_setupfall.IsNext.
              GetComponent<UISprite>().Issprite);// UI設定

            _setupfall.IsNext = null;               // ネクストブロック情報削除

            holdUseFlg = true;                      // フラグ上げ
        }
        // ブロック入れ替え
        else if (Input.GetKeyDown(KeyCode.L) && _hold.holdBlock &&
            !itemUseFlg && !holdUseFlg)
        {

            _hold.SetImage(_setupfall.IsNext.
              GetComponent<UISprite>().Issprite);// UI設定

            GameObject work = _setupfall.IsNext;    // ネクストブロック情報退避
            _setupfall.IsNext = _hold.holdBlock;    // ホールドしてたブロックをネクストブロックにする

            _rotateBlock.next = _setupfall.IsNext;  // 回転操作対象情報の更新
            _hold.ResetLayer();                     // レイヤー値を元に戻す

            _hold.holdBlock = work;                 // ホールドするブロックを更新
            _hold.HoldBlock();                      // 回転リセット、レイヤーをいじる

            holdUseFlg = true;                      // フラグ上げ
        }

        // アイテム使用
        if (Input.GetKeyDown(KeyCode.RightShift) && !itemUseFlg)
        {
            ItemUse();      // アイテム使用
        }
        //// 使用キャンセル
        //else if(Input.GetKeyDown(KeyCode.RightShift) && itemUseFlg)
        //{
        //    ItemCancel();   // 使用キャンセル
        //}

        // 落下
        if (Input.GetKeyDown(KeyCode.Return))
        {
            // 消しゴムを使ってたら
            if (kesiUseFlg)
            {
                // 180度回転させる
                Quaternion rot = Quaternion.Euler(0.0f, 0.0f, 180.0f);
                _setupfall.IsNext.transform.rotation = rot;
                kesiUseFlg = false;                         // フラグ下げ
            }

            _animator.SetTrigger("Drop");

            holdUseFlg = false;                            // ホールド使用フラグ下げ

            if (itemUseFlg)
            {
                _itemPouch.ItemDelete();                    // ポーチからアイテムを消す
                itemUseFlg = false;                         // フラグ下げ
            }
            else
            {
                // サウンドセット
                _setupfall.IsNext.AddComponent<NormalCollisionSound>().SetSE(_soundManager, 11);
            }

            _setupfall.Fall();                             // 落下処理
        }
    }
    // コールバックイベント
    public void OnMove(InputAction.CallbackContext context)
    {
        if (!_isControl) return;
        Input_move = true; 
        _moveInput = context.ReadValue<Vector2>().x;
    }

    public void OnRightShoulder(InputAction.CallbackContext context) // 右回転
    {
        if (!_isControl) return;

        // 持ち上げ準備に入ってたらブロックの処理をしない
        if (_goal.isInArea) return;

        // ボタンが押された瞬間と押している間の処理
        if (context.performed)
        {
            isRightShoulderPressed = true;
        }

        // ボタンが離された時の処理
        if (context.canceled)
        {
            isRightShoulderPressed = false;
        }

    }
    public void OnLeftShoulder(InputAction.CallbackContext context) // 左回転
    {
        if (!_isControl) return;

        // 持ち上げ準備に入ってたらブロックの処理をしない
        if (_goal.isInArea) return;

        // ボタンが押された瞬間と押している間の処理
        if (context.performed)
        {
            isLeftShoulderPressed = true;
        }

        // ボタンが離された時の処理
        if (context.canceled)
        {
            isLeftShoulderPressed = false;
        }
    }
    public void OnSouth(InputAction.CallbackContext context) // ブロックを落とす
    {
        if (!_isControl) return;

        // 持ち上げ準備に入ってたらブロックの処理をしない
        if (_goal.isInArea) return;

        if (_setupfall.IsNext && _storeBlock.block_InArea)
        {
            // 落下できない
            // SE再生
            _soundManager.PlayerSound(0);
            return;
        }

        // ボタンが押された瞬間と押している間の処理
        if (context.performed)
        {
            if (!_setupfall.IsNext)
            {
                currentTime += Time.deltaTime;
                return;
            }

            // 消しゴムを使ってたら
            if (kesiUseFlg)
            {
                // 180度回転させる
                Quaternion rot = Quaternion.Euler(0.0f, 0.0f, 180.0f);
                _setupfall.IsNext.transform.rotation = rot;
                kesiUseFlg = false;                         // フラグ下げ
            }

            _animator.SetTrigger("Drop");

            holdUseFlg = false;                             // ホールド使用フラグ下げ

            if (itemUseFlg)
            {
                _itemPouch.ItemDelete();                    // ポーチからアイテムを消す
                itemUseFlg = false;                         // フラグ下げ
            }
            else
            {
                // サウンドセット
                _setupfall.IsNext.AddComponent<NormalCollisionSound>().SetSE(_soundManager, 11);
            }

            _setupfall.Fall();
        }


    }
    public void OnEast(InputAction.CallbackContext context) // ブロックホールド
    {
        if (!_isControl) return;

        // 持ち上げ準備に入ってたらブロックの処理をしない
        if (_goal.isInArea) return;

        // ボタンが押された瞬間と押している間の処理
        if (context.performed)
        {
            if (!_setupfall.IsNext)
            {
                currentTime += Time.deltaTime;
                return;
            }
            if (!_hold.holdBlock && !itemUseFlg && !holdUseFlg)
            {
                GameObject hold = _setupfall.IsNext;    // ネクストブロックをホールドする
                _hold.holdBlock = hold;                 // ホールドしてる情報として残す
                _hold.HoldBlock();                      // 回転リセット、レイヤーをいじる

                _hold.SetImage(_setupfall.IsNext.
                  GetComponent<UISprite>().Issprite);// UI設定

                _setupfall.IsNext = null;               // ネクストブロック情報削除

                holdUseFlg = true;                      // フラグ上げ
            }
            // ブロック入れ替え
            else if (_hold.holdBlock && !itemUseFlg && !holdUseFlg)
            {
                _hold.SetImage(_setupfall.IsNext.
                  GetComponent<UISprite>().Issprite);// UI設定

                GameObject work = _setupfall.IsNext;    // ネクストブロック情報退避
                _setupfall.IsNext = _hold.holdBlock;    // ホールドしてたブロックをネクストブロックにする

                _rotateBlock.next = _setupfall.IsNext;  // 回転操作対象情報の更新
                _hold.ResetLayer();                     // レイヤー値を元に戻す

                _hold.holdBlock = work;                 // ホールドするブロックを更新
                _hold.HoldBlock();                      // 回転リセット、レイヤーをいじる

                holdUseFlg = true;                      // フラグ上げ
            }
        }


    }
    public void OnNorth(InputAction.CallbackContext context) // アイテム使用
    {
        if (!_isControl) return;

        // 持ち上げ準備に入ってたらブロックの処理をしない
        if (_goal.isInArea) return;

        if (context.performed)
        {
            // アイテム使用
            if (!itemUseFlg)
            {
                ItemUse();      // アイテム使用
            }
            //// 使用キャンセル
            //else if (itemUseFlg)
            //{
            //    ItemCancel();   // 使用キャンセル
            //}
        }


    }

    public void OnSelect(InputAction.CallbackContext context)
    {

        if (context.performed && Time.timeScale == 1) 
        {
            _gameManager.GamePose();
        }
        else if(context.performed && Time.timeScale == 0)
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

    // アイテム使用時のそれぞれの処理
    private void ItemUse()
    {
        // フラグでわける
        // のり
        if(_itemPouch.hasStick)
        {
            StickItem();                        // 専用の処理
            _gameManager.AddUseItem();
        }
        // 巨大化
        else if(_itemPouch.hasBig)
        {
            BigItem();                          // 専用の処理
            _gameManager.AddUseItem();
        }
        // 消しゴム
        else if(_itemPouch.hasEraser)
        {
            EraserItem();                       // 専用の処理
            _gameManager.AddUseItem();
        }
        // アイテムなし
        else
        {
            return;
        }

        itemUseFlg = true;                          // フラグ上げ
        _itemPouch.ItemLayer(true);                 // 表示順をいじる
    }


    private void StickItem()
    {
        // コンポーネントをセット
        // くっつけれる対象のタグをセット
        _setupfall.IsNext.AddComponent<Stick>().layerMask = _setupfall.IsNext.layer;
        Stick _stick = _setupfall.IsNext.GetComponent<Stick>();
        _stick.BaseTag = "Base";
        // サウンドコンポーネントセット
        _stick._soundManager = _soundManager;

        // 自分のタグをセット
        _setupfall.IsNext.tag = _itemPouch.sticktagName; // タグ付け

        _soundManager.PlayerSound(5);                               // SE再生
    }

    private void BigItem()
    {
        // 対象のタグ、コンポーネントをセット
        _setupfall.IsNext.AddComponent<Big>().BigScale(_setupfall.IsNext);  // 巨大化
        _setupfall.IsNext.tag = _itemPouch.bigtagName;                      // タグ付け

        // サウンドコンポーネントセット
        _setupfall.IsNext.GetComponent<Big>()._soundManager = _soundManager;

        _soundManager.PlayerSound(6);                               // SE再生
    }

    private void EraserItem()
    {
        // ブロックを消しゴムにする
        GameObject Eraser = Instantiate(_itemPouch.GetEraserObj(),
            _setupfall.IsNext.transform.position, Quaternion.identity);     // 消しゴム生成
        Destroy(_setupfall.IsNext);                                         // ブロック削除
        _setupfall.IsNext = Eraser;                                         // 次のブロックを消しゴムに変更

        // 消せれるタグのセット
        Eraser _eraser = Eraser.GetComponent<Eraser>();
        _eraser.tagName[0] = _itemPouch.blocktagName;
        _eraser.tagName[1] = _itemPouch.sticktagName;
        _eraser.tagName[2] = _itemPouch.bigtagName;
        // サウンドコンポーネントセット
        _eraser._soundManager = _soundManager;

        // 自分自身のタグをセット
        _setupfall.IsNext.tag = _itemPouch.erasertagName;                   // タグ付け

        kesiUseFlg = true;                                                  // フラグ上げ

        _soundManager.PlayerSound(7);                               // SE再生
    }

    //// アイテム使用キャンセル
    //private void ItemCancel()
    //{
    //    // フラグでわける
    //    // のり
    //    if (_itemPouch.hasStick)
    //    {
    //        StickItemCancel();                          // 専用のキャンセル処理
    //    }
    //    // 巨大化
    //    else if (_itemPouch.hasBig)
    //    {
    //        BigItemCancel();                            // 専用のキャンセル処理
    //    }
    //    // 消しゴム
    //    else if (_itemPouch.hasEraser)
    //    {
    //        EraserItemCancel();                         // 専用のキャンセル処理
    //    }
    //    // アイテムなし
    //    else
    //    {
    //        return;
    //    }

    //    _setupfall.IsNext.tag = _itemPouch.blocktagName; // タグを戻す
    //    itemUseFlg = false;                              // フラグ下げ
    //    _itemPouch.ItemLayer(false);                     // 表示順をいじる
    //}

    //// 元のブロックに戻す
    //private void StickItemCancel()
    //{
    //    // 追加したコンポーネントを削除
    //    Destroy(_setupfall.IsNext.GetComponent<LineRenderer>());
    //    Destroy(_setupfall.IsNext.GetComponent<Stick>());
    //}

    //// 元のブロックに戻す
    //private void BigItemCancel()
    //{
    //    // サイズを戻す
    //    _setupfall.IsNext.GetComponent<Big>().ResetScale(_setupfall.IsNext);
    //    // 追加したコンポーネントを削除
    //    Destroy(_setupfall.IsNext.GetComponent<Big>());
    //}

    //// 元のブロックに戻す
    //private void EraserItemCancel()
    //{
    //    // 追加したコンポーネントを削除
    //    Destroy(_setupfall.IsNext.GetComponent<Eraser>());
    //}

    public void SetControl(bool Enable)
    {
        _isControl = Enable;
    }
}
