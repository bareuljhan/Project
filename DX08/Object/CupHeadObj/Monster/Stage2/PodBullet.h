#pragma once
class PodBullet
{
public:
	enum State
	{
		BLUE,
		RED,
		PURPLE,
		NONE
	};
	PodBullet();
	~PodBullet();

	void Update();
	void Render();

	void SetAction(State state);
	void ChomperSpawn();

	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	bool isActive = false;
	bool isFloorOne = false;
	bool isFloorTwo = false;
	bool isFloorThr = false;

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Vine> GetVine() { return _vine; }
	shared_ptr<Chomper> GetChomperOne() { return _chompers[0]; }
	shared_ptr<Chomper> GetChomperTwo() { return _chompers[1]; }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	State _oldState = NONE;
	State _curState = BLUE;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr <Chomper>> _chompers;
	shared_ptr<Vine> _vine;

	shared_ptr<Collider> _collider;

	shared_ptr<Effect> _effect;

	Vector2 _direction = { 0, 1 };
	float _speed = 150.0f;

	float _chomperDelay = 0.0f;
	float _chomperDelayTwo = 0.0f;
	float _vineDelay = 0.0f;
};

