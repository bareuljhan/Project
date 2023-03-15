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

	void SetAction(State state);
	void SetIDLE();
	void SetIntro();

	void BeamAttack();
	void BulletAttack();
	void GetDamaged(float amount);
	void Dead();

	shared_ptr<Transform> GetTransform() { return _transform; }

	bool isDead = false;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::SPAWN;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	shared_ptr<CupMosaicBuffer> _mosaicBuffer;

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<RectCollider> _collider;

	float _hp = 300.0f;
};

