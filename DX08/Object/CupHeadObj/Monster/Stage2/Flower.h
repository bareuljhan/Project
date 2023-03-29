#pragma once
class Flower
{
public:
	enum State
	{
		INTRO,
		IDLE,
		GATLING,
		HANDATK,
		TRANSFORM,
		NEWIDLE,
		ATK,
		DEAD,
		NONE
	};
	Flower();
	~Flower();

	void Update();
	void Render();

	void SetAction(State state);

	void AttackPattern();

	void SetIDLE();
	void SetGatling();
	void SetHandATK();
	void SetNewIDLE();
	void SetATK();

	void PlayEffect();
	void PlayHandEffect();
	void GroundEffect();

	void GetDamaged(float amount);
	void Dead();

	void BallAttack(shared_ptr<Player> player);
	void PotBallATK();
	void PuffATK();
	void VineATK();

	bool isUpdate = false;
	bool isDead = false;

	vector<shared_ptr<HandATK>> GetBalls() { return _balls; }
	vector<shared_ptr<PodBullet>> GetBullets() { return _podBullets; }
	vector<shared_ptr<PuffBall>> GetPuffBalls() { return _puffBalls; }
	vector<shared_ptr<GroundATK>> GetGround() { return _atks; }
	shared_ptr<PodBullet> GetBulletOne() { return _podBullets[0]; }
	shared_ptr<PodBullet> GetBulletTwo() { return _podBullets[1]; }
	shared_ptr<PodBullet> GetBulletThr() { return _podBullets[2]; }

	shared_ptr<RectCollider> GetBodyCollider() { return _hitCollider; }
private:
	void CreateAction(string name, Action::Type type);

	State _oldState = NONE;
	State _curState = IDLE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<PodBullet>> _podBullets;
	vector<shared_ptr<HandATK>> _balls;
	vector<shared_ptr<PuffBall>> _puffBalls;

	shared_ptr<Effect> _effect;

	shared_ptr<RectCollider> _hitCollider;
	shared_ptr<RectCollider> _atkCollider;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<RectCollider>> _colliders;

	vector<shared_ptr<GroundATK>> _atks;

	float _shootDelay = 0.0f;

	int _count = 0;
	
	float _vineDelay = 0.0f;
	float _efCheck = 0.0f;

	float _groundDelay = 0.0f;

	float _hp = 500.0f;
};

