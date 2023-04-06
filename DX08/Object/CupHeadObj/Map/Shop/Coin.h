#pragma once
class Coin
{
public:
	Coin();
	~Coin();

	void Update();
	void Render();
	void PostRender();

	shared_ptr<Transform> GetTransform() { return _transform; }
	
	bool isActive = false;
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Transform> _transform;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;
};

