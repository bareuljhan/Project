#pragma once
class Tutorial_Iner_BG
{
public:
	Tutorial_Iner_BG();
	~Tutorial_Iner_BG();

	void Update();
	void Render();

	Vector2 LeftBottom();
	Vector2 RightTop();

	shared_ptr<Transform> GetTransform() { return _transform; }
	void SetPlayer(shared_ptr<Player> player) { _player = player; }

	shared_ptr<RectCollider> GetExitCol() { return _exitCol; }
	shared_ptr<CircleCollider> GetTargetCol() { return _targetCol; }

	void Damaged(float amount);
	void Init();
private:
	weak_ptr<Player> _player;

	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _mainSheet;
	shared_ptr<Quad> _jumpCube;
	shared_ptr<Quad> _exit;
	shared_ptr<Quad> _cylinder1;
	shared_ptr<Quad> _cylinder2;
	shared_ptr<Quad> _pyramidTarget;
	shared_ptr<Quad> _target;

	vector<shared_ptr<RectCollider>> _colliders;
	shared_ptr<RectCollider> _floorCol;
	shared_ptr<RectCollider> _cubeCol;
	shared_ptr<RectCollider> _exitCol;
	shared_ptr<RectCollider> _cylinder1Col;
	shared_ptr<RectCollider> _cylinder2Col;
	shared_ptr<RectCollider> _cylinder3Col;
	shared_ptr<CircleCollider> _targetCol;

	float _targetHP = 50.0f;
	float _speed = 200.0f;
	
	bool _isDestroy = false;
};

