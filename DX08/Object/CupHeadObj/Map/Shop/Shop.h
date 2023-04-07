#pragma once
class Shop : public Inventory
{
public:
	enum State
	{
		WELCOME,
		IDLE,
		GOODBYE,
		NONE
	};
	Shop();
	~Shop();

	void Update();
	void Render();
	void PostRender();

	void SetAction(State state);

	void SetIDLE() { SetAction(State::IDLE); }
	void TableMove();
	void TableReturn();

	void SetStoreItems();

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool isMove = false;
	bool isReturn = false;
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	State _oldState = NONE;
	State _curState = WELCOME;

	shared_ptr<Quad> _bg;
	shared_ptr<Quad> _table;
	shared_ptr<Quad> _cutton;
	shared_ptr<Quad> _left;
	shared_ptr<Quad> _right;

	shared_ptr<Quad> _chalk;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<ItemIconButton>> _icons;

	float _speed = 300.0f;
};

