#pragma once
class EpilogueAni
{
public:
	EpilogueAni();
	~EpilogueAni();

	void Update();
	void Render();
private:
	void CreateAction();

	shared_ptr<Action> _action;
	shared_ptr<Sprite> _sprite;
};

