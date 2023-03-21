#pragma once
class Stage1_Panic
{
public:
	Stage1_Panic();
	~Stage1_Panic();

	void Update();
	void PreRender();
	void Render();
	void MidleRender();
	void PostRender();

	void SetPlayer(shared_ptr<Player> player) { _player = player; }

	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	weak_ptr<Player> _player;

	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _sky;
	shared_ptr<Quad> _mainField1;
	shared_ptr<Quad> _mainBG;
	shared_ptr<Quad> _field1;
	shared_ptr<Quad> _field2;
	shared_ptr<Quad> _field3;
	shared_ptr<Quad> _field4;
	shared_ptr<Quad> _field5;
	shared_ptr<Quad> _field6;
	shared_ptr<Quad> _cloud1;
	shared_ptr<Quad> _cloud2;
	shared_ptr<Quad> _cloud3;
	shared_ptr<Quad> _cloud4;
	shared_ptr<Quad> _cloud5;
	shared_ptr<Quad> _cloud6;
	shared_ptr<Quad> _postField1;
	shared_ptr<Quad> _postField2;
	shared_ptr<Quad> _sideField1;
	shared_ptr<Quad> _sideField2;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<RectCollider> _floorCol;
	shared_ptr<RectCollider> _sideCol;
	shared_ptr<RectCollider> _sideCol2;

	vector<shared_ptr<RectCollider>> _colliders;
};

