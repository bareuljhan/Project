#pragma once
class Player
{
public:
	enum State
	{
		INTRO,
		IDLE,
		RUN,
		JUMP,
		DUCK,
		SHOT,
		AIMUPSHOT,
		DIAGONALSHOT,
		DUCKSHOT,
		GROUNDDASH,
		SKILLSHOT,
		RUNSHOT,
		HIT,
		DEAD,
		REVIVE,
		NONE
	};
	Player();
	~Player();

	virtual void Update();
	virtual void Render();

	void SetRight();
	void SetLeft();

	void Input();
	void Jump();
	void Shot();
	void AimUpShot();
	void DiagonalShot();
	void DuckShot();
	void SkillShot();
	void SkillAction();
	void SetGravity(float value) { _subGravity = value; }
	void Ground();
	void NGround();

	void SetAction(State state);
	void SetIDLE();
	void SetRun();
	void SetDUCK();

	void Dead();
	void Revive();

	void SetColliderSize();
	void SetSpeed(float speed) { _speed = speed; }
	void GetDamaged(float amount);

	void ScreenHP();

	vector<shared_ptr<Bullet>> GetBullets() { return _bullets; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetBlockCollider() { return _blockCollider; }
	shared_ptr<RectCollider> GetBodyCollider() { return _hitCollider; }
	shared_ptr<Action> GetAction() { return _actions[_curState]; }

	float GetATK() { return _atk; }

	shared_ptr<Hp> GetHpPNG() { return _health; }

	bool isDead = false;
	bool isInvincible = false;
protected:
	void CreateAction(string name, Action::Type type);


	State _curState = State::INTRO;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Bullet>> _bullets;

	shared_ptr<Inventory> _inven;

	shared_ptr<CircleCollider> _blockCollider;
	shared_ptr<RectCollider> _hitCollider;

	shared_ptr<Effect> _effect;
	
	shared_ptr<Hp> _health;

	Vector2 _origin = { 0,0 };
	Vector2 _originPos = { 0,0 };

	float _jumpPower = 200.0f;
	float _subGravity = 10.0f;
	float _speed = 300.0f;
	float _dashSpeed = 1000.0f;

	float _effectStart = 0.0f;
	float _effectDelay = 0.3f;

	float _atk = 10.0f;

	bool _isRight = true;
	bool _isGround = false;

	float _hp = 4;
	const int _poolCount = 30;

	float _invincibleTime = 2.5f;
	float _delay = 0.0f;
};

