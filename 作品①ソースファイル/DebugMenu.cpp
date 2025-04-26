#ifdef _DEBUG
#include "DebugMenu.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Input.h"
#include "DirectX.h"
#include <algorithm>
#include <stack>
#include <fstream>

namespace debug {

// static�錾
Item*						Item::dummy = nullptr;
Window						Window::dummy;
std::vector<Window>			Menu::m_windows;
std::vector<Menu::SaveData> Menu::m_data;

//=====================================================
/*
* @brief ���ڕ\��
*/
class ItemValue : public Item
{
public:
	ItemValue() : value{}, save(false) {}
	~ItemValue() {}
public:
	Value	value;
	bool	save;
};
/*
* @brief �\���A�C�e���쐬
*/
Item* Item::CreateValue(const char* name, Kind kind, bool isSave)
{
	ItemValue* item = new ItemValue;
	item->name = name;
	item->kind = kind;
	item->save = isSave;
	item->value.color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	return item;
}

//=====================================================
/*
* @brief �ϐ��ƕR�Â�������
*/
class ItemBind : public Item
{
public:
	ItemBind() : ptr(nullptr) {}
	~ItemBind() {}
public:
	void* ptr;
};
/*
* @brief �R�Â����ڂ̍쐬
*/
Item* Item::CreateBind(const char* name, Kind kind, void* ptr)
{
	ItemBind* item = new ItemBind;
	item->name = name;
	item->kind = kind;
	item->ptr = ptr;
	return item;
}

//=====================================================
/*
* @brief �l�ύX�Ăяo��
*/
class ItemCallback : public Item
{
public:
	ItemCallback() {}
	~ItemCallback() {}
public:
	Value		value;
	Callback	func;
};
/*
* @brief �l�ύX�Ăяo���쐬
*/
Item* Item::CreateCallBack(const char* name, Kind kind, Callback func)
{
	ItemCallback* item = new ItemCallback;
	item->name = name;
	item->kind = kind;
	item->func = func;
	item->value.color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	return item;
}

//=====================================================
/*
* @brief �O���[�v�\��
*/
class ItemGroup : public Item
{
public:
	ItemGroup() {}
	~ItemGroup()
	{
		auto it = group.begin();
		while (it != group.end())
		{
			delete (*it);
			++it;
		}
	}
public:
	Items group;
};
/*
* @brief ���X�g�\���̍쐬
*/
Item* Item::CreateGroup(const char* name)
{
	ItemGroup* item = new ItemGroup;
	item->name = name;
	item->kind = Item::Group;
	return item;
}

//=====================================================
/*
* @brief ���X�g�\��
*/
class ItemList : public Item
{
public:
	ItemList() : selectNo(-1), save(false) {}
	~ItemList() {}
public:
	std::list<std::string>	list;		// �A�C�e���ꗗ
	int						selectNo;	// �I�����ڔԍ�
	ConstCallback			func;		// ���ڑI�����̃R�[���o�b�N
	bool					save;		// �I��ԍ��̕ۑ�
};
/*
* @brief ���X�g�쐬
*/
Item* Item::CreateList(const char* name, ConstCallback func, bool isSave)
{
	ItemList* item = new ItemList;
	item->name = name;
	item->kind = Item::List;
	item->func = func;
	item->save = isSave;
	return item;
}

//=====================================================
// Item
Item::Item()
{
	name = "None";
	kind = Kind::Label;
}
Item::~Item()
{
}
const char* Item::GetName() const
{
	return name.c_str();
}
Item::Kind Item::GetKind() const
{
	return kind;
}
/*
* @brief Bool���ڂ̎擾
*/
bool Item::GetBool() const
{
	if (kind == Bool)
		return reinterpret_cast<const ItemValue*>(this)->value.flg;
	return false;
}
/*
* @brief �������ڂ̎擾
*/
int Item::GetInt() const
{
	if (kind == Int)
		return reinterpret_cast<const ItemValue*>(this)->value.nValue;
	else if (kind == List)
		return static_cast<const ItemList*>(this)->selectNo;
	return 0;
}
/*
* @brief �������ڂ̎擾
*/
float Item::GetFloat() const
{
	if (kind == Float)
		return reinterpret_cast<const ItemValue*>(this)->value.fValue;
	return 0.0f;
}
/*
* @brief �x�N�g�����ڂ̎擾
*/
DirectX::XMFLOAT3 Item::GetVector() const
{
	if (kind == Vector)
		return reinterpret_cast<const ItemValue*>(this)->value.vec;
	return DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}
/*
* @brief �F���ڂ̎擾
*/
DirectX::XMFLOAT4 Item::GetColor() const
{
	if (kind == Color)
		return static_cast<const ItemValue*>(this)->value.color;
	return DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}
/*
* @brief �t�@�C���p�X���ڂ̎擾
*/
const char* Item::GetPath() const
{
	if(kind == Path)
		return static_cast<const ItemValue*>(this)->value.path;
	return "";
}

/*
* @brief ���X�g�\�����ڂ̒ǉ�
*/
void Item::AddListItem(const char* name)
{
	if (kind != List) return;
	reinterpret_cast<ItemList*>(this)->list.push_back(name);
}
/*
* @brief ���X�g�\�����ڂ̍폜
*/
void Item::RemoveListItem(const char* name)
{
	if (kind != List) return;
	reinterpret_cast<ItemList*>(this)->list.remove(name);
}

/*
* @brief �O���[�v���ڂ̒ǉ�
*/
void Item::AddGroupItem(Item* item)
{
	if (kind != Group) return;
	static_cast<ItemGroup*>(this)->group.push_back(item);
}
/*
* @brief �O���[�v���̓��荀�ڂ��擾
*/
Item& Item::operator[](const char* name)
{
	// �O���[�v�ȊO�̎擾�̓_�~�[��ԋp
	if (kind != Group) return *dummy;

	// �O���[�v���̃A�C�e���ꗗ���擾
	auto items = static_cast<ItemGroup*>(this)->group;

	// �A�C�e���ꗗ����w��A�C�e���̒T��
	auto it = std::find_if(items.begin(), items.end(),
		[&name](const Item* obj) {
			return strcmp(obj->GetName(), name) == 0;
		});

	// ���������A�C�e���̕ԋp
	if (it != items.end())
		return **it;

	// ������Ȃ�������_�~�[��ԋp
	return *dummy;
}

/*
* @brief �����񂩂��ʂɕϊ�
*/
Item::Kind Item::StrToKind(std::string str)
{
	if (str == "Label")		return Item::Label;
	if (str == "Bool")		return Item::Bool;
	if (str == "Int")		return Item::Int;
	if (str == "Float")		return Item::Float;
	if (str == "Vector")	return Item::Vector;
	if (str == "Color")		return Item::Color;
	if (str == "Path")		return Item::Path;
	if (str == "Command")	return Item::Command;
	if (str == "Group")		return Item::Group;
	if (str == "List")		return Item::List;
	return Item::Label;
}
/*
* @brief ��ʂ��當����ɕϊ�
*/
std::string Item::KindToStr(Kind kind)
{
	switch (kind) {
	default:
	case Item::Label:		return "Label";
	case Item::Bool:		return "Bool";
	case Item::Int:			return "Int";
	case Item::Float:		return "Float";
	case Item::Vector:		return "Vector";
	case Item::Color:		return "Color";
	case Item::Path:		return "Path";
	case Item::Command:		return "Command";
	case Item::Group:		return "Group";
	case Item::List:		return "List";
	}
}

//=====================================================
// Window
Window::Window()
	: enable(false), name("")
{
}
/*
* @brief �E�B���h�E���̕\�����ڂ��擾
*/
Item& Window::operator[](const char* name)
{
	auto it = FindItem(name);
	if (it == items.end())
		return *Item::dummy;
	return **it;
}
/*
* @brief �E�B���h�E�֕\�����ڂ�ǉ�
*/
void Window::AddItem(Item* item)
{
	// �����̍��ڂƓ����̃A�C�e�����Ȃ����T��
	auto it = FindItem(item->GetName());
	if (it != items.end()) return;

	// �ۑ��f�[�^�̏ꍇ�́A�ǉ����ɕۑ��ς݂̃f�[�^�ŏ㏑��
	Menu::DataRead(name + "/", item);

	// �\�����ڂ̒ǉ�
	items.push_back(item);
}
/*
* @brief �ꗗ�̍폜
*/
void Window::Clear()
{
	auto it = items.begin();
	while (it != items.end())
	{
		delete* it;
		++it;
	}
	items.clear();
}
/*
* @brief �A�C�e���̒T��
*/
Items::iterator Window::FindItem(const char* name)
{
	return std::find_if(items.begin(), items.end(),
		[&name](const Item* obj) {
			return strcmp(obj->GetName(), name) == 0;
		});
}

//=====================================================
// Menu
Menu::Menu()
{
}
Menu::~Menu()
{
}
/*
* @brief ������
*/
void Menu::Init()
{
	// ImGui������
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(GetActiveWindow());
	ImGui_ImplDX11_Init(GetDevice(), GetContext());

	// Dummy�f�[�^������
	Item::dummy = Item::CreateValue("None", Item::Label);
	
	// �����E�B���h�E�̍쐬
	Window window;
	window.name = "Menu";
	m_windows.push_back(window);

	// �t�@�C���ǂݏo��
	FILE* fp;
	fopen_s(&fp, "Assets/DebugMenu.csv", "rt");
	if (fp) {
		const int size = 1024;
		char line[size];
		m_data.clear();
		while (fgets(line, size, fp) != NULL) {
			// �Z�����e�擾
			std::vector<std::string> cells;
			*strstr(line, "\n") = ',';
			char* start = line;
			char* end = strstr(start, ",");
			do {
				*end = '\0';
				cells.push_back(start);
				start = end + 1;
				end = strstr(start, ",");
			} while (end);
			// �f�[�^�ǉ�
			SaveData data;
			data.kind = Item::StrToKind(cells[0]);
			data.path = cells[1];
			data.value = cells[2];
			m_data.push_back(data);
		}
		fclose(fp);
	}
}
/*
* @brief �I������
*/
void Menu::Uninit()
{
	// �_�~�[�̍폜
	delete Item::dummy;

	// �ۑ��f�[�^�̍쐬
	std::string data;
	auto it = m_windows.begin();
	while (it != m_windows.end())
	{
		// �E�B���h�E��O���[�v���K�w�ƂȂ�悤�Ƀp�X���쐬
		std::string path = it->name + "/";

		// �������݂��K�v�ȃf�[�^��ۑ�
		auto itemIt = it->items.begin();
		while (itemIt != it->items.end())
		{
			DataWrite(data, path, *itemIt);
			++itemIt;
		}

		// �E�B���h�E�̃N���A
		it->Clear();
		++it;
	}

	// �ۑ�����
	FILE* fp;
	fopen_s(&fp, "Assets/DebugMenu.csv", "wt");
	if (fp) {
		fwrite(data.c_str(), data.size(), 1, fp);
		fclose(fp);
	}

	// ImGui�I������
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
/*
* @brief �X�V����
*/
void Menu::Update()
{
	// �f�o�b�O���j���[�̕\���؂�ւ�
	auto& mainWindow = m_windows[0];
	if (IsKeyPress(VK_SHIFT) && IsKeyPress(VK_SPACE)) {
		if (IsKeyTrigger(VK_RETURN))
			mainWindow.enable ^= true;
	}

	// ���C���E�B���h�E�̃`�F�b�N�󋵂ɉ����Ăق��̃E�B���h�E��\��
	int cnt = 1; // 0�̓��C���E�B���h�E�Ȃ̂ōl�����Ȃ�
	auto it = mainWindow.items.begin();
	while (it != mainWindow.items.end())
	{
		m_windows[cnt].enable = (*it)->GetBool();
		++it;
		++cnt;
	}
}
/*
* @brief �\��
*/
void Menu::Draw()
{
	// ���C���E�B�h�E���L���ɂȂ��Ă��Ȃ���Δ�\��
	if (!m_windows[0].enable)
		return;

	// Imgui�̕`�揀��
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �E�B���h�E���̕\�����ڂ�`��
	auto windowIt = m_windows.begin();
	while (windowIt != m_windows.end())
	{
		if (windowIt->enable)
		{
			// �E�B���h�E���̕`��J�n
			ImGui::Begin(windowIt->name.c_str());

			// �A�C�e�����Ƃɕ`��
			auto itemIt = windowIt->items.begin();
			while (itemIt != windowIt->items.end())
			{
				DrawImgui(*itemIt);
				++itemIt;
			}

			// �E�B���h�E���̕`��I��
			ImGui::End();
		}
		++windowIt;
	}

	// ImGui�̕\��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

/*
* @brief �E�B���h�E�̍쐬
*/
Window& Menu::Create(const char* name)
{	
	// �E�B���h�E��T�����Ă��łɂ���ꍇ�͒ǉ����Ȃ�
	auto winIt = std::find_if(m_windows.begin(), m_windows.end(),
		[&name](const Window& obj) {
		return strcmp(obj.name.c_str(), name) == 0;
	});
	if (winIt != m_windows.end()) {
		return *winIt;
	}

	// �ʃE�B���h�E�ݒ�
	Window window;
	window.name = name;
	window.enable = false;
	window.items.clear();
	m_windows.push_back(window);

	// �����E�B���h�E�ɒǉ�
	Item* label = Item::CreateValue(name, Item::Bool, true);
	DataRead(m_windows[0].name + "/", label);
	m_windows[0].items.push_back(label);

	return m_windows.back();
}
/*
* @brief �����E�B���h�E�̎擾
*/
Window& Menu::Get(const char* name)
{
	// �E�B���h�E�̒T��
	auto winIt = std::find_if(m_windows.begin(), m_windows.end(),
		[&name](const Window& obj) {
			return strcmp(obj.name.c_str(), name) == 0;
		});

	// ������Ȃ���΃_�~�[��ԋp
	if (winIt == m_windows.end())
		return Window::dummy;

	// ���������E�B���h�E��ԋp
	return *winIt;
}
/*
* @brief ���ڂɉ�����Imgui�̕\��
*/
void Menu::DrawImgui(Item* item)
{
	// �e�v�f�̎擾
	bool isValue	= typeid(ItemValue) == typeid(*item);
	bool isBind		= typeid(ItemBind) == typeid(*item);
	bool isCallback	= typeid(ItemCallback) == typeid(*item);
	ItemValue*		pValue		= static_cast<ItemValue*>(item);
	ItemBind*		pBind		= static_cast<ItemBind*>(item);
	ItemCallback*	pCallback	= static_cast<ItemCallback*>(item);

	switch (item->GetKind())
	{
	// ���ږ��݂̂̕\��
	case Item::Label:
		ImGui::Text("%s", item->GetName());
		break;
	// �`�F�b�N�t���O�̕\��
	case Item::Bool:
		if (isValue)
			ImGui::Checkbox(item->GetName(), &pValue->value.flg);
		else if (isBind)
			ImGui::Checkbox(item->GetName(), reinterpret_cast<bool*>(pBind->ptr));
		else if (isCallback) {
			pCallback->func(false, &pCallback->value.flg);
			if (ImGui::Checkbox(item->GetName(), &pCallback->value.flg))
				pCallback->func(true, &pCallback->value.flg);
		}
		break;
	// �������ڂ̕\��
	case Item::Int:
		if(isValue)
			ImGui::InputInt(item->GetName(), &pValue->value.nValue);
		else if(isBind)
			ImGui::InputInt(item->GetName(), reinterpret_cast<int*>(pBind->ptr));
		else if (isCallback) {
			pCallback->func(false, &pCallback->value.nValue);
			if (ImGui::InputInt(item->GetName(), &pCallback->value.nValue))
				pCallback->func(true, &pCallback->value.nValue);
		}
		break;
	// �������ڂ̕\��
	case Item::Float:
		if(isValue)
			ImGui::InputFloat(item->GetName(), &pValue->value.fValue);
		else if(isBind)
			ImGui::InputFloat(item->GetName(), reinterpret_cast<float*>(pBind->ptr));
		else if (isCallback) {
			pCallback->func(false, &pCallback->value.fValue);
			if (ImGui::InputFloat(item->GetName(), &pCallback->value.fValue))
				pCallback->func(true, &pCallback->value.fValue);
		}
		break;
	// �x�N�g�����ڂ̕\��
	case Item::Vector:
		if(isValue)
			ImGui::InputFloat3(item->GetName(), &pValue->value.vec.x, "%.4f");
		else if(isBind)
			ImGui::InputFloat3(item->GetName(), reinterpret_cast<float*>(pBind->ptr), "%.4f");
		else if (isCallback) {
			pCallback->func(false, &pCallback->value.vec.x);
			if (ImGui::InputFloat3(item->GetName(), &pCallback->value.vec.x, "%.4f"))
				pCallback->func(true, &pCallback->value.vec.x);
		}
		break;
	// �F���ڂ̕\��
	case Item::Color:
		if (isValue)
			ImGui::ColorEdit4(item->GetName(), &pValue->value.color.x);
		else if(isBind)
			ImGui::ColorEdit4(item->GetName(), reinterpret_cast<float*>(pBind->ptr));
		else if (isCallback) {
			pCallback->func(false, &pCallback->value.color.x);
			if(ImGui::ColorEdit4(item->GetName(), &pCallback->value.color.x))
				pCallback->func(true, &pCallback->value.color.x);
		}
		break;
	// �p�X���ڂ̕\��
	case Item::Path:
		if (typeid(ItemValue) == typeid(*item)) // �ʏ�\��
			ImGui::InputText(item->GetName(), static_cast<ItemValue*>(item)->value.path, MAX_PATH);
		else // �R�Â����ڂ̕\��
			ImGui::InputText(item->GetName(), reinterpret_cast<char*>(static_cast<ItemBind*>(item)->ptr), MAX_PATH);
		break;
	// �{�^���̕\��
	case Item::Kind::Command:
		if (ImGui::Button(item->GetName()))
			pCallback->func(false, nullptr);
		break;
	// �O���[�v���ڂ̕\��
	case Item::Group:
		{
			ItemGroup* ptr = reinterpret_cast<ItemGroup*>(item);
			// �\�����ڂ��Ȃ���Ε\�����Ȃ�
			if (ptr->group.empty()) break;

			// �O���[�v���W�J����ĂȂ���Ε\�����Ȃ�
			if (!ImGui::CollapsingHeader(item->GetName(), ImGuiTreeNodeFlags_DefaultOpen)) break;

			// �O���[�v���̍��ڂ��ċA�ŕ\��
			auto it = ptr->group.begin();
			while (it != ptr->group.end())
			{
				DrawImgui(*it);
				++it;
			}
		}
		break;
	// ���X�g���ڂ̕\��
	case Item::List:
		{
			ItemList* ptr = reinterpret_cast<ItemList*>(item);
			// �\�����ڂ��Ȃ���Ε\�����Ȃ�
			if (ptr->list.empty()) break;

			// �\�����ڂ̍\�z
			static const char* pList[100];
			auto it = ptr->list.begin();
			for (int i = 0; i < ptr->list.size() && i < 100; ++i, ++it)
				pList[i] = it->c_str();

			// �\��
			if(ImGui::ListBox(item->GetName(), &ptr->selectNo, pList, static_cast<int>(ptr->list.size())))
			{
				// �֐�������ΑI�������������s
				if(ptr->func && ptr->selectNo >= 0)
					ptr->func(pList[ptr->selectNo]);
			}
		}
		break;
	}
}
/*
* @brief �f�[�^�̕ۑ�
*/
void Menu::DataWrite(std::string& data, std::string path, Item* item)
{
	// �O���[�v�A�C�e���ł���΁A�p�X���X�V���čċA�Ăяo��
	if (item->GetKind() == Item::Group)
	{
		ItemGroup* groupItem= static_cast<ItemGroup*>(item);

		// �p�X�̍X�V
		path = path + groupItem->GetName() + "/";

		// �O���[�v���A�C�e���̃f�[�^��������
		auto it = groupItem->group.begin();
		while (it != groupItem->group.end())
		{
			DataWrite(data, path, *it);
			++it;
		}

		// �ȍ~�̏����͍s��Ȃ�
		return;
	}

	// �ۑ��t���O���ݒ肳��Ă��邩�m�F
	ItemValue* pValue = static_cast<ItemValue*>(item);
	ItemList* pList = static_cast<ItemList*>(item);
	if (typeid(*item) == typeid(ItemValue)) {
		if (!pValue->save) return;
	}
	else if (typeid(*item) == typeid(ItemList)) {
		if (!pList->save) return;
	}
	else {
		return;
	}

	// ���ڂ̏�������
	data += Item::KindToStr(item->GetKind()) + ",";
	// �\�����̏�������
	data += path + item->GetName() + ",";
	// ���ڕʂ̏�������
	switch (item->GetKind())
	{
	default:
		data += "0";
	case Item::Bool:
		data += pValue->value.flg ? "1" : "0";
		break;
	case Item::Int:
		data += std::to_string(pValue->value.nValue);
		break;
	case Item::Float:
		data += std::to_string(pValue->value.fValue);
		break;
	case Item::Color:
		data += std::to_string(pValue->value.color.x) + "/";
		data += std::to_string(pValue->value.color.y) + "/";
		data += std::to_string(pValue->value.color.z) + "/";
		data += std::to_string(pValue->value.color.w);
		break;
	case Item::List:
		data += std::to_string(pList->selectNo);
		break;
	}
	data += "\n";
}
/*
* @brief �f�[�^�̓ǂݎ��
*/
void Menu::DataRead(std::string path, Item* item)
{
	// �O���[�v�A�C�e���ł���΁A�p�X���X�V���čċA�Ăяo��
	if (item->GetKind() == Item::Group)
	{
		ItemGroup* groupItem = static_cast<ItemGroup*>(item);
		// �p�X�̍X�V
		path = path + groupItem->GetName() + "/";

		// �O���[�v���A�C�e���̃f�[�^�ǂݎ��
		auto it = groupItem->group.begin();
		while (it != groupItem->group.end())
		{
			DataRead(path, *it);
			++it;
		}

		// �ȍ~�̏����͍s��Ȃ�
		return;
	}

	// �ۑ��t���O���ݒ肳��Ă��邩�m�F
	ItemValue* pValue = static_cast<ItemValue*>(item);
	ItemList* pList = static_cast<ItemList*>(item);
	if (typeid(*item) == typeid(ItemValue)) {
		if (!pValue->save) return;
	}
	else if (typeid(*item) == typeid(ItemList)) {
		if (!pList->save) return;
	}
	else {
		return;
	}

	// �p�X�ƍ��ږ�����ǂݎ��f�[�^�����쐬
	path += item->GetName();

	// �f�[�^���ɑΉ�����f�[�^��T��
	auto dataIt = std::find_if(m_data.begin(), m_data.end(),
		[&path](const SaveData& data) {
			return data.path == path;
		});

	// �Ȃ���΃f�[�^�̏㏑�����s��Ȃ�
	if (dataIt == m_data.end()) return;

	// ���ڂɉ����ăf�[�^�̓ǂݎ��
	switch (item->GetKind())
	{
	case Item::Bool:
		pValue->value.flg = atoi(dataIt->value.c_str()) > 0;
		break;
	case Item::Int:
		pValue->value.nValue = atoi(dataIt->value.c_str());
		break;
	case Item::Float:
		pValue->value.fValue = strtof(dataIt->value.c_str(), nullptr);
		break;
	case Item::Color: {
		const char* top[] = {
			dataIt->value.c_str(),
			strstr(top[0], "/") + 1,
			strstr(top[1], "/") + 1,
			strstr(top[2], "/") + 1,
		};
		pValue->value.color = DirectX::XMFLOAT4(
			strtof(top[0], nullptr),
			strtof(top[1], nullptr),
			strtof(top[2], nullptr),
			strtof(top[3], nullptr)
		);
		} break;
	case Item::List:
		pList->selectNo = atoi(dataIt->value.c_str());
		if (pList->func) {
			auto it = pList->list.begin();
			//for (int i = 0; i < pList->selectNo; ++i)
			//	it++;
			pList->func(it->c_str());
		}
		break;
	}
}
} // namespace debug
#endif // _DEBUG