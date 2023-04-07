#pragma once
class OverWorld_Player
{
public:	
	enum State
	{
		IDLE,
		RUN_DOWN,
		RUN_UP,
		RUN,
		CLEAR,
		NONE
	};

	struct Vertex
	{
		Vector2 pos;
		Vector2 index;

		float g;
		float h;
		float f;

		bool operator > (const Vertex& other) const
		{
			return this->f > other.f;
		}
		bool operator < (const Vertex& other) const
		{
			return this->f < other.f;
		}
	};

	OverWorld_Player();
	~OverWorld_Player();
	
	void SetRight();
	void SetLeft();

	void Update();
	void Render();

	void Init();
	void MoveTO();
	void AStar(Vector2 start, Vector2 end);
	void SetAction(State state);

	shared_ptr<Transform> GetTransform() { return _transform; }
	bool isRun = false;
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::IDLE;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Collider> _collider;

	vector<vector<bool>> _discorvered;
	vector<vector<Vector2>> _parent;

	shared_ptr<Route> _route;

	Vector2 _targetIndex = Vector2(7, 14);
	Vector2 _direction = { 0,0 };
	Vector2 _endPos = { 0,0 };

	vector<Vector2> _pathPos;
	vector<Vector2> _path;

	float _speed = 50.0f;

	int _posIndex = 1;
	int _index = 0;
};

