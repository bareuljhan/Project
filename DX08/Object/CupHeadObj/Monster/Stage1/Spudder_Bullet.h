#pragma once
class Spudder_Bullet
{
public:
	enum State
	{
		SPUDDER_BULLET,
		NONE
	};
	Spudder_Bullet();
	~Spudder_Bullet();

	void Update();
	void Render();

	void SetFireDir(Vector2 dir);

	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	void SetAction(State state);

	bool isActive = false;

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::SPUDDER_BULLET;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;

	float _speed = 400.0f;
	Vector2 _direction = { 0,0 };

	float _delay = 0.0f;
	float _lifeTime = 3.0f;
};
