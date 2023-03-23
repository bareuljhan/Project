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

	bool isUpdate = false;
	bool isDead = false;

	shared_ptr<PodBullet> GetPodBullet() { return _podBullet; }

	shared_ptr<RectCollider> GetBodyCollider() { return _hitCollider; }
private:
	void CreateAction(string name, Action::Type type);

	State _oldState = NONE;
	State _curState = IDLE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<PodBullet> _podBullet;
	vector<shared_ptr<HandATK>> _balls;

	shared_ptr<Effect> _effect;

	shared_ptr<RectCollider> _hitCollider;
	shared_ptr<RectCollider> _atkCollider;

	vector<shared_ptr<RectCollider>> _colliders;

	float _shootDelay = 0.0f;

	int _count = 0;
	
	float _vineDelay = 0.0;
	

	float _hp = 500.0f;
};

