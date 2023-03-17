#pragma once
class ClearMessage
{
public:
	ClearMessage();
	~ClearMessage();

	void Update();
	void Render();
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

};

