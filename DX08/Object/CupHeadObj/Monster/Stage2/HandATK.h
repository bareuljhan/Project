#pragma once
class HandATK
{
public:
	enum State
	{
		BALL,
		BALLATK,
		BOOMERANG,
		NONE
	};
	HandATK();
	~HandATK();

	void Update();
	void Render();

	void Enable();
	void Disable();

	void SetFireDir(Vector2 dir);

	bool Collision(shared_ptr<Collider> col);

	void SetAction(State state);

	State GetCurState() { return _curState; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	bool isActive = false;
	bool isEnd = false;
	float delay = 0.0f;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = BALL;
	State _oldState = NONE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;

	shared_ptr<Effect> _effect;

	Vector2 _direction = { 0,0 };
	float _speed = 300.0f;
	float _boomerangSpeed = 350.0f;
};

