using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class Player2_Manager : MonoBehaviour
{
    // �ړ��R���|�[�l���g
    Move _move;

    // �u���b�N�����R���|�[�l���g
    SetupFall _setupfall;

    // ��]�R���|�[�l���g
    RotateBlock _rotateBlock;

    // �z�[���h�R���|�[�l���g
    Hold _hold;

    // �A�C�e���R���|�[�l���g
    ItemPouch _itemPouch;

    // �u���b�N�����܂��R���|�[�l���g
    StoreBlock _storeBlock;

    // �S�[���R���|�[�l���g
    Goal _goal;

    // �A�j���[�^�[�R���|�[�l���g
    private Animator _animator;

    private SoundManager _soundManager;

    public bool Input_move { get; set; }

    //�@�ړ��p�����[�^�[
    private float _moveInput;

    // R�{�^���������
    private bool isRightShoulderPressed = false;

    // R�{�^���������
    private bool isLeftShoulderPressed = false;

    private int normalLayerNum;         // �����u���b�N�̒ʏ탌�C���[���l

    private float currentTime = 0.0f;   // �o�ߎ��Ԍv�Z�p

    private bool itemUseFlg = false;    // �A�C�e���g�p�t���O

    private bool kesiUseFlg = false;    // �����S���A�C�e���g�p�t���O

    private bool holdUseFlg = false;    // �z�[���h�g�p�t���O

    private GameManager _gameManager;

    private bool _isControl = false;
    // Start is called before the first frame update
    void Start()
    {
        // �R���|�[�l���g���̎擾
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

        // �u���b�N����
        _setupfall.CreateBlock();
        _rotateBlock.next = _setupfall.IsNext;
        normalLayerNum = _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder;

        _isControl = false;
    }


    // Update is called once per frame
    void Update()
    {
        // �ړ����͂�����ĂȂ�
        Input_move = false;

        // Time.timeScale��0�̎��͓��삵�Ȃ��悤�ɂ���
        if (_isControl == false) return;

        // �E
        if (Input.GetKey(KeyCode.RightArrow) || _moveInput > 0)
        {
            _animator.SetInteger("Move", 1);
            _move.RightMove();
            _setupfall.BlockMove(true);
            Input_move = true;
        }
        // ��
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

        // �������ҁ`�̎����グ�ł���͈͂ɓ����Ă��珈�������Ȃ�
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

        // �u���b�N���^���ɂ������炵�܂�
        if (_setupfall.IsNext && _storeBlock.block_InArea)
        {
            _setupfall.IsNext.GetComponent<SpriteRenderer>().sortingOrder = -5;

            // �����ł��Ȃ�
            if (Input.GetKeyDown(KeyCode.Return))
            {
                // SE�Đ�
                _soundManager.PlayerSound(0);
            }

            return;
        }


        // ���̃u���b�N�p��
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


        // �E��]
        if ((Input.GetKey(KeyCode.P) || isRightShoulderPressed) &&
            !kesiUseFlg)
        {
            _rotateBlock.RightRotate();
        }
        // ����]
        else if ((Input.GetKey(KeyCode.O) || isLeftShoulderPressed) &&
            !kesiUseFlg)
        {
            _rotateBlock.LeftRotate();
        }


        // �z�[���h
        if (Input.GetKeyDown(KeyCode.L) && !_hold.holdBlock &&
            !itemUseFlg && !holdUseFlg)
        {

            GameObject hold = _setupfall.IsNext;    // �l�N�X�g�u���b�N���z�[���h����
            _hold.holdBlock = hold;                 // �z�[���h���Ă���Ƃ��Ďc��
            _hold.HoldBlock();                      // ��]���Z�b�g�A���C���[��������

            _hold.SetImage(_setupfall.IsNext.
              GetComponent<UISprite>().Issprite);// UI�ݒ�

            _setupfall.IsNext = null;               // �l�N�X�g�u���b�N���폜

            holdUseFlg = true;                      // �t���O�グ
        }
        // �u���b�N����ւ�
        else if (Input.GetKeyDown(KeyCode.L) && _hold.holdBlock &&
            !itemUseFlg && !holdUseFlg)
        {

            _hold.SetImage(_setupfall.IsNext.
              GetComponent<UISprite>().Issprite);// UI�ݒ�

            GameObject work = _setupfall.IsNext;    // �l�N�X�g�u���b�N���ޔ�
            _setupfall.IsNext = _hold.holdBlock;    // �z�[���h���Ă��u���b�N���l�N�X�g�u���b�N�ɂ���

            _rotateBlock.next = _setupfall.IsNext;  // ��]����Ώۏ��̍X�V
            _hold.ResetLayer();                     // ���C���[�l�����ɖ߂�

            _hold.holdBlock = work;                 // �z�[���h����u���b�N���X�V
            _hold.HoldBlock();                      // ��]���Z�b�g�A���C���[��������

            holdUseFlg = true;                      // �t���O�グ
        }

        // �A�C�e���g�p
        if (Input.GetKeyDown(KeyCode.RightShift) && !itemUseFlg)
        {
            ItemUse();      // �A�C�e���g�p
        }
        //// �g�p�L�����Z��
        //else if(Input.GetKeyDown(KeyCode.RightShift) && itemUseFlg)
        //{
        //    ItemCancel();   // �g�p�L�����Z��
        //}

        // ����
        if (Input.GetKeyDown(KeyCode.Return))
        {
            // �����S�����g���Ă���
            if (kesiUseFlg)
            {
                // 180�x��]������
                Quaternion rot = Quaternion.Euler(0.0f, 0.0f, 180.0f);
                _setupfall.IsNext.transform.rotation = rot;
                kesiUseFlg = false;                         // �t���O����
            }

            _animator.SetTrigger("Drop");

            holdUseFlg = false;                            // �z�[���h�g�p�t���O����

            if (itemUseFlg)
            {
                _itemPouch.ItemDelete();                    // �|�[�`����A�C�e��������
                itemUseFlg = false;                         // �t���O����
            }
            else
            {
                // �T�E���h�Z�b�g
                _setupfall.IsNext.AddComponent<NormalCollisionSound>().SetSE(_soundManager, 11);
            }

            _setupfall.Fall();                             // ��������
        }
    }
    // �R�[���o�b�N�C�x���g
    public void OnMove(InputAction.CallbackContext context)
    {
        if (!_isControl) return;
        Input_move = true; 
        _moveInput = context.ReadValue<Vector2>().x;
    }

    public void OnRightShoulder(InputAction.CallbackContext context) // �E��]
    {
        if (!_isControl) return;

        // �����グ�����ɓ����Ă���u���b�N�̏��������Ȃ�
        if (_goal.isInArea) return;

        // �{�^���������ꂽ�u�ԂƉ����Ă���Ԃ̏���
        if (context.performed)
        {
            isRightShoulderPressed = true;
        }

        // �{�^���������ꂽ���̏���
        if (context.canceled)
        {
            isRightShoulderPressed = false;
        }

    }
    public void OnLeftShoulder(InputAction.CallbackContext context) // ����]
    {
        if (!_isControl) return;

        // �����グ�����ɓ����Ă���u���b�N�̏��������Ȃ�
        if (_goal.isInArea) return;

        // �{�^���������ꂽ�u�ԂƉ����Ă���Ԃ̏���
        if (context.performed)
        {
            isLeftShoulderPressed = true;
        }

        // �{�^���������ꂽ���̏���
        if (context.canceled)
        {
            isLeftShoulderPressed = false;
        }
    }
    public void OnSouth(InputAction.CallbackContext context) // �u���b�N�𗎂Ƃ�
    {
        if (!_isControl) return;

        // �����グ�����ɓ����Ă���u���b�N�̏��������Ȃ�
        if (_goal.isInArea) return;

        if (_setupfall.IsNext && _storeBlock.block_InArea)
        {
            // �����ł��Ȃ�
            // SE�Đ�
            _soundManager.PlayerSound(0);
            return;
        }

        // �{�^���������ꂽ�u�ԂƉ����Ă���Ԃ̏���
        if (context.performed)
        {
            if (!_setupfall.IsNext)
            {
                currentTime += Time.deltaTime;
                return;
            }

            // �����S�����g���Ă���
            if (kesiUseFlg)
            {
                // 180�x��]������
                Quaternion rot = Quaternion.Euler(0.0f, 0.0f, 180.0f);
                _setupfall.IsNext.transform.rotation = rot;
                kesiUseFlg = false;                         // �t���O����
            }

            _animator.SetTrigger("Drop");

            holdUseFlg = false;                             // �z�[���h�g�p�t���O����

            if (itemUseFlg)
            {
                _itemPouch.ItemDelete();                    // �|�[�`����A�C�e��������
                itemUseFlg = false;                         // �t���O����
            }
            else
            {
                // �T�E���h�Z�b�g
                _setupfall.IsNext.AddComponent<NormalCollisionSound>().SetSE(_soundManager, 11);
            }

            _setupfall.Fall();
        }


    }
    public void OnEast(InputAction.CallbackContext context) // �u���b�N�z�[���h
    {
        if (!_isControl) return;

        // �����グ�����ɓ����Ă���u���b�N�̏��������Ȃ�
        if (_goal.isInArea) return;

        // �{�^���������ꂽ�u�ԂƉ����Ă���Ԃ̏���
        if (context.performed)
        {
            if (!_setupfall.IsNext)
            {
                currentTime += Time.deltaTime;
                return;
            }
            if (!_hold.holdBlock && !itemUseFlg && !holdUseFlg)
            {
                GameObject hold = _setupfall.IsNext;    // �l�N�X�g�u���b�N���z�[���h����
                _hold.holdBlock = hold;                 // �z�[���h���Ă���Ƃ��Ďc��
                _hold.HoldBlock();                      // ��]���Z�b�g�A���C���[��������

                _hold.SetImage(_setupfall.IsNext.
                  GetComponent<UISprite>().Issprite);// UI�ݒ�

                _setupfall.IsNext = null;               // �l�N�X�g�u���b�N���폜

                holdUseFlg = true;                      // �t���O�グ
            }
            // �u���b�N����ւ�
            else if (_hold.holdBlock && !itemUseFlg && !holdUseFlg)
            {
                _hold.SetImage(_setupfall.IsNext.
                  GetComponent<UISprite>().Issprite);// UI�ݒ�

                GameObject work = _setupfall.IsNext;    // �l�N�X�g�u���b�N���ޔ�
                _setupfall.IsNext = _hold.holdBlock;    // �z�[���h���Ă��u���b�N���l�N�X�g�u���b�N�ɂ���

                _rotateBlock.next = _setupfall.IsNext;  // ��]����Ώۏ��̍X�V
                _hold.ResetLayer();                     // ���C���[�l�����ɖ߂�

                _hold.holdBlock = work;                 // �z�[���h����u���b�N���X�V
                _hold.HoldBlock();                      // ��]���Z�b�g�A���C���[��������

                holdUseFlg = true;                      // �t���O�グ
            }
        }


    }
    public void OnNorth(InputAction.CallbackContext context) // �A�C�e���g�p
    {
        if (!_isControl) return;

        // �����グ�����ɓ����Ă���u���b�N�̏��������Ȃ�
        if (_goal.isInArea) return;

        if (context.performed)
        {
            // �A�C�e���g�p
            if (!itemUseFlg)
            {
                ItemUse();      // �A�C�e���g�p
            }
            //// �g�p�L�����Z��
            //else if (itemUseFlg)
            //{
            //    ItemCancel();   // �g�p�L�����Z��
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

    // �A�C�e���g�p���̂��ꂼ��̏���
    private void ItemUse()
    {
        // �t���O�ł킯��
        // �̂�
        if(_itemPouch.hasStick)
        {
            StickItem();                        // ��p�̏���
            _gameManager.AddUseItem();
        }
        // ���剻
        else if(_itemPouch.hasBig)
        {
            BigItem();                          // ��p�̏���
            _gameManager.AddUseItem();
        }
        // �����S��
        else if(_itemPouch.hasEraser)
        {
            EraserItem();                       // ��p�̏���
            _gameManager.AddUseItem();
        }
        // �A�C�e���Ȃ�
        else
        {
            return;
        }

        itemUseFlg = true;                          // �t���O�グ
        _itemPouch.ItemLayer(true);                 // �\������������
    }


    private void StickItem()
    {
        // �R���|�[�l���g���Z�b�g
        // ���������Ώۂ̃^�O���Z�b�g
        _setupfall.IsNext.AddComponent<Stick>().layerMask = _setupfall.IsNext.layer;
        Stick _stick = _setupfall.IsNext.GetComponent<Stick>();
        _stick.BaseTag = "Base";
        // �T�E���h�R���|�[�l���g�Z�b�g
        _stick._soundManager = _soundManager;

        // �����̃^�O���Z�b�g
        _setupfall.IsNext.tag = _itemPouch.sticktagName; // �^�O�t��

        _soundManager.PlayerSound(5);                               // SE�Đ�
    }

    private void BigItem()
    {
        // �Ώۂ̃^�O�A�R���|�[�l���g���Z�b�g
        _setupfall.IsNext.AddComponent<Big>().BigScale(_setupfall.IsNext);  // ���剻
        _setupfall.IsNext.tag = _itemPouch.bigtagName;                      // �^�O�t��

        // �T�E���h�R���|�[�l���g�Z�b�g
        _setupfall.IsNext.GetComponent<Big>()._soundManager = _soundManager;

        _soundManager.PlayerSound(6);                               // SE�Đ�
    }

    private void EraserItem()
    {
        // �u���b�N�������S���ɂ���
        GameObject Eraser = Instantiate(_itemPouch.GetEraserObj(),
            _setupfall.IsNext.transform.position, Quaternion.identity);     // �����S������
        Destroy(_setupfall.IsNext);                                         // �u���b�N�폜
        _setupfall.IsNext = Eraser;                                         // ���̃u���b�N�������S���ɕύX

        // �������^�O�̃Z�b�g
        Eraser _eraser = Eraser.GetComponent<Eraser>();
        _eraser.tagName[0] = _itemPouch.blocktagName;
        _eraser.tagName[1] = _itemPouch.sticktagName;
        _eraser.tagName[2] = _itemPouch.bigtagName;
        // �T�E���h�R���|�[�l���g�Z�b�g
        _eraser._soundManager = _soundManager;

        // �������g�̃^�O���Z�b�g
        _setupfall.IsNext.tag = _itemPouch.erasertagName;                   // �^�O�t��

        kesiUseFlg = true;                                                  // �t���O�グ

        _soundManager.PlayerSound(7);                               // SE�Đ�
    }

    //// �A�C�e���g�p�L�����Z��
    //private void ItemCancel()
    //{
    //    // �t���O�ł킯��
    //    // �̂�
    //    if (_itemPouch.hasStick)
    //    {
    //        StickItemCancel();                          // ��p�̃L�����Z������
    //    }
    //    // ���剻
    //    else if (_itemPouch.hasBig)
    //    {
    //        BigItemCancel();                            // ��p�̃L�����Z������
    //    }
    //    // �����S��
    //    else if (_itemPouch.hasEraser)
    //    {
    //        EraserItemCancel();                         // ��p�̃L�����Z������
    //    }
    //    // �A�C�e���Ȃ�
    //    else
    //    {
    //        return;
    //    }

    //    _setupfall.IsNext.tag = _itemPouch.blocktagName; // �^�O��߂�
    //    itemUseFlg = false;                              // �t���O����
    //    _itemPouch.ItemLayer(false);                     // �\������������
    //}

    //// ���̃u���b�N�ɖ߂�
    //private void StickItemCancel()
    //{
    //    // �ǉ������R���|�[�l���g���폜
    //    Destroy(_setupfall.IsNext.GetComponent<LineRenderer>());
    //    Destroy(_setupfall.IsNext.GetComponent<Stick>());
    //}

    //// ���̃u���b�N�ɖ߂�
    //private void BigItemCancel()
    //{
    //    // �T�C�Y��߂�
    //    _setupfall.IsNext.GetComponent<Big>().ResetScale(_setupfall.IsNext);
    //    // �ǉ������R���|�[�l���g���폜
    //    Destroy(_setupfall.IsNext.GetComponent<Big>());
    //}

    //// ���̃u���b�N�ɖ߂�
    //private void EraserItemCancel()
    //{
    //    // �ǉ������R���|�[�l���g���폜
    //    Destroy(_setupfall.IsNext.GetComponent<Eraser>());
    //}

    public void SetControl(bool Enable)
    {
        _isControl = Enable;
    }
}
