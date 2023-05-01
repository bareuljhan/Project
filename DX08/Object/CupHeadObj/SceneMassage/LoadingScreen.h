#pragma once
class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void Update();
	void Render();
	bool isReady = false;
	shared_ptr<FadeBuffer> GetBuffer() { return _buffer; }
private:
	void CreateAction(string name, Action::Type type);

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	shared_ptr<Quad> _quad;
	shared_ptr<FadeBuffer> _buffer;

	float _delay = 0.0f;
};

