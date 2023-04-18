#pragma once
class Coin;

class Inventory
{
public:
	Inventory();
	~Inventory();

	virtual void Update();
	virtual void Render();
	virtual void PostRender();

	void SetCurIndex(int value);

	void Set();
	void SetPannelPos(Vector2 pos) { _pannel->GetTransform()->SetPosition(pos); Update(); Set(); }

	virtual bool AddItem(string name) final;
	virtual void SellItem(string name) final;
	virtual void SellItem() final;
	virtual bool AddMoney(UINT amount) final;
	virtual bool SubMoney(UINT amount) final;

	void UseItem();

	bool ValidIndex() { return _curIndex >= 0 && _curIndex <= 8; }

	bool hp = false;
	bool atk = false;
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

	shared_ptr<Button> _useButton;
	int _curIndex = -1;

	int _coin = 4;
};

