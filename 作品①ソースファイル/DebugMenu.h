/**
 * 2024.04.08
 *	imgui�����A�e�L�X�g�t�@�C���ǂݍ��݁A�o�C���h�ǉ�
 * 2024.04.09
 *	Bind�������R�[���o�b�N�őΉ��A�f�[�^�̓ǂݏ�����ǉ��A���X�g�ǉ��A�V�[���̐؂�ւ�
 * 2024.04.10
 *	���f���̐؂�ւ��A�V�[���̐؂�ւ�
 * 2024.07.23
 * �@�\�����e���f�[�^����ǂݎ��̂ł͂Ȃ��A�v���O������Őݒ�ł���悤�ɕύX
 * �@GameObject��ύX���āAUnity���̃C���X�y�N�^�[�\�����s���悤�ɕύX
 */
#ifndef __DEBUG_MENU_H__
#define __DEBUG_MENU_H__

#ifdef _DEBUG
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <vector>
#include <DirectXMath.h>
#include <Windows.h>

namespace debug {

/*
* @brief �\������
*/
class Item
{
public:
	using Callback = std::function<void(bool isWrite, void* arg)>;
	using ConstCallback = std::function<void(const void* arg)>;
	union Value {
		bool				flg;
		int					nValue;
		float				fValue;
		DirectX::XMFLOAT3	vec;
		DirectX::XMFLOAT4	color;
		char				path[MAX_PATH];
	};
	enum Kind {
		Label,		// ���ڂ݂̂̕\��
		Bool,		// �`�F�b�N�{�b�N�X
		Int,		// ��������
		Float,		// ��������
		Vector,		// �x�N�^�[����
		Color,		// �F����
		Path,		// �t�@�C���p�X�̎w��
		Command,	// �{�^��
		Group,		// �\�����ڂ��܂Ƃ߂�
		List,		// �ꗗ�\��
	};
protected:
	Item();
public:
	virtual ~Item();
	// ���ڒǉ�
	static Item* CreateValue(const char* name, Kind kind, bool isSave = false);
	// �ϐ���R�Â�������
	static Item* CreateBind(const char* name, Kind kind, void* ptr);
	// �{�^��or�l�ύX��
	static Item* CreateCallBack(const char* name, Kind kind, Callback func);
	// �O���[�v
	static Item* CreateGroup(const char* name);
	// �ꗗ�\��
	static Item* CreateList(const char* name, ConstCallback func = nullptr, bool isSave = false);

public:
	// ���ږ��̎擾
	const char* GetName() const;
	// ���ڎ�ʂ̎擾
	Kind GetKind() const;

	// �e��ݒ�l�̎擾
	bool GetBool() const;
	int GetInt() const;
	float GetFloat() const;
	DirectX::XMFLOAT3 GetVector() const;
	DirectX::XMFLOAT4 GetColor() const;
	const char* GetPath() const;

	// �O���[�v�̐ݒ�
	void AddGroupItem(Item* item);
	Item& operator[](const char* name);

	// �ꗗ�\���̐ݒ�
	void AddListItem(const char* name);
	void RemoveListItem(const char* name);

public:
	// �����񂩂獀�ڂ̎�ʂ��擾
	static Kind StrToKind(std::string str);
	// ���ڂ̎�ʂ��當������擾
	static std::string KindToStr(Kind kind);

public:
	static Item* dummy;	// �w��f�[�^���擾�ł��Ȃ������ꍇ�̃_�~�[
private:
	std::string name;	// 
	Kind kind;			// ���ڎ��
};
using Items = std::list<Item*>;

/*
* @brief �f�o�b�O�E�B���h�E
*/
class Window
{
	friend class Menu;
public:
	Window();
	Item& operator[](const char* name);

	// �A�C�e���ǉ�
	void AddItem(Item* item);
	// �A�C�e���폜
	void RemoveItem(const char* name);
	// �S�A�C�e���폜
	void Clear();

private:
	// �A�C�e���̒T��
	Items::iterator FindItem(const char* name);

public:
	static Window	dummy;	// �w��E�B���h�E���擾�ł��Ȃ������Ƃ��̃_�~�[
private:
	bool			enable;	// �\���t���O
	std::string		name;	// �E�B���h�E��
	Items			items;	// �\������
};

/*
* @brief �f�o�b�O�\���ꌳ�Ǘ�
*/
class Menu
{
	friend class Window;
public:
	// �ۑ��f�[�^
	struct SaveData
	{
		Item::Kind kind;
		std::string path;
		std::string value;
	};
private:
	Menu();
	~Menu();

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �E�B���h�E����
	static Window& Create(const char* name);
	// �E�B���h�E�擾
	static Window& Get(const char* name);
private:
	static void DrawImgui(Item* item);
	static void DataWrite(std::string& data, std::string path, Item* item);
	static void DataRead(std::string path, Item* item);

private:
	static std::vector<Window>		m_windows;	// �\���E�B���h�E�ꗗ
	static std::vector<SaveData>	m_data;		// �ۑ��f�[�^
};

} // namespace debug
#endif // _DEBUG
#endif // __DEBUG_MENU_H__