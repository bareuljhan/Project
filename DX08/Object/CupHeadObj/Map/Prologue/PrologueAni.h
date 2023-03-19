#pragma once
class PrologueAni
{
public:
	enum State
	{
		ONE,
		TWO,
		NONE
	};
	PrologueAni();
	~PrologueAni();

	void Update();
	void Render();

	void SetNext();

	void SetAction(State state);
private:
	void CreateAction(string name, Action::Type type);

	State _curState = ONE;
	State _oldState = NONE;

	vector<shared_ptr<Sprite>> _sprites;
	vector<shared_ptr<Action>> _actions;
};

