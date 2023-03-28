#pragma once
class PodBullet
{
public:
	enum State
	{
		BLUE,
		RED,
		PURPLE,
		NONE
	};
	PodBullet();
	~PodBullet();

	void Update();
	void Render();

	void Enable(int index);
	void Disable(int index);

	bool Collision(shared_ptr<Collider> col, int index);

	bool isActive[3] = { true, true, true };
	bool isFloorOne = false;
	bool isFloorTwo = false;
	bool isFloorThr = false;

	shared_ptr<Collider> GetColliderOne() { return _collider1; }
	shared_ptr<Collider> GetColliderTwo() { return _collider2; }
	shared_ptr<Collider> GetColliderThr() { return _collider3; }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider1;
	shared_ptr<Collider> _collider2;
	shared_ptr<Collider> _collider3;

	vector<shared_ptr<Collider>> _colliders;

	shared_ptr<Chomper> _chomper;
	//vector<shared_ptr<Vine>> _vines;

	float _bulletSpeed = 80.0f;

	float _shotDelay = 0.0f;
	float _lifeTime = 1.0f;
};

