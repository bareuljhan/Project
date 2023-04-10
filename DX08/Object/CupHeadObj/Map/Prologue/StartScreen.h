#pragma once
class StartScreen
{
public:
	StartScreen();
	~StartScreen();

	void Update();
	void Render();
	void PostRender();
private:
	void CreateAction(Action::Type type);

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Quad> _quad;
};

