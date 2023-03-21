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
	void PlayEffect();

	bool isUpdate = false;
private:
	void CreateAction(string name, Action::Type type);

	State _oldState = NONE;
	State _curState = IDLE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<PodBullet> _podBullet;

	shared_ptr<Effect> _effect;

	shared_ptr<RectCollider> _hitCollider;
	shared_ptr<RectCollider> _atkCollider;

	vector<shared_ptr<RectCollider>> _colliders;
};

