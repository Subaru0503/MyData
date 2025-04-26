#include "GameObject.hpp"
#include "Component.h"
#include <typeinfo>
#include <algorithm>

/*
* @brief コンストラクタ
* @param[in] name オブジェクト名
*/
GameObject::GameObject(std::string name)
	: m_name(name)
	, m_pos{}, m_quat{0.0f, 0.0f, 0.0f, 1.0f}, m_scale{1.0f, 1.0f, 1.0f}
	, m_2DObjNo(0)
	, m_3DObjNo(0)
	//, m_DirectRad(0.0f)
	, m_OnMoveFloor(false)
{
	// オブジェクト名に応じて、保存ファイルの読み込み
	std::string path = "Assets/GameObject/" + m_name + ".dat";
	FILE* fp;
	fopen_s(&fp, path.c_str(), "rb");
	if (fp) {
		// ファイル一括読み込み
		fseek(fp, 0, SEEK_END);
		long fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* ptr = new char[fileSize];
		fread(ptr, fileSize, 1, fp);
		m_datas.push_back({"data", ptr}); // 一括で読み込んだデータを保存
		fclose(fp);

		// ゲームオブジェクト内のデータの読み込み
		memcpy(&m_pos, ptr, sizeof(m_pos));
		memcpy(&m_quat, ptr += sizeof(m_pos), sizeof(m_quat));
		memcpy(&m_scale, ptr += sizeof(m_quat), sizeof(m_scale));
		ptr += sizeof(m_scale);
		// データのキーと値が保存されている個所へのポインタを取得
		while (ptr - m_datas[0].value < fileSize)
		{
			char* data[2]; // キー,値
			size_t size;
			for (int i = 0; i < 2; ++i)
			{
				// データサイズ
				size = *reinterpret_cast<size_t*>(ptr);
				ptr += sizeof(size);
				// データ
				data[i] = ptr;
				ptr += size;
			}
			m_datas.push_back({ data[0], data[1] });
		}
	}
}

/*
* @brief デストラクタ
*/
GameObject::~GameObject()
{
	// 保存データの削除
	if(!m_datas.empty())
		delete[] m_datas[0].value;

	auto it = m_components.begin();

#ifdef _DEBUG
	// データの保存
	std::string path = "Assets/GameObject/" + m_name + ".dat";
	FILE* fp;
	fopen_s(&fp, path.c_str(), "wb");
	if (fp)
	{
		// ゲームオブジェクトのデータを保存
		fwrite(&m_pos, sizeof(m_pos), 1, fp);
		fwrite(&m_quat, sizeof(m_quat), 1, fp);
		fwrite(&m_scale, sizeof(m_scale), 1, fp);

		// コンポーネントのデータを保存
		it = m_components.begin();
		while (it != m_components.end())
		{
			const char* name = typeid(**it).name();
			Component::DataAccessor accessor(nullptr);
			(*it)->ReadWrite(&accessor);
			// データのキーを保存
			size_t size = strlen(name);
			fwrite(&size, sizeof(size), 1, fp);
			fwrite(name, size, 1, fp);
			// データの保存
			size = accessor.GetWriteSize();
			fwrite(&size, sizeof(size), 1, fp);
			fwrite(accessor.GetData(), size, 1, fp);
			++it;
		}
		fclose(fp);
	}
#endif

	// コンポーネントの削除
	it = m_components.begin();
	while (it != m_components.end())
	{
		delete (*it);
		++it;
	}
}

/*
* @brief 更新処理
*/
void GameObject::Execute()
{
	// 座標退避
	m_oldpos = m_pos;

	// コンポーネントの処理
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		(*it)->Execute();
		++it;
	}
	// 継承先オブジェクトの処理
	Update();
}

/*
* 初期状態に戻す
* オブジェクトをシーンが始まったときの状態に戻す
*/
void GameObject::ResetState()
{

}

/*
* @brief 衝突したオブジェクト
*/
void GameObject::OnCollision(GameObject* obj)
{

}
/*
* @brief 検知したオブジェクト
*/
void GameObject::OnScanner(GameObject* obj)
{
}

#ifdef _DEBUG
/*
* @brief インスペクターへの表示
* 選択された内容を表示
*/
void GameObject::Debug(debug::Window* window)
{
	// トランスフォームグループの作成
	debug::Item* group = debug::Item::CreateGroup("Transform");
	group->AddGroupItem(debug::Item::CreateBind("Pos",		debug::Item::Vector, &m_pos));
	group->AddGroupItem(debug::Item::CreateCallBack("Rotation", debug::Item::Vector,
		[this](bool isWrite, void* arg) {
			DirectX::XMFLOAT3* pVec = static_cast<DirectX::XMFLOAT3*>(arg);
			if (isWrite) {
				DirectX::XMStoreFloat4(&m_quat,
					DirectX::XMQuaternionRotationRollPitchYaw( // zxy
						DirectX::XMConvertToRadians(pVec->x), // pitch
						DirectX::XMConvertToRadians(pVec->y), // yaw
						DirectX::XMConvertToRadians(pVec->z)) // roll
				);
			}
			else {
				// https://qiita.com/aa_debdeb/items/3d02e28fb9ebfa357eaf
				// クォータニオン > 行列
				DirectX::XMVECTOR quat = DirectX::XMLoadFloat4(&m_quat);
				DirectX::XMFLOAT3X3 mat;
				DirectX::XMStoreFloat3x3(&mat, DirectX::XMMatrixRotationQuaternion(quat));

				// x軸回転の計算
				float rotX = asinf(mat._23);

				// ジンバルロックの確認(cos(rotX) == 0の時に発生)
				bool isLock = (fabsf(rotX) == DirectX::XM_PIDIV2);

				float rotY = 0.0f;
				float rotZ = 0.0f;
				if (isLock) {
					// ジンバルロック中はy軸回転を無視
					rotZ = atanf(mat._12 / mat._11);
				}
				else {
					rotY = atanf(-mat._13 / mat._33);
					rotZ = atanf(-mat._21 / mat._22);
				}

				// 格納
				pVec->x = DirectX::XMConvertToDegrees(rotX);
				pVec->y = DirectX::XMConvertToDegrees(rotY);
				pVec->z = DirectX::XMConvertToDegrees(rotZ);
			}
		}));
	group->AddGroupItem(debug::Item::CreateBind("Scale",	debug::Item::Vector, &m_scale));
	window->AddItem(group);

	// コンポーネントのインスペクター登録
	auto it = m_components.begin();
	while (it != m_components.end())
	{
		(*it)->Debug(window);
		++it;
	}
}
#endif

/*
* @brief 座標設定
*/
void GameObject::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

/*
* @brief サイズ設定
*/
void GameObject::SetScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

/*
* @brief 回転設定
*/
void GameObject::SetQuat(DirectX::XMFLOAT4 quat)
{
	m_quat = quat;
}

void GameObject::Set2DObjNo(int no)
{
	m_2DObjNo = no;
}

void GameObject::Set3DObjNo(int no)
{
	m_3DObjNo = no;
}

/*
* @brief オブジェクトタグ設定
*/
void GameObject::SetTag(std::string tag)
{
	m_tag = tag;
}
/*
* @brief 座標取得
*/
DirectX::XMFLOAT3 GameObject::GetPos()
{
	return m_pos;
}

/*
* @brief 過去座標取得
*/
DirectX::XMFLOAT3 GameObject::GetOldPos()
{
	return m_oldpos;
}
/*
* @brief サイズ取得
*/
DirectX::XMFLOAT3 GameObject::GetScale()
{
	return m_scale;
}
/*
* @brief 回転取得
*/
DirectX::XMFLOAT4 GameObject::GetQuat()
{
	return m_quat;
}
/*
* @brief ワールド行列取得
* @param[in] transpose 転置設定
*/
DirectX::XMFLOAT4X4 GameObject::GetWorld(bool transpose)
{
	// 各要素の行列を取得
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(
		DirectX::XMVectorSet(m_quat.x, m_quat.y, m_quat.z, m_quat.w)
	);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	// 行列の合算
	DirectX::XMMATRIX M = S * R * T;

	// 転置
	if (transpose)
	{
		M = DirectX::XMMatrixTranspose(M);
	}
	// XMMATRIXからXMFLOATへ変換
	DirectX::XMFLOAT4X4 fMat;
	DirectX::XMStoreFloat4x4(&fMat, M);

	return fMat;
}
/*
* @brief 前方ベクトルの取得
*/
DirectX::XMFLOAT3 GameObject::GetFront()
{
	DirectX::XMVECTOR vFront = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vFront = DirectX::XMVector3Rotate(vFront, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vFront));
	return dir;
}

/*
* @brief 右方向ベクトルの取得
*/
DirectX::XMFLOAT3 GameObject::GetRight()
{
	DirectX::XMVECTOR vRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vRight = DirectX::XMVector3Rotate(vRight, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, DirectX::XMVector3Normalize(vRight));
	return dir;
}
/*
* @brief 上方ベクトルの取得
*/
DirectX::XMFLOAT3 GameObject::GetUp()
{
	DirectX::XMVECTOR vUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR qRotate = DirectX::XMLoadFloat4(&m_quat);
	vUp = DirectX::XMVector3Rotate(vUp, qRotate);
	DirectX::XMFLOAT3 dir;
	DirectX::XMStoreFloat3(&dir, vUp);
	return dir;
}

// 2Dオブジェクト番号を返す
int GameObject::Get2DObjNo()
{
	return m_2DObjNo;
}

// 3Dオブジェクト番号を返す
int GameObject::Get3DObjNo()
{
	return m_3DObjNo;
}

/*
* @brief オブジェクトのタグ取得
*/
std::string GameObject::GetTag()
{
	return m_tag;
}

/*
* @brief コンポーネント追加時の初期化処理
*/
void GameObject::_addComponent(Component* component)
{
	// 所持オブジェクトの登録
	component->transform = this;

	// 保存データに一致するコンポーネントがあるか探索
	const char* name = typeid(*component).name();
	auto it = std::find_if(m_datas.begin(), m_datas.end(), [&name](SaveData& data) {
		return strstr(data.name, name) == data.name;
		});
	if (it == m_datas.end()) return;

	// 保存されている情報を設定
	Component::DataAccessor accessor(it->value);
	component->ReadWrite(&accessor);
}