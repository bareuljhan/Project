#pragma once
class Vaggie_Carrot
{
public:
	enum State
	{
		INTRO,
		IDLE,
		ATTACK,
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

	void AttackToPlayer();
	void GetDamaged(float amount);
	void Dead();

private:
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite>> _sprites;
};

