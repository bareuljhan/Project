#pragma once
class GroundATK
{
public:
	enum State
	{
		INTRO_A,
		IDLE_A,
		ATK_A,
		NONE
	};

	GroundATK();
	~GroundATK();

	void Update();
	void Render();

	void SetIDLE();
	void ATKPattern();

	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	void SetAction(State state);

	bool isActive = false;

	shared_ptr<Transform> GetTransform() { return _transform;  }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	State _oldState = NONE;
	State _curState = INTRO_A;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;

	float _delay = 0.0f;
};

