#pragma once
class Carrot
{
public:
	enum State
	{
		INTRO,
		IDLE,
		MOVE,
		DEAD,
		NONE
	};
	Carrot();
	~Carrot();

	virtual void Update();
	virtual void Render();

	void SetMove();
	void GetDamaged(float amount);
	void Dead();

	void SetAction(State state);
	void SetIDLE();

	void Move(shared_ptr<Player> player);

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetBodyCollider() { return _collider; }

	bool isDead = false;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::INTRO;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _collider;

	float _speed = 200.0f;

	float _hp = 150.0f;
};

