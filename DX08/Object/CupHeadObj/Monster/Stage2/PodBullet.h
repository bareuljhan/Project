#pragma once
class PodBullet
{
public:
	PodBullet();
	~PodBullet();

	void Update();
	void Render();

private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<CircleCollider> _collider;

	float _bulletSpeed = 80.0f;
};

