#pragma once
class PodBullet
{
public:
	enum State
	{

	};
	PodBullet();
	~PodBullet();

	void Update();
	void Render();

	void Enable();
	void Disable();

	bool Collision(shared_ptr<Collider> col);

	bool isActive = false;
	bool isFloor = false;

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Collider> _collider;

	Vector2 _direction = { 0, 1 };

	float _speed = 100.0f;
};

