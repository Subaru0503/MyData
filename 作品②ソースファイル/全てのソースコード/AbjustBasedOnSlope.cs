using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AbjustBasedOnSlope : MonoBehaviour
{
    private Rigidbody2D _rigidbody2D;
    [SerializeField] private PhysicsMaterial2D lowFrictionMaterial;  // 低摩擦用の物理マテリアル
    [SerializeField] private PhysicsMaterial2D highFrictionMaterial; // 高摩擦用の物理マテリアル
    [SerializeField] private float slopeThreshold = 30f; // 角度のしきい値（この角度以上で高摩擦に）


    [SerializeField] public LayerMask groundLayer;
    // Start is called before the first frame update
    void Start()
    {
        _rigidbody2D = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        // キャラクターの足元にレイを飛ばして地面を検出
        RaycastHit2D hit = Physics2D.Raycast(transform.position, Vector2.down, 1f, groundLayer);

        if (hit.collider != null)
        {
            // 地面の法線を取得
            Vector2 groundNormal = hit.normal;

            // 地面の角度を計算
            float slopeAngle = Vector2.Angle(groundNormal, Vector2.up);

            // 角度に応じて摩擦を設定
            if (slopeAngle > slopeThreshold)
            {
                // 高摩擦の物理マテリアルを設定
                _rigidbody2D.sharedMaterial = highFrictionMaterial;
            }
            else
            {
                // 低摩擦の物理マテリアルを設定
                _rigidbody2D.sharedMaterial = lowFrictionMaterial;
            }

            // 地面の法線に基づいて回転角度を計算
            float slopeRotationAngle = Mathf.Atan2(groundNormal.y, groundNormal.x) * Mathf.Rad2Deg - 90f;

            // 回転角度を -30度から +30度の範囲内に制限
            slopeRotationAngle = Mathf.Clamp(slopeRotationAngle, -30f, 30f);

            // 目標の回転角度を設定
            Quaternion targetRotation = Quaternion.Euler(0f, 0f, slopeRotationAngle);

            // 現在の回転と目標の回転の間を線形補完して滑らかに回転
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * 10f);  // 補完速度
        }
        else
        {
            // 空中にいる場合は摩擦をリセット
            _rigidbody2D.sharedMaterial = lowFrictionMaterial;

            // 地面に接地していない場合は回転をリセット
            Quaternion targetRotation = Quaternion.Euler(0f, 0f, 0f);
            transform.rotation = Quaternion.Lerp(transform.rotation, targetRotation, Time.deltaTime * 10f);  // 補完速度
        }
    }
    // レイキャストの可視化
    private void OnDrawGizmos()
    {
        // シーンビューでレイを赤色で描画
        Gizmos.color = Color.blue;

        // レイの起点
        Vector2 rayOrigin = transform.position;

        // レイの方向と距離を描画
        Gizmos.DrawLine(rayOrigin, rayOrigin + Vector2.down * 0.5f);
    }
}
