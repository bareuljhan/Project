#include "framework.h"
#include "Inventory.h"

Inventory::Inventory()
{
#pragma region InvenSetting
	_pannel = make_shared<Quad>(L"Resource/Texture/CupHead/Pannel.png");
	_pannel->GetTransform()->SetPosition(Vector2(1100, CENTER_Y + 100));
	_pannel->GetTransform()->SetScale(Vector2(0.6f, 0.6f));

	_noise = make_shared<Quad>(L"Resource/Texture/CupHead/Noise.png");
	_noise->GetTransform()->SetPosition(_pannel->GetTransform()->GetPos());
	_noise->GetTransform()->SetScale(Vector2(0.8f, 1.5f));

	_text = make_shared<Quad>(L"Resource/Texture/CupHead/world_map_equip_text.png");
	_text->GetTransform()->SetPosition(Vector2(_pannel->GetTransform()->GetPos().x, _pannel->GetTransform()->GetPos().y + 145));
	_text->GetTransform()->SetScale(Vector2(1.7f, 1.0f));

	CreateAction("InvenAni", Action::Type::LOOP);

	_cupSprite->GetTransform()->SetPosition(Vector2(_pannel->GetTransform()->GetPos().x - 120, _pannel->GetTransform()->GetPos().y + 145));
	_cupSprite->GetTransform()->SetScale(Vector2(0.18f, 0.18f));

	_cupAction->Play();

	_slotOffset = Vector2(180, 120);

	for (int y = 1; y >= -1; y--)
	{
		for (int x = -1; x < 2; x++)
		{
			shared_ptr<Slot> slot = make_shared<Slot>();
			slot->SetPosition(Vector2(_slotOffset.x * x, (_slotOffset.y * y) - 20));
			slot->SetParent(_pannel->GetTransform());
			_slots.push_back(slot);
		}
	}

	Vector2 CoinOffset = Vector2(-110, -230);

	for (int i = 0; i < 8; i++)
	{
		shared_ptr<Coin> coin = make_shared<Coin>();
		coin->GetTransform()->SetPosition(Vector2(CoinOffset.x + i * 50, CoinOffset.y));
		coin->GetTransform()->SetScale(Vector2(0.25f, 0.25f));
		coin->GetTransform()->SetParent(_pannel->GetTransform());
		_coins.push_back(coin);
	}


	for (int i = 0; i < 9; i++)
	{
		shared_ptr<ItemIconButton> icon = make_shared<ItemIconButton>();
		icon->SetScale(Vector2(0.4f, 0.4f));
		icon->GetButton()->SetIntEvent(std::bind(&Inventory::SetCurIndex, this, i));
		_icons.push_back(icon);
	}
	_itemDates.resize(9);
#pragma endregion

	Set();
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
	_pannel->Update();
	_noise->Update();
	_text->Update();
	_cupAction->Update();
	_cupSprite->Update();
	
	for(auto icon : _icons)
		icon->Update();

	for (auto slot : _slots)
		slot->Update();
	
	for (int i = 0; i < _coin; i++)
	{
		_coins[i]->Update();
	}
}

void Inventory::Render()
{
	_pannel->Render();
	_text->Render();
	for (auto slot : _slots)
		slot->Render();
	_noise->Render();
	_cupSprite->Render();
	_cupSprite->SetActionClip(_cupAction->GetCurClip());

	for (int i = 0; i < _coin; i++)
	{
		_coins[i]->Render();
	}
	for(auto icon : _icons)
		icon->Render();
}

void Inventory::PostRender()
{
	RECT rect;
	rect.left = 940;
	rect.right = 1040;
	rect.top = 385;
	rect.bottom = 445;

	DirectWrite::GetInstance()->RenderText(L"COIN => ", rect);

	if (_curIndex >= 0 && _curIndex < 9)
	{
		ItemInfo temp = _itemDates[_curIndex];
		ImGui::Text(temp.name.c_str());
		ImGui::SliderInt("index", &_curIndex, 0, 8);
	}
}

void Inventory::SetCurIndex(int value)
{
	if (value < 0 || value > 9)
	{
		_curIndex = -1;
		return;
	}
	_curIndex = value;
}

void Inventory::Set()
{

	for (int i = 0; i < _icons.size(); i++)
	{
		_icons[i]->SetPosition(Vector2(_slots[i]->GetTransform()->GetWorldPos().x, _slots[i]->GetTransform()->GetWorldPos().y - 5));
		_icons[i]->SetItem(_itemDates[i]);
	}
}

bool Inventory::AddItem(string name)
{
	ItemInfo info = DATA_M->GetItemByName(name);

	if (info.name == "" || _coin - info.price < 0)
		return false;

	auto iter = std::find_if(_itemDates.begin(), _itemDates.end(), [](const ItemInfo& info)->bool
	{
		if (info.name == "")
			return true;
		return false;
	});
	
	if (iter == _itemDates.end())
		return false;

	*iter = info;
	
	Set();
	return true;
}

void Inventory::SellItem(string name)
{
	auto iter = std::find_if(_itemDates.begin(), _itemDates.end(),[name](const ItemInfo& info) -> bool 
	{
		if (info.name == name)
			return true;
		return false;
	});

	if (iter == _itemDates.end())
		return;
	AddMoney(iter->price);
	iter->SetEmpty();

	Set();

}

void Inventory::SellItem()
{
	if (_curIndex < 0 || _curIndex > 8) return;

	ItemInfo& info = _itemDates[_curIndex];

	if (info.name == "")
		return;

	AddMoney(info.price);
	info.SetEmpty();

	_curIndex = -1;
	Set();
}

bool Inventory::AddMoney(UINT amount)
{
	_coin += amount;
	return true;
}

bool Inventory::SubMoney(UINT amount)
{
	if (_coin - amount < 0)
		return false;
	_coin -= amount;
	return true;
}

void Inventory::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Shop/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Shop/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;

	_cupAction = make_shared<Action>(xml.GetClips(), actionName, type);
	_cupSprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
