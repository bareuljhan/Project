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

private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Quad> _pannel;
	shared_ptr<Quad> _noise;
	shared_ptr<Quad> _text;
	
	Vector2 _slotOffset;

	vector<shared_ptr<Slot>> _slots;
	vector<shared_ptr<Coin>> _coins;

	shared_ptr<Sprite> _cupSprite;
	shared_ptr<Action> _cupAction;

	shared_ptr<ItemIcon> _icon;

	UINT _coin = 2;
};

