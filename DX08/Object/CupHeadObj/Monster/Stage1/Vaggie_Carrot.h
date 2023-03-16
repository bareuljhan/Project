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
	void BulletRender() { for (auto bullet : _bullets) bullet->Render(); }

	void SetAction(State state);
	void SetIDLE();
	void SetIntro();
	void SetBeam();

	void BeamAttack(shared_ptr<Player> player);
	void BulletAttack(shared_ptr<Player> player);
	void GetDamaged(float amount);
	void Dead();

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

	float _shotDelay = 0.0f;
	float _delay = 1.0f;
	
	float _hp = 300.0f;
	float _bulletSpeed = 200.0f;
};

