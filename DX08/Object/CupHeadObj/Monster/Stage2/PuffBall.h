#pragma once
class PuffBall
{
public:
	PuffBall();
	~PuffBall();

	void Update();
	void Render();

	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	bool isActive = false;
	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Collider> _collider;

	Vector2 _direction = { -1, 1 };
	Vector2 _directionDW = { -1, -1 };

	float _speed = 200.0f;
	float _delay = 0.0f;

};

