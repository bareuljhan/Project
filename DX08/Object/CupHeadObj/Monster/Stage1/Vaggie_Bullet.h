#pragma once
class Vaggie_Bullet
{
public:
	enum State
	{
		BULLET,
		DESTROY,
		NONE
	};
	Vaggie_Bullet();
	~Vaggie_Bullet();

	void Update();
	void Render();

	void SetFireDir(Vector2 dir);

	void Enable();
	void Disable();

	void Destroy();

	void GetDamage(float amount);

	bool Collision(shared_ptr<Collider> col);

	void SetAction(State state);

	void SetFalse() { isActive = false; }

	bool isActive = false;
	bool isDestroy = false;


	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::BULLET;
	State _oldState = State::BULLET;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;

	float _delay = 5.0f;
	float _lifeTime = 0.0f;

	float _a = 1.0f;
	float _b = 0.0f;

	float _speed = 100.0f;
	Vector2 _direction = { 0,0 };

	float _hp = 30;
};

