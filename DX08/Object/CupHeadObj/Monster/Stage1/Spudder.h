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
	
	void AttackToPlayer();
	void GetDamaged(float amount);
	void Dead();

	vector<shared_ptr<Monster_Bullet>> GetBullets() { return _bullets; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<Collider> GetBodyCollider() { return _collider; }

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

	vector<shared_ptr<Monster_Bullet>> _bullets;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	float _check = 0.0f;
	float _delay = 4.8f;

	int _count = 0;

	float a = 0.0f;

	float _hp = 200.0f;
};

