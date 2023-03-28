#pragma once
class Chomper
{
public:
	enum State
	{
		IDLE,
		NONE
	};
	Chomper();
	~Chomper();

	void Update();
	void Render();

	void Enable();
	void Disable();

	bool isActive = true;
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Collider> _collider;
};

