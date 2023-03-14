#pragma once
class Player
{
public:
	enum State
	{
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

	void Ground();
	void NGround();

	void SetAction(State state);
	void SetIDLE();
	void SetRun();
	void SetDUCK();

	void SetColliderSize();
	void SetSpeed(float speed) { _speed = speed; }
	void GetDamaged(float amount);

	void ScreenHP();

	vector<shared_ptr<Bullet>> GetBullets() { return _bullets; }

	shared_ptr<Transform> GetTransform() { return _transform; }
	shared_ptr<CircleCollider> GetBlockCollider() { return _blockCollider; }
	shared_ptr<RectCollider> GetBodyCollider() { return _hitCollider; }

	float GetATK() { return _atk; }

	shared_ptr<Hp> GetHpPNG() { return _health; }

	bool isDead = false;
protected:
	void CreateAction(string name, Action::Type type);


	State _curState = State::IDLE;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Bullet>> _bullets;

	shared_ptr<CircleCollider> _blockCollider;
	shared_ptr<RectCollider> _hitCollider;

	shared_ptr<Effect> _effect;
	
	shared_ptr<Hp> _health;

	Vector2 _origin = { 0,0 };
	Vector2 _originPos = { 0,0 };

	float _jumpPower = 250.0f;
	float _speed = 300.0f;
	float _dashSpeed = 1000.0f;

	float _sceneStart = 0.0f;
	float _sceneDelay = 1.5f;

	float _atk = 10.0f;

	bool _isRight = true;
	bool _isGround = false;

	float _hp = 4;
	const int _poolCount = 30;
};

