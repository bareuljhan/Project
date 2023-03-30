#pragma once
class WinScreen
{
public:
	WinScreen();
	~WinScreen();

	void Update();
	void Render();

	void SetEnd() { isEnd = true; }

	bool isEnd = false;
private:
	void CreateAction(string name, Action::Type type);
	
	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
	
};

