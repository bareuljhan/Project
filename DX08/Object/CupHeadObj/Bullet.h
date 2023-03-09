#pragma once
class Bullet
{
public:	
	enum State
	{
		BASIC,
		SPECIAL,
		NONE
	};
	Bullet();
	~Bullet();
	
	void Update();
	void Render();

	void SetPostion(Vector2 pos);
	void SetFireDir(Vector2 dir);
	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	void SetAction(State state);
	void SetOldState(State state) { _oldState = state; }
	void SetCurState(State state) { _curState = state; }



	shared_ptr<Collider> GetCollider() { return _collider; }

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool isCollision = false;
	bool isActive = false;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::BASIC;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;
	shared_ptr<Collider> _collider2;

	shared_ptr<Effect> _effect;

	float _speed = 400.0f;
	Vector2 _direction = { 0,0 };

	float _delay = 0.0f;
	float _lifeTime = 3.0f;


};