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

	shared_ptr<Transform> GetTransform() { return _transform; }
	bool isActive = false;
	bool isEnd = false;
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
	float _speed = 200.0f;

	float _delay = 0.0f;
	
};

