// インクルード部
#include "CollisionManager.h"

// コンポーネント
#include "BoxCollider.h"
#include "Scanner.h"
#include "ModelRenderer3D.h"

// 更新処理
void CollisionManager::Update()
{
	// コライダー付きのオブジェクトの当たり判定チェックループ
	for (auto itA = m_pObjList.begin(); itA != m_pObjList.end(); ++itA)
	{
		// 主体になるオブジェクト
		GameObject* objA = *itA;

		// BoxColliderコンポーネント
		BoxCollider* _objABoxCollider = objA->GetComponent<BoxCollider>();

		// スキャナコンポーネント
		Scanner* _objAScanner = objA->GetComponent<Scanner>();

		// タグ取得
		string tag = objA->GetTag();

		if (_objABoxCollider)
		{
			// フラグリセット
			_objABoxCollider->SetCollision(false);
		}

		// スキャナコンポーネントがあるか確認
		if (_objAScanner)
		{
			// フラグをリセット
			_objAScanner->SetCollision(false);
		}
		// 特定のタグ以外はここで終わり
		else if(tag != "Goal" && tag != "CheckPointPath")
		{
			continue;
		}

		for (auto itB = m_pObjList.begin(); itB != m_pObjList.end(); ++itB)
		{
			// ゲームオブジェクト型に変換
			GameObject* objB = *itB;

			// オブジェクトAの座標を取得
			float3 objAPos = float3::Tofloat3(objA->GetPos());

			// オブジェクトBの座標を取得
			float3 objBPos = float3::Tofloat3(objB->GetPos());

			// オブジェクトAとオブジェクトBの距離を計算
			float distance = float3::distance(objAPos, objBPos);

			// 3Dモデルレンダラーコンポーネント取得
			ModelRenderer3D* modelRenderer3D = objB->GetComponent<ModelRenderer3D>();

			// オブジェクトナンバーが被ったら(同じオブジェクト)処理しない
			// 当たり判定を取らないタグだったら処理しない
			// 一定以上距離が離れてたら処理しない
			// 描画してないオブジェクトは処理しない
			if (objA->Get3DObjNo() == objB->Get3DObjNo() ||
				_objABoxCollider->CheckTag(objB) ||
				distance > 15.0f ||
				(modelRenderer3D && !modelRenderer3D->GetDrawFlg()))
			{
				continue;
			}

			// 周りにオブジェクトがあるかスキャン
			if (_objAScanner &&
				_objAScanner->CheckObb(objA, objB))
			{
				// スキャン判定呼び出し
				objA->OnScanner(objB);

				// 検知したフラグを上げる
				_objAScanner->SetCollision(true);
			}

			// obb当たり判定チェック
			if (modelRenderer3D && !_objABoxCollider->GetIsTrigger() &&
				_objABoxCollider->CheckObb(objA, objB))
			{
				// コリジョン判定呼び出し
				objA->OnCollision(objB);

				// 当たったフラグを上げる
				_objABoxCollider->SetCollision(true);

				// 座標を補正
				_objABoxCollider->FixPos(objB);
			}
		}

		// 検知しなかった
		if (_objAScanner && !_objAScanner->GetCollision())
		{
			objA->OnScanner(nullptr);	// 当たってない情報を渡す
		}
		// 何にも当たらなかった
		if (!_objABoxCollider->GetCollision())
		{
			objA->OnCollision(nullptr);
		}
	}
}
