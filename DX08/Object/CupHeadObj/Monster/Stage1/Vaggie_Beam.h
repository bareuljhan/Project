#pragma once
class Vaggie_Beam
{
public:
	enum State
	{
		BEAM,
		NONE
	};
	Vaggie_Beam();
	~Vaggie_Beam();
	
	void Update();
	void Render();

	void SetFireDir(Vector2 dir);

	void Enable();
	void Disable();
	void SetAction(State state);

	bool Collision(shared_ptr<Collider> col);
	
	shared_ptr<Transform> GetTransform() { return _transform; }

	bool isActive = false;
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	State _oldState = NONE;
	State _curState = BEAM;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
	Vector2 _direction = { 0, 0 };
	float _speed = 300.0f;

	float _delay = 1.5f;
	float _lifeTime = 0.0f;
};

