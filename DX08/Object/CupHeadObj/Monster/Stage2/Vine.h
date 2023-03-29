#pragma once
class Vine
{
public:
	enum State
	{
		IDLE,
		ATK,
		NONE
	};
	Vine();
	~Vine();

	void Update();
	void Render();

	void SetAction(State state);

	void Enable();
	void Disable();

	void SetAttack();

	bool Collision(shared_ptr<Collider> col);

	bool isActive = true;

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetCollider() { return _collider; }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	State _curState = IDLE;
	State _oldState = NONE;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;
	shared_ptr<Effect> _effect;

	float _speed = 100.0f;

	Vector2 _direction = { -1,1 };

	float _delay = 0.0f;
};

