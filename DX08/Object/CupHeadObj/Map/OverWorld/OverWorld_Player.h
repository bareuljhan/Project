#pragma once
class OverWorld_Player
{
public:	
	enum State
	{
		IDLE,
		RUN,
		RUN_UP,
		RUN_DOWN,
		RUN_WD,
		RUN_SD,
		CLEAR,
		NONE
	};

	OverWorld_Player();
	~OverWorld_Player();
	
	void SetRight();
	void SetLeft();

	void Update();
	void Render();

	void Init();
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

	vector<vector<bool>> _discorvered;
	vector<vector<Vector2>> _parent;

	shared_ptr<Route> _route;

	Vector2 _direction = { 0,0 };
	Vector2 _endPos = { 0,0 };
	float _speed = 300.0f;
};

