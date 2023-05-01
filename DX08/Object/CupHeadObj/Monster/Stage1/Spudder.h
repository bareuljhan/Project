#pragma once
class Spudder
{
public:	

enum State
{
	SPAWN,
	IDLE,
	DEAD,
	NONE
};
	Spudder();
	~Spudder();

	virtual void Update();
	virtual void Render();

	void SetAction(State state);
	void SetIDLE();

	void Init();
	
	void BeamAttack();
	void GetDamaged(float amount);
	void Dead();

	vector<shared_ptr<Spudder_Bullet>> GetBullets() { return _bullets; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetBodyCollider() { return _collider; }
	shared_ptr<Action> GetAction() { return _actions[_curState]; }
	bool isDead = false;
	bool isNextMonster = false;
private:
	void CreateAction(string name, Action::Type type);


	State _curState = State::SPAWN;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	shared_ptr<RectCollider> _collider;
	shared_ptr<CircleCollider> _bulletCol;

	shared_ptr<Quad> _support;

	vector<shared_ptr<Spudder_Bullet>> _bullets;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Effect> _effect;

	float _check = 0.0f;
	float _delay = 4.8f;

	float _efCheck = 0.0f;

	int _count = 0;

	float a = 0.0f;

	float _hp = 200.0f;
};

