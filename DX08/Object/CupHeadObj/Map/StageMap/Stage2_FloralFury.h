#pragma once
class Stage2_FloralFury
{
public:
	Stage2_FloralFury();
	~Stage2_FloralFury();

	void Update();
	void Render();
	void PreRender();
	void PostRender();

	void SetPlayer(shared_ptr<Player> player) { _player = player; }

	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	weak_ptr<Player> _player;

	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _sky;
	shared_ptr<Quad> _mainBG;
	shared_ptr<Quad> _hill;
	shared_ptr<Quad> _cloud;
	shared_ptr<Quad> _flower;
	shared_ptr<Quad> _sea;
	shared_ptr<Quad> _sun;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<RectCollider> _floorCol;
	shared_ptr<RectCollider> _sideCol;
	shared_ptr<RectCollider> _sideCol2;

	vector<shared_ptr<RectCollider>> _colliders;
};

