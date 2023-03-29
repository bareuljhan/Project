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
	shared_ptr<RectCollider> GetFloorCollider() { return _floorCol; }
	shared_ptr<RectCollider> GetSideCollider() { return _sideCol; }
	shared_ptr<RectCollider> GetSideTwoCollider() { return _sideCol2; }
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

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<RectCollider> _floorCol;
	shared_ptr<RectCollider> _sideCol;
	shared_ptr<RectCollider> _sideCol2;
	shared_ptr<RectCollider> _platformCol1;
	shared_ptr<RectCollider> _platformCol2;
	shared_ptr<RectCollider> _platformCol3;

	vector<shared_ptr<RectCollider>> _colliders;
};

