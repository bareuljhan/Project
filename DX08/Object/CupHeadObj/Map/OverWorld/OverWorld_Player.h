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

	struct Vertex
	{
		Vector2 pos;
		float g;
		float h;
		float f;

		bool operator<(const Vertex& other) const
		{
			return f < other.f;
		}

		bool operator>(const Vertex& other) const
		{
			return f > other.f;
		}
	};

	OverWorld_Player();
	~OverWorld_Player();
	
	void SetRight();
	void SetLeft();

	void Update();
	void Render();

	bool CanGo(Vector2 pos);
	void Init();
	void AStar(Vector2 start, Vector2 end);
	void SetAction(State state);


	shared_ptr<Transform> GetTransform() { return _transform; }
private:
	void CreateAction(string name, Action::Type type);

	State _curState = State::IDLE;
	State _oldState = State::NONE;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;

	vector<vector<bool>> _discorvered;
	vector<vector<Vector2>> _parent;

	shared_ptr<Quad> _quad;
	float _speed = 300.0f;
};

