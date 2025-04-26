using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stick : MonoBehaviour
{
    public SoundManager _soundManager { get; set; } // �T�E���h�R���|�[�l���g

    public int layerMask { get; set; }             // �̂肪�������郌�C���[

    public string BaseTag { get; set; }            // �y��̃^�O

    private LineRenderer lineRenderer;
    private BoxCollider2D boxCollider;
    private PolygonCollider2D polygonCollider;

    private float mass = 0;                         // ��̃u���b�N�̎��ʏ��

    private bool PlaySE = false;                    // SE�Đ��t���O

    // Start is called before the first frame update
    void Awake()
    {
        // �R���|�[�l���g�ǉ�
        lineRenderer = gameObject.AddComponent<LineRenderer>();

        // ���C���[�ݒ�
        lineRenderer.sortingOrder = 3;

        // �R���|�[�l���g�擾
        polygonCollider = GetComponent<PolygonCollider2D>();

        // LineRenderer���I�u�W�F�N�g�̈ʒu���]�ɒǏ]����悤�ɒ���
        lineRenderer.useWorldSpace = false;

        StickDraw();
    }

    // ���ł킩��₷�����邽�߂ɐ���`��
    public void StickDraw()
    {
        if (polygonCollider)
        {
            PolygonDraw();
        }
    }

    private void BoxDraw()
    {
        // BoxCollider2D�̒��_���ɍ��킹��LineRenderer�̒��_����ݒ�
        lineRenderer.positionCount = 5;  // 4�̒��_�{1�ڂ̒��_�ɖ߂邽�߂�5�K�v

        // ���̐F�Ƒ�����ݒ�
        lineRenderer.startColor = Color.red;
        lineRenderer.endColor = Color.red;
        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;

        // BoxCollider2D�̃T�C�Y����ɒ��_���v�Z�i���[�J�����W�j
        Vector2 size = boxCollider.size;   // BoxCollider2D�̃T�C�Y�i���[�J�����W�n�j
        Vector2 offset = boxCollider.offset; // BoxCollider2D�̃I�t�Z�b�g�i���[�J�����W�n�j

        Vector3 topLeft = new Vector3(-size.x / 2 + offset.x, size.y / 2 + offset.y, 0);
        Vector3 topRight = new Vector3(size.x / 2 + offset.x, size.y / 2 + offset.y, 0);
        Vector3 bottomRight = new Vector3(size.x / 2 + offset.x, -size.y / 2 + offset.y, 0);
        Vector3 bottomLeft = new Vector3(-size.x / 2 + offset.x, -size.y / 2 + offset.y, 0);

        // ���_��LineRenderer�ɐݒ�
        lineRenderer.SetPosition(0, topLeft);
        lineRenderer.SetPosition(1, topRight);
        lineRenderer.SetPosition(2, bottomRight);
        lineRenderer.SetPosition(3, bottomLeft);
        lineRenderer.SetPosition(4, topLeft);  // �Ō�ɍŏ��̒��_�ɖ߂�
    }

    private void PolygonDraw()
    {
        // PolygonCollider2D�̒��_���ɍ��킹��LineRenderer�̒��_����ݒ�
        lineRenderer.positionCount = polygonCollider.points.Length + 1;  // �����`�ɂ��邽�߂�+1

        // �F�𔽉f�����邽�߂Ƀ}�e���A���ݒ�
        lineRenderer.material = new Material(Shader.Find("Sprites/Default"));

        // ���̐F�Ƒ�����ݒ�
        Gradient gradient = new Gradient();
        gradient.SetKeys(
            new GradientColorKey[] {
                new GradientColorKey(Color.yellow, 0.0f),      // �n�_: ���F

                new GradientColorKey(new Color(1.0f, 0.5f, 0.0f), 0.5f),      // �^��: �ԂƃI�����W�̒��ԐF

                new GradientColorKey(Color.yellow, 1.0f),      // �I�_: ���F
            },
            new GradientAlphaKey[]{
                new GradientAlphaKey(1.0f, 0.0f),   // �n�_�̓����x: �s����
                new GradientAlphaKey(1.0f, 1.0f)    // �I�_�̓����x: �s����
            }
        );

        lineRenderer.colorGradient = gradient;

        lineRenderer.startWidth = 0.1f;
        lineRenderer.endWidth = 0.1f;

        // PolygonCollider2D�̊e���_��LineRenderer�ɐݒ�i���[�J�����W�j
        for (int i = 0; i < polygonCollider.points.Length; i++)
        {
            Vector3 localPosition = new Vector3(polygonCollider.points[i].x,
                polygonCollider.points[i].y, -0.1f);  // ���[�J�����W�̒��_���擾
            lineRenderer.SetPosition(i, localPosition);
        }

        // �Ō�̒��_�ɍŏ��̒��_��ݒ肵�ĕ���
        lineRenderer.SetPosition(polygonCollider.points.Length,
            new Vector3(polygonCollider.points[0].x,
            polygonCollider.points[0].y,
            -0.1f));
    }

    // �G�ꂽ�u���b�N������������
    private void OnCollisionEnter2D(Collision2D collision)
    {
        // �ǂ����������e�Ȃ珈�������Ȃ�
        // �v���C���[�Ȃ珈�������Ȃ�
        // ����̃��C���[�Ȃ珈�������Ȃ�
        if ((transform.parent && collision.collider.transform.parent &&
            collision.collider.transform.parent == transform.parent) ||
            collision.collider.tag == "Player" || collision.collider.tag == "Eraser" ||
            collision.gameObject.layer == 11)
        {
            return;
        }

        if (mass == 0)
        {
            // ���擾
            mass = GetComponent<Rigidbody2D>().mass;
        }
        // �y��ȊO�̃u���b�N�ɏՓ˂����玩�����g�̏���n��
        if (layerMask == collision.gameObject.layer)
        {
            // �������g�̏����󂯓n��
            PassSelfInfo(collision.collider.gameObject);
        }

        // ���C���[���w�肳�ꂽ���̂ŁA�e���Ȃ��u���b�N��������
        if(layerMask == collision.gameObject.layer &&
            !collision.collider.transform.parent)
        {
            // �y��ɂ�����
            if (collision.gameObject.tag == BaseTag)
            {
                BaseAttach(collision.gameObject);
            }
            // �Փ˂����u���b�N�������ɂ�����
            else
            {
                AttachSelf(collision.gameObject);
            }
        }
        // �ڐG�����u���b�N�����݂��ɐe�������Ă��āA�����e����Ȃ������ꍇ
        // �ЂƂ̃O���[�v�ɂ���
        // �y�䂪�q�ɂȂ��Ă�e�ɍ��킹��
        else if(transform.parent && collision.collider.transform.parent.childCount > 0 &&
            transform.parent.childCount > 0)
        {
            MergeParent(collision.collider.gameObject);              // �ЂƂ̐e�I�u�W�F�N�g�ɓ���
        }
        // ���łɐe�q�֌W������u���b�N�ɂ̂�u���b�N���G�ꂽ�ꍇ
        else if(collision.collider.transform.parent.childCount > 0)
        {
            StickTo(collision.collider.gameObject);                  // ����ɂ�����
        }

        // �Đ����ĂȂ������炷��
        if (!PlaySE)
        {
            _soundManager.PlayerSound(2);   // SE�Đ�
            PlaySE = true;                          // �t���O�グ
        }
    }

    // �������g�̏����󂯓n��
    private void PassSelfInfo(GameObject block)
    {
        ResetBlock resetBlock = block.GetComponent<ResetBlock>();

        // ���ɏ����擾���Ă��珈�������Ȃ�
        if (resetBlock && resetBlock.stick) return;

        // �y��Ȃ��p�̃t���O���グ��
        if(block.tag == BaseTag)
        {
            resetBlock.Base = true;
        }
        resetBlock.StickBlock = gameObject;                 // ����n��
        resetBlock.stick = true;                            // ���������t���O���グ��
        resetBlock.mass = mass;                             // ���ʏ����擾
    }


    // �y��ɂ�����
    private void BaseAttach(GameObject block)
    {
        //if (block.transform.parent) return;

        // �e���p�ӂ���ĂȂ�������
        if (!block.transform.parent)
        {
            var obj = new GameObject();                             // �e����
            obj.AddComponent<Rigidbody2D>();                        // Rigidbody2D�ǉ�
            obj.AddComponent<UpdateMass>();                         // �X�N���v�g�ǉ�
            obj.tag = block.tag;                                    // �^�O�ݒ�
            obj.layer = block.layer;                                // ���C���[�ݒ�

            Rigidbody2D rb = obj.GetComponent<Rigidbody2D>();
            rb.mass = mass;                                         // ���ʐݒ�
            rb.gravityScale = 0;                                    // �d��OFF
            rb.isKinematic = true;                                  // �������ZOFF

            block.transform.parent = obj.transform;                       // �e�ݒ�
            Destroy(block.transform.GetComponent<Rigidbody2D>());         // ���g��Rigidbody2D�폜
        }

        // �����ɐe�������ꍇ�q��S�Ĉڂ��Đe���폜
        if (transform.parent)
        {
            Transform oldparent = transform.parent;
            while (oldparent.childCount > 0)
            {
                int i = 0;
                oldparent.GetChild(i).parent = block.transform.parent;
            }

            Destroy(oldparent.gameObject);
        }
        // �e�����Ȃ�������e��ݒ肵�ă��W�b�h�{�f�B�̍폜
        else
        {
            transform.parent = block.transform.parent;                         // �e�ݒ�
            Destroy(transform.GetComponent<Rigidbody2D>());             // ���g��Rigidbody2D�폜
        }
    }

    // �������g�ɂ�����
    private void AttachSelf(GameObject block)
    {
        // �e���p�ӂ���ĂȂ�������
        if(!transform.parent)
        {
            var obj = new GameObject();                             // �e����
            obj.AddComponent<Rigidbody2D>();                        // Rigidbody2D�ǉ�
            obj.AddComponent<UpdateMass>();                         // �X�N���v�g�ǉ�
            obj.layer = gameObject.layer;                           // ���C���[�ݒ�

            Rigidbody2D rb = obj.GetComponent<Rigidbody2D>();
            rb.mass = mass;                                         // ���ʂ���

            transform.parent = obj.transform;                       // �e�ݒ�
            Destroy(transform.GetComponent<Rigidbody2D>());         // ���g��Rigidbody2D�폜
        }

        block.transform.parent = transform.parent;                  // �̂肪���ĂȂ��u���b�N�̐e�ݒ�
        Destroy(block.GetComponent<Rigidbody2D>());                 // Rigidbody2D�폜
    }

    // �ЂƂ̐e�I�u�W�F�N�g�ɂ܂Ƃ߂�
    private void MergeParent(GameObject block)
    {
        Transform oldparent;
        //List<Transform> childTransform = new List<Transform>();

        // �Ԃ������u���b�N�̐e�I�u�W�F�N�g���y��̐e�������ꍇ
        if (block.transform.parent.tag == BaseTag)
        {
            // �����擾���Ă���
            oldparent = transform.parent;

            //// �J�E���g������邩���ɏ��擾����
            //for (int i = 0; i < transform.parent.childCount; i++)
            //{
            //    childTransform.Add(transform.parent.GetChild(i));
            //}

            //for (int i = 0; i < childTransform.Count; i++)
            //{
            //    childTransform[i].parent = block.transform;
            //}

            // �������g�̐e�q�O���[�v�̎q��S�ĂԂ������u���b�N�̐e�I�u�W�F�N�g�̎q�ɂ���
            while (oldparent.childCount > 0)
            {
                int i = 0;
                oldparent.GetChild(i).parent = block.transform.parent;
            }

            // �v��Ȃ��e�I�u�W�F�N�g�͔j�����܂��傤
            Destroy(oldparent.gameObject);                              // �e�I�u�W�F�N�g�폜�@���߂��
            return;
        }

        // ���y�䂪�����Ă�e�I�u�W�F�N�g�������͂ǂ������y�䂪�����ĂȂ��I�u�W�F�N�g�������ꍇ

        // �����擾���Ă���
        oldparent = block.transform.parent;

        //// �J�E���g������邩���ɏ��擾����
        //for (int i = 0; i < block.transform.childCount; i++)
        //{
        //    childTransform.Add(block.transform.GetChild(i));
        //}

        //// �Ԃ���������̃u���b�N�������̐e�I�u�W�F�N�g�ɂ����
        //for (int i = 0; i < childTransform.Count; i++)
        //{
        //    childTransform[i].parent = transform.parent;
        //}

        // �Ԃ������u���b�N�̐e�q�O���[�v�̎q��S�Ď������g�̐e�I�u�W�F�N�g�̎q�ɂ���
        while (oldparent.childCount > 0)
        {
            int i = 0;
            oldparent.GetChild(i).parent = transform.parent;
        }

        // �v��Ȃ��e�I�u�W�F�N�g�͔j�����܂��傤
        Destroy(oldparent.gameObject);                              // �e�I�u�W�F�N�g�폜�@���߂��
    }

    // ����ɂ�����
    private void StickTo(GameObject block)
    {
        transform.parent = block.transform.parent;              // �e��ݒ�
        Destroy(transform.GetComponent<Rigidbody2D>());             // ���g��Rigidbody2D�폜
    }
}
