#pragma once
class PuffBall
{
public:
	PuffBall();
	~PuffBall();

	void Update();
	void Render();

	void Enalbe();
	void Disable();

	bool Collision(shared_ptr<Collider> col);
	
	void SetFireDir(Vector2 pos);

	bool isActive = false;
	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;
	shared_ptr<Transform> _muzzle;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Collider> _collider;

	Vector2 _direction = { 0, 0 };

	float _speed = 150.0f;
};

