#pragma once
class Coin;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render();
	void PostRender();

	void SetCurIndex(int value);

	void Set();
	void SetPannelPos(Vector2 pos) { _pannel->GetTransform()->SetPosition(pos); Update(); Set(); }

	void BuyItem(string name);
	void SellItem(string name);
	void SellItem();
	bool AddMoney(UINT amount);
	bool SubMoney(UINT amount);

protected:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Quad> _pannel;
	shared_ptr<Quad> _noise;
	shared_ptr<Quad> _text;

	shared_ptr<Sprite> _cupSprite;
	shared_ptr<Action> _cupAction;
	
	Vector2 _slotOffset;

	vector<shared_ptr<Slot>> _slots;
	vector<shared_ptr<Coin>> _coins;
	vector<ItemInfo> _itemDates;

	vector<shared_ptr<ItemIconButton>> _icons;

	int _curIndex = -1;

	int _coin = 4;
};

