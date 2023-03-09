#pragma once
class PrologueAni
{
public:
	PrologueAni();
	~PrologueAni();

	void Update();
	void Render();
private:
	void CreateAction();

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

