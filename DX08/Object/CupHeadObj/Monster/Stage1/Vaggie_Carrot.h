#pragma once
class Vaggie_Carrot
{
public:
	enum State
	{
		SPAWN,
		INTRO,
		IDLE,
		BEAM,
		DEAD,
		NONE
	};
	Vaggie_Carrot();
	~Vaggie_Carrot();

	virtual void Update();
	virtual void Render();
	void BulletRender();

	void SetAction(State state);
	void SetIDLE();
	void SetIntro();
	void SetBeam();

	void BeamAttack(shared_ptr<Player> player);
	void BulletAttack(shared_ptr<Player> player);
	void GetDamaged(float amount);
	void Dead();


	vector<shared_ptr<Vaggie_Bullet>> GetBullets() { return _bullets; }
	vector<shared_ptr<Vaggie_Beam>> GetBeams() { return _beams; }
	shared_ptr<Vaggie_Bullet> GetBulletOne() { return _bullets[0]; }
	shared_ptr<Vaggie_Bullet> GetBulletTwo() { return _bullets[1]; }
	shared_ptr<Collider> BulletOneCollider() { return _bullets[0]->GetCollider(); }
	shared_ptr<Collider> BulletTwoCollider() { return _bullets[1]->GetCollider(); }
	shared_ptr<RectCollider> GetBodyCollider() { return _collider; }

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool isDead = false;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::SPAWN;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<RectCollider> _collider;

	vector<shared_ptr<Vaggie_Bullet>> _bullets;
	vector<shared_ptr<Vaggie_Beam>> _beams;

	shared_ptr<Effect> _effect;

	float _hp = 300.0f;
	float _bulletSpeed = 100.0f;
	
	float _shot = 0.0f;
	float _shotDelay = 0.15f;

	float _efCheck = 0.0f;

};

